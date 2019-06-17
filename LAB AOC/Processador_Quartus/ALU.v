module ALU (input Reset, input [4:0] ALU_Op, input [31:0] Data_1, input [31:0] Data_2, output reg True, output reg [31:0] Result);



always @ (Data_1 or Data_2 or ALU_Op or Reset)
begin
	if (Reset)
	begin
	
		Result <= 0;
		True <= 0;
	
	end
	else
	begin
	
		True <= 0;
	
		case(ALU_Op)
	
			0: //ADD
			begin
				Result <= Data_1 + Data_2;
			end
	
			1: //SUB
			begin
				Result <= Data_1 - Data_2;
			end
	
			2: //MUL
			begin
				Result <= Data_1 * Data_2;
			end
	
			3: //DIV
			begin
				Result <= Data_1 / Data_2;
			end
	
			4: //MOD
			begin
				Result <= Data_1 % Data_2;
			end
	
			5: //AND
			begin
				Result <= Data_1 & Data_2;
			end
	
			6: //OR
			begin
				Result <= Data_1 | Data_2;
			end
	
			7: //XOR
			begin
				Result <= Data_1 ^ Data_2;
			end
	
			8: //NOT
			begin
				Result <= ~Data_1;
			end
	
			9: //Shift Left
			begin
				Result <= Data_1 << Data_2;
			end
	
			10: //Shift Right
			begin
				Result <= Data_1 >> Data_2;
			end
	
			11: //Equal Than
			begin
				if (Data_1 == Data_2) begin
					Result <= 1;
					True <= 1;
				end
	
				else begin
					Result <= 0;
					True <= 0;
				end
			end
	
			12: //Not Equal Than
			begin
				if (Data_1 != Data_2) begin
					Result <= 1;
					True <= 1;
				end
	
				else begin
					Result <= 0;
					True <= 0;
				end
			end
	
			13: //Greater or Equal Than
			begin
				if (Data_1 >= Data_2) begin
					Result <= 1;
					True <= 1;
				end
	
				else begin
					Result <= 0;
					True <= 0;
				end
			end
	
			14: //Greater Than
			begin
				if (Data_1 > Data_2) begin
					Result <= 1;
					True <= 1;
				end
	
				else begin
					Result <= 0;
					True <= 0;
				end
			end
	
			15: //Less or Equal Than
			begin
				if (Data_1 <= Data_2) begin
					Result <= 1;
					True <= 1;
				end
	
				else begin
					Result <= 0;
					True <= 0;
				end
			end
	
			16: //Less Than
			begin
				if (Data_1 < Data_2) begin
					Result <= 1;
					True <= 1;
				end
	
				else begin
					Result <= 0;
					True <= 0;
				end
			end
	
			17: //NOP
			begin
				Result <= 0;
				True <= 0;
			end
	
			18: //IMM
			begin
				Result <= Data_2;
				True <= 0;
			end
			
			default:
			begin
				Result <= 0;
				True <= 0;
			end
			
		endcase
	end
end

endmodule