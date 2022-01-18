module Mux13
#(parameter BITS = 13)
(
	input Switch,
	input [BITS-1:0] Data_0,
	input [BITS-1:0] Data_1,
	output reg [BITS-1:0] Data_Out
);

always @ (Switch or Data_0 or Data_1)
begin
	if (Switch)
		Data_Out <= Data_1;
	else
		Data_Out <= Data_0;
end

endmodule