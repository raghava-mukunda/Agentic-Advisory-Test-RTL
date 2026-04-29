// pipeline_unit.v
// Multi-stage pipeline with hazards and saturation

module pipeline_unit #(
    parameter WIDTH = 8
)(
    input clk,
    input rst,

    input [WIDTH-1:0] a,
    input [WIDTH-1:0] b,
    input [1:0] op,

    output reg [WIDTH-1:0] y,

    output reg err_overflow,
    output reg err_underflow,
    output reg err_hazard,
    output reg err_sat
);

localparam MAX = (1<<WIDTH)-1;

// pipeline registers
reg [WIDTH-1:0] a1, b1;
reg [WIDTH-1:0] a2, b2;
reg [WIDTH-1:0] res;

reg [1:0] op1, op2;

// stage 1
always @(posedge clk) begin
    a1 <= a;
    b1 <= b;
    op1 <= op;
end

// stage 2
always @(posedge clk) begin
    a2 <= a1;
    b2 <= b1;
    op2 <= op1;
end

// stage 3 (compute)
always @(posedge clk or posedge rst) begin
    if (rst) begin
        y <= 0;
        err_overflow <= 0;
        err_underflow <= 0;
        err_hazard <= 0;
        err_sat <= 0;
    end else begin

        err_overflow <= 0;
        err_underflow <= 0;
        err_hazard <= 0;
        err_sat <= 0;

        case(op2)

        2'b00: res = a2 + b2;
        2'b01: begin
            if (a2 < b2) begin
                err_underflow <= 1;
                res = 0;
            end else
                res = a2 - b2;
        end
        2'b10: res = a2 * b2;
        2'b11: begin
            if (b2 == 0)
                err_hazard <= 1;
            else
                res = a2 / b2;
        end

        endcase

        // overflow detection
        if (res > MAX) begin
            err_overflow <= 1;
            res = MAX;
        end

        // saturation bug
        if (res > 200) begin
            err_sat <= 1;
        end

        y <= res;
    end
end

endmodule
