module Extend_Imm 
(
	input signed [19:0] In_Imm, 
	input Long_Imm, 
	output reg signed [31:0] Out_Imm
);

always @ (In_Imm or Long_Imm)
begin
	if (Long_Imm)
	begin
		Out_Imm <= {{12{In_Imm[19]}},In_Imm};
	end else
	begin
		Out_Imm <= {{18{In_Imm[13]}},In_Imm[13:0]};
	end
end

endmodule