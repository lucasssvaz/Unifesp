module StackFile (input Reset, input Sys_Clock, input Stack_Write, input Stack_Enable, input [7:0] NPPC, output reg [7:0] Ret_Add, output reg Err_Out);

reg [7:0] StackReg[63:0];

reg [5:0] Stack_Pointer;

always @ (negedge Sys_Clock or posedge Reset)
begin
	if (Reset)
	begin
		Ret_Add = 0;
		Stack_Pointer = 0;
		Err_Out = 0;
	end
	else if (Stack_Enable && Stack_Write)
	begin
		if (Stack_Pointer <= 6'b111111)
		begin	
			StackReg[Stack_Pointer] = NPPC;
			Stack_Pointer = Stack_Pointer + 1;
			Err_Out = 0;
		end
		else
		begin
			Err_Out = 1;
		end
	end
	else if (Stack_Enable && (!Stack_Write))
	begin
		if (Stack_Pointer > 0)
		begin
			Stack_Pointer = Stack_Pointer - 1;
			Ret_Add = StackReg[Stack_Pointer];
			Err_Out = 0;
		end
		else
		begin
			Err_Out = 1;
		end
	end
end

endmodule