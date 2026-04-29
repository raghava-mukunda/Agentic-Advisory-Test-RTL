// alu_fsm.v
// Stateful FSM-based ALU — upgraded for AAT-RTL benchmarking
//
// Improvements over baseline:
//   - 4-state FSM (IDLE → LOAD → EXEC → DONE) to create multi-cycle
//     dependencies that random testing struggles to reach
//   - Accumulator register — enables carry/overflow across cycles
//   - Saturation logic — triggers a distinct saturation failure mode
//   - Parameterised width — can be instantiated at 8/16 bit
//   - Cleaner error classification: div_zero and overflow are separate
//     error outputs so the analyzer can distinguish them without
//     inferring from input values
//
// Failure modes:
//   | Type         | Condition                          | Cycle |
//   |--------------|------------------------------------| ------|
//   | divide_by_zero| op==DIV && b==0                  | EXEC  |
//   | overflow      | (a + b) > MAX or (a * b) > MAX   | DONE  |
//   | saturation    | acc exceeds 2*MAX threshold       | DONE  |
//   | underflow     | a - b wraps below 0 (unsigned)   | EXEC  |

module alu_fsm #(
    parameter WIDTH = 8
)(
    input                   clk,
    input                   rst,
    input  [WIDTH-1:0]      a,
    input  [WIDTH-1:0]      b,
    input  [1:0]            op,
    output reg [WIDTH-1:0]  y,
    output reg              err_div_zero,
    output reg              err_overflow,
    output reg              err_underflow,
    output reg [1:0]        state_out    // expose state for testbench
);

// ---- Parameters ----
localparam MAX_VAL   = (1 << WIDTH) - 1;
localparam OVF_THRESH = 200;              // overflow threshold (< MAX for testability)
localparam SAT_THRESH = 220;

// ---- FSM states ----
localparam IDLE = 2'b00;
localparam LOAD = 2'b01;
localparam EXEC = 2'b10;
localparam DONE = 2'b11;

reg [1:0]        state;
reg [WIDTH-1:0]  a_reg, b_reg;
reg [1:0]        op_reg;
reg [WIDTH:0]    result_wide;   // one extra bit to catch overflow
reg [WIDTH-1:0]  accumulator;   // carries value across operations

// ---- FSM ----
always @(posedge clk or posedge rst) begin
    if (rst) begin
        state        <= IDLE;
        y            <= 0;
        accumulator  <= 0;
        err_div_zero <= 0;
        err_overflow <= 0;
        err_underflow<= 0;
        result_wide  <= 0;
    end else begin
        case (state)

            IDLE: begin
                // Clear errors, latch inputs
                err_div_zero  <= 0;
                err_overflow  <= 0;
                err_underflow <= 0;
                a_reg  <= a;
                b_reg  <= b;
                op_reg <= op;
                state  <= LOAD;
            end

            LOAD: begin
                // One idle cycle — creates multi-cycle dependency
                // Agent must hold inputs stable across IDLE→LOAD→EXEC
                state <= EXEC;
            end

            EXEC: begin
                case (op_reg)
                    2'b00: begin   // ADD
                        result_wide <= {1'b0, a_reg} + {1'b0, b_reg};
                    end
                    2'b01: begin   // SUB
                        if (a_reg < b_reg) begin
                            err_underflow <= 1;
                            result_wide   <= 0;
                        end else begin
                            result_wide <= {1'b0, a_reg} - {1'b0, b_reg};
                        end
                    end
                    2'b10: begin   // MUL (lower WIDTH bits only)
                        result_wide <= a_reg * b_reg;
                    end
                    2'b11: begin   // DIV
                        if (b_reg == 0) begin
                            err_div_zero <= 1;
                            result_wide  <= 0;
                        end else begin
                            result_wide <= {1'b0, a_reg / b_reg};
                        end
                    end
                endcase
                state <= DONE;
            end

            DONE: begin
                y <= result_wide[WIDTH-1:0];

                // Overflow check: MSB of wide result is set, or result > threshold
                if (result_wide[WIDTH] || result_wide[WIDTH-1:0] > OVF_THRESH) begin
                    err_overflow <= 1;
                end

                // Accumulator update — saturation bug: saturates but reports error
                accumulator <= accumulator + result_wide[WIDTH-1:0];
                if (accumulator > SAT_THRESH) begin
                    err_overflow <= 1;   // reuse overflow flag for saturation
                end

                state <= IDLE;
            end

        endcase
    end
end

assign state_out = state;

endmodule
