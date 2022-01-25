module StackFile 
(
	input Reset, Slow_Clock, Stack_Write, Stack_Enable, 
	input [12:0] NPPC, 
	output reg [12:0] Ret_Add, 
	output reg Err_Out
);

reg [12:0] StackReg[63:0];

reg [9:0] Stack_Pointer = 0;

always @ (negedge Slow_Clock or posedge Reset)
begin
	if (Reset)
	begin
		Ret_Add = 0;
		Stack_Pointer = 0;
		Err_Out = 0;
	end
	else if (Stack_Enable && Stack_Write)
	begin
		if (Stack_Pointer < 10'b1111111111)
		begin	
			StackReg[Stack_Pointer] = NPPC;
			Stack_Pointer = Stack_Pointer + 10'b1;
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
			Stack_Pointer = Stack_Pointer - 10'b1;
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