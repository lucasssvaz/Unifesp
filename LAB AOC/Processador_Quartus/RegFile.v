module RegFile (input Reset, input Sys_Clock, input Reg_Write, input [31:0] Write_Data, input [5:0] Reg_1, input [5:0] Reg_2, input [5:0] Reg_WR, output [31:0] Data_1, output [31:0] Data_2, output [31:0] Data_3);

reg [31:0] DataReg[63:0];

//READ
assign Data_1 = DataReg[Reg_1];
assign Data_2 = DataReg[Reg_2];
assign Data_3 = DataReg[Reg_WR];


always @ (negedge Sys_Clock or posedge Reset) //WRITE
begin
	if (Reset)
	begin
		DataReg[0] <= 32'b00000000_00000000_00000000_00000000;
	end
	else if (Reg_Write && (Reg_WR != 0))
	begin
		DataReg[Reg_WR] <= Write_Data;
	end
end

endmodule