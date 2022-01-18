module ALU
(
	output reg True,
	output reg signed [31:0] Result,
	input Fast_Clock,
	input signed [31:0] Data_1,
	input signed [31:0] Data_2,
	input [4:0] ALU_Op
);

always @ (negedge Fast_Clock)
begin
	case (ALU_Op)
	
		0:		//ADD
		begin
			Result = Data_1 + Data_2;
			True = 0;
		end
	
		1:		//SUB
		begin
			Result = Data_1 - Data_2;
			True = 0;
		end
		
		2:		//MUL
		begin
			Result = Data_1 * Data_2;
			True = 0;
		end
		
		3:		//DIV
		begin
			Result = Data_1 / Data_2;
			True = 0;
		end
		
		4:		//MOD
		begin
			Result = Data_1 % Data_2;
			True = 0;
		end
		
		5:		//AND
		begin
			Result = Data_1 & Data_2;
			True = 0;
		end
		
		6:		//OR
		begin
			Result = Data_1 | Data_2;
			True = 0;
		end
		
		7:		//XOR
		begin
			Result = Data_1 ^ Data_2;
			True = 0;
		end
		
		8:		//NOT
		begin
			Result = ~Data_1;
			True = 0;
		end
		
		9:		//Shift Left
		begin
			Result = Data_1 <<< Data_2;
			True = 0;
		end
		
		10:	//Shift Right
		begin
			Result = Data_1 >>> Data_2;
			True = 0;
		end
		
		11:	//Equal
		begin
			if (Data_1 == Data_2)
			begin
				Result = 1;
				True = 1;
			end
			else
			begin
				Result = 0;
				True = 0;
			end
		end
		
		12:	//Not Equal
		begin
			if (Data_1 != Data_2)
			begin
				Result = 1;
				True = 1;
			end
			else
			begin
				Result = 0;
				True = 0;
			end
		end
		
		13:	//Greater or Equal
		begin
			if (Data_1 >= Data_2)
			begin
				Result = 1;
				True = 1;
			end
			else
			begin
				Result = 0;
				True = 0;
			end
		end
		
		14:	//Greater
		begin
			if (Data_1 > Data_2)
			begin
				Result = 1;
				True = 1;
			end
			else
			begin
				Result = 0;
				True = 0;
			end
		end
		
		15:	//Less or Equal
		begin
			if (Data_1 <= Data_2)
			begin
				Result = 1;
				True = 1;
			end
			else
			begin
				Result = 0;
				True = 0;
			end
		end
		
		16:	//Less
		begin
			if (Data_1 < Data_2)
			begin
				Result = 1;
				True = 1;
			end
			else
			begin
				Result = 0;
				True = 0;
			end
		end
		
		17:	//NOP
		begin
			Result = 0;
			True = 0;
		end
		
		18:	//IMM
		begin
			Result = Data_2;
			True = 0;
		end
		
		default:
		begin
			Result = 0;
			True = 0;
		end
	
	endcase

end

endmodule
