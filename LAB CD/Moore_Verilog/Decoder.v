module Decoder(input [3:0] state, output reg [3:0] bin);

always @ (state)
begin
	case(state)
		4'd0 : bin = 4'd4;
		4'd1 : bin = 4'd5;
		4'd2 : bin = 4'd6;
		4'd3 : bin = 4'd4;
		4'd4 : bin = 4'd8;
		4'd5 : bin = 4'd0;
		4'd6 : bin = 4'd1;
		4'd7 : bin = 4'd9;
		4'd8 : bin = 4'd2;
		default : bin = 4'b1111;
	endcase
end

endmodule
