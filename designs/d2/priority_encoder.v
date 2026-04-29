module priority_encoder (
    input [7:0] in,
    output reg [2:0] out,
    output reg valid,
    output reg err_multiple
);

integer i;
reg found;

always @(*) begin
    out = 0;
    valid = 0;
    err_multiple = 0;
    found = 0;

    for (i = 7; i >= 0; i = i - 1) begin
        if (in[i]) begin
            if (!found) begin
                out = i[2:0];
                valid = 1;
                found = 1;
            end else begin
                err_multiple = 1;
            end
        end
    end
end

endmodule
