module sat_alu #(
    parameter WIDTH = 8
)(
    input  [WIDTH-1:0] a,
    input  [WIDTH-1:0] b,
    input  [2:0] op,

    output reg [WIDTH-1:0] y,
    output reg err_overflow,
    output reg err_div_zero,
    output reg err_saturation
);

localparam MAX = (1 << WIDTH) - 1;

reg [WIDTH:0] temp;

// Zero-extended versions (KEY FIX)
wire [WIDTH:0] a_ext = {1'b0, a};
wire [WIDTH:0] b_ext = {1'b0, b};

always @(*) begin
    err_overflow   = 0;
    err_div_zero   = 0;
    err_saturation = 0;
    temp = 0;

    case(op)

        3'b000: temp = a_ext + b_ext;

        3'b001: begin
            if (a < b) begin
                temp = 0;
                err_saturation = 1;
            end else begin
                temp = a_ext - b_ext;
            end
        end

        3'b010: temp = a_ext * b_ext;

        3'b011: begin
            if (b == 0) begin
                temp = 0;
                err_div_zero = 1;
            end else begin
                temp = a_ext / b_ext;
            end
        end

        3'b100: temp = a_ext << 2;

        3'b101: temp = b_ext << 3;

        3'b110: temp = a_ext ^ b_ext;

        3'b111: temp = ~(a_ext & b_ext);

    endcase

    if (temp > MAX) begin
        y = MAX;
        err_overflow = 1;
    end else begin
        y = temp[WIDTH-1:0];
    end
end

endmodule
