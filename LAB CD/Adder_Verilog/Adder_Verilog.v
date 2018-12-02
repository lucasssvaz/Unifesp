module Adder_Verilog(input [1:0] A, input [1:0] B, output [6:0] A_disp, output [6:0] B_disp, output [6:0] Res_disp);

reg [2:0] Res;

SeteSeg Hex3(.bin({1'd0,Res}), .out(Res_disp));
SeteSeg Hex6(.bin({2'd0,A}), .out(A_disp));
SeteSeg Hex5(.bin({2'd0,B}), .out(B_disp));

always@(A or B)
begin
	Res = A + B;
end

endmodule
