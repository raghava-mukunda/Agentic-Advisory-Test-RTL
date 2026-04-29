// comb_unit.v
// Complex combinational arithmetic + logic unit

module comb_unit #(
    parameter WIDTH = 8
)(
    input  [WIDTH-1:0] a,
    input  [WIDTH-1:0] b,
    input  [2:0] op,

    output reg [WIDTH-1:0] y,

    output reg err_overflow,
    output reg err_underflow,
    output reg err_div_zero,
    output reg err_flag,
    output reg err_sat
);

localparam MAX = (1 << WIDTH) - 1;

// internal signals
reg [WIDTH:0] temp;
reg carry;
reg zero_flag;

always @(*) begin

    // reset flags
    err_overflow  = 0;
    err_underflow = 0;
    err_div_zero  = 0;
    err_flag      = 0;
    err_sat       = 0;

    carry = 0;
    zero_flag = 0;

    case(op)

    // ADD
    3'b000: begin
        temp = a + b;
        y = temp[WIDTH-1:0];
        carry = temp[WIDTH];

        if (carry)
            err_overflow = 1;
    end

    // SUB
    3'b001: begin
        if (a < b) begin
            err_underflow = 1;
            y = 0;
        end else begin
            y = a - b;
        end
    end

    // MUL
    3'b010: begin
        temp = a * b;
        y = temp[WIDTH-1:0];

        if (temp > MAX)
            err_overflow = 1;
    end

    // DIV
    3'b011: begin
        if (b == 0) begin
            err_div_zero = 1;
            y = 0;
        end else begin
            y = a / b;
        end
    end

    // AND
    3'b100: y = a & b;

    // OR
    3'b101: y = a | b;

    // XOR
    3'b110: y = a ^ b;

    // SATURATED ADD (bug injected)
    3'b111: begin
        temp = a + b;

        if (temp > 200) begin
            err_sat = 1;
            y = MAX;  // saturation
        end else begin
            y = temp[WIDTH-1:0];
        end
    end

    endcase

    // flag logic (intentional bug)
    zero_flag = (y == 0);

    if (zero_flag && (a != b))
        err_flag = 1;

end

endmodule
