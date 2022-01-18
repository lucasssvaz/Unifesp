module Ctrl_Module
(
	input [5:0] Instruction,
	output reg IO_Enable,
	output reg IO_Selection,
	output reg Reg_Write,
	//output reg R_Type,
	output reg Jump_R,
	output reg Jump_I,
	output reg Stack_Enable,
	output reg Stack_Write,
	output reg Branch,
	output reg Mem_Write,
	//output reg W_Only,
	output reg Mem_To_Reg,
	output reg [4:0] ALU_Op,
	output reg ALU_Src,
	output reg Halt,
	output reg Long_Imm
);

always @ (Instruction)
begin
	
	case (Instruction[5:4])
		
		2'b00:
		begin

			IO_Enable = 0;
			IO_Selection = 0;
			Reg_Write = 1;
			Jump_R = 0;
			Jump_I = 0;
			Stack_Enable = 0;
			Stack_Write = 0;
			//Branch
			Mem_Write = 0;
			Mem_To_Reg = 0;
			//ALU_Op
			ALU_Src = 0;
			Halt = 0;
			Long_Imm = 0;

			case (Instruction[3:0])

				4'b0000: //ADD
				begin
					Branch = 0;
					ALU_Op = 0;
				end

				4'b0001: //AND
				begin
					Branch = 0;
					ALU_Op = 5;
				end

				4'b0010: //BEQ
				begin
					Reg_Write = 0;
					Branch = 1;
					ALU_Op = 11;
				end

				4'b0011: //BGE
				begin
					Reg_Write = 0;
					Branch = 1;
					ALU_Op = 13;
				end

				4'b0100: //BGT
				begin
					Reg_Write = 0;
					Branch = 1;
					ALU_Op = 14;
				end

				4'b0101: //BLE
				begin
					Reg_Write = 0;
					Branch = 1;
					ALU_Op = 15;
				end

				4'b0110: //BLT
				begin
					Reg_Write = 0;
					Branch = 1;
					ALU_Op = 16;
				end

				4'b0111: //BNE
				begin
					Reg_Write = 0;
					Branch = 1;
					ALU_Op = 12;
				end

				4'b1000: //DIV
				begin
					Branch = 0;
					ALU_Op = 3;
				end

				4'b1001: //HALT
				begin
					Branch = 0;
					Reg_Write = 0;
					ALU_Op = 17;
					Halt = 1;
				end

				4'b1010: //MOD
				begin
					Branch = 0;
					ALU_Op = 4;
				end

				4'b1011: //MUL
				begin
					Branch = 0;
					ALU_Op = 2;
				end

				4'b1100: //NOP
				begin
					Branch = 0;
					ALU_Op = 17;
					Reg_Write = 0;
				end

				4'b1101: //OR
				begin
					Branch = 0;
					ALU_Op = 6;
				end

				4'b1110: //STEQ
				begin
					Branch = 0;
					ALU_Op = 11;
				end

				4'b1111: //STGT
				begin
					Branch = 0;
					ALU_Op = 14;
				end

			endcase

		end

		2'b01:
		begin
			
			IO_Enable = 0;
			IO_Selection = 0;
			Reg_Write = 1;
			Jump_R = 0;
			Jump_I = 0;
			Stack_Enable = 0;
			Stack_Write = 0;
			//Branch
			Mem_Write = 0;
			Mem_To_Reg = 0;
			//ALU_Op
			ALU_Src = 0;
			Halt = 0;
			Long_Imm = 0;

			case (Instruction[3:0])

				4'b0000: //STLT
				begin
					Branch = 0;
					ALU_Op = 16;
				end

				4'b0001: //STNE
				begin
					Branch = 0;
					ALU_Op = 12;
				end

				4'b0010: //SUB
				begin
					Branch = 0;
					ALU_Op = 1;
				end

				4'b0011: //XOR
				begin
					Branch = 0;
					ALU_Op = 7;
				end

				4'b0100: //STGE
				begin
					Branch = 0;
					ALU_Op = 13;
				end

				4'b0101: //STLE
				begin
					Branch = 0;
					ALU_Op = 15;
				end
				
				default:
				begin
					Branch = 0;
					ALU_Op = 17;
				end
				
			endcase

		end

		2'b10:
		begin
			
			//IO_Enable
			//IO_Selection
			//Reg_Write
			//Jump_R
			//Jump_I
			//Stack_Enable
			//Stack_Write
			Branch = 0;
			Mem_Write = 0;
			Mem_To_Reg = 0;
			ALU_Op = 18;
			ALU_Src = 1;
			Halt = 0;
			Long_Imm = 1;

			case (Instruction[3:0])

				4'b0000: //IN
				begin
					IO_Enable = 1;
					IO_Selection = 0;
					Reg_Write = 1;
					Jump_R = 0;
					Jump_I = 0;
					Stack_Enable = 0;
					Stack_Write = 0;
				end

				4'b0001: //JAL
				begin
					IO_Enable = 0;
					IO_Selection = 0;
					Reg_Write = 0;
					Jump_R = 0;
					Jump_I = 1;
					Stack_Enable = 1;
					Stack_Write = 1;
				end

				4'b0010: //JR
				begin
					IO_Enable = 0;
					IO_Selection = 0;
					Reg_Write = 0;
					Jump_R = 1;
					Jump_I = 0;
					Stack_Enable = 0;
					Stack_Write = 0;
				end

				4'b0011: //LI
				begin
					IO_Enable = 0;
					IO_Selection = 0;
					Reg_Write = 1;
					Jump_R = 0;
					Jump_I = 0;
					Stack_Enable = 0;
					Stack_Write = 0;
				end

				4'b0100: //OUT
				begin
					IO_Enable = 1;
					IO_Selection = 1;
					Reg_Write = 0;
					Jump_R = 0;
					Jump_I = 0;
					Stack_Enable = 0;
					Stack_Write = 0;
				end

				4'b0101: //RET
				begin
					IO_Enable = 0;
					IO_Selection = 0;
					Reg_Write = 0;
					Jump_R = 0;
					Jump_I = 0;
					Stack_Enable = 1;
					Stack_Write = 0;
				end

				4'b0110: //J
				begin
					IO_Enable = 0;
					IO_Selection = 0;
					Reg_Write = 0;
					Jump_R = 0;
					Jump_I = 1;
					Stack_Enable = 0;
					Stack_Write = 0;
				end

				default:
				begin
					IO_Enable = 0;
					IO_Selection = 0;
					Reg_Write = 0;
					Jump_R = 0;
					Jump_I = 0;
					Stack_Enable = 0;
					Stack_Write = 0;
				end

			endcase

		end

		2'b11:
		begin

			IO_Enable = 0;
			IO_Selection = 0;
			//Reg_Write
			Jump_R = 0;
			Jump_I = 0;
			Stack_Enable = 0;
			Stack_Write = 0;
			Branch = 0;
			//Mem_Write
			//Mem_To_Reg
			//ALU_Op
			ALU_Src = 1;
			Halt = 0;
			Long_Imm = 0;
			
			case (Instruction[3:0])

				4'b0000: //ADDI
				begin
					Reg_Write = 1;
					Mem_Write = 0;
					Mem_To_Reg = 0;
					ALU_Op = 0;
				end

				4'b0001: //DIVI
				begin
					Reg_Write = 1;
					Mem_Write = 0;
					Mem_To_Reg = 0;
					ALU_Op = 3;
				end

				4'b0010: //LW
				begin
					Reg_Write = 1;
					Mem_Write = 0;
					Mem_To_Reg = 1;
					ALU_Op = 0;
				end

				4'b0011: //MODI
				begin
					Reg_Write = 1;
					Mem_Write = 0;
					Mem_To_Reg = 0;
					ALU_Op = 4;
				end

				4'b0100: //MOVE
				begin
					Reg_Write = 1;
					Mem_Write = 0;
					Mem_To_Reg = 0;
					ALU_Op = 0;
				end

				4'b0101: //MULI
				begin
					Reg_Write = 1;
					Mem_Write = 0;
					Mem_To_Reg = 0;
					ALU_Op = 2;
				end

				4'b0110: //NOT
				begin
					Reg_Write = 1;
					Mem_Write = 0;
					Mem_To_Reg = 0;
					ALU_Op = 8;
				end

				4'b0111: //SHL
				begin
					Reg_Write = 1;
					Mem_Write = 0;
					Mem_To_Reg = 0;
					ALU_Op = 9;
				end

				4'b1000: //SHR
				begin
					Reg_Write = 1;
					Mem_Write = 0;
					Mem_To_Reg = 0;
					ALU_Op = 10;
				end

				4'b1001: //STEQI
				begin
					Reg_Write = 1;
					Mem_Write = 0;
					Mem_To_Reg = 0;
					ALU_Op = 11;
				end

				4'b1010: //STGTI
				begin
					Reg_Write = 1;
					Mem_Write = 0;
					Mem_To_Reg = 0;
					ALU_Op = 14;
				end

				4'b1011: //STLTI
				begin
					Reg_Write = 1;
					Mem_Write = 0;
					Mem_To_Reg = 0;
					ALU_Op = 16;
				end

				4'b1100: //STNEI
				begin
					Reg_Write = 1;
					Mem_Write = 0;
					Mem_To_Reg = 0;
					ALU_Op = 12;
				end

				4'b1101: //SUBI
				begin
					Reg_Write = 1;
					Mem_Write = 0;
					Mem_To_Reg = 0;
					ALU_Op = 1;
				end

				4'b1110: //SW
				begin
					Reg_Write = 0;
					Mem_Write = 1;
					Mem_To_Reg = 0;
					ALU_Op = 0;
				end
				
				default:
				begin
					Reg_Write = 0;
					Mem_Write = 0;
					Mem_To_Reg = 0;
					ALU_Op = 0;
				end


			endcase

		end

		default:
		begin

			IO_Enable = 0;
			IO_Selection = 0;
			Reg_Write = 0;
			Jump_R = 0;
			Jump_I = 0;
			Stack_Enable = 0;
			Stack_Write = 0;
			Branch = 0;
			Mem_Write = 0;
			Mem_To_Reg = 0;
			ALU_Op = 0;
			ALU_Src = 0;
			Halt = 0;
			Long_Imm = 0;
			
		end
	endcase
end


endmodule