module Reaper_Processor
(
	input Button,
	input [17:0] Raw_Input,
	input Sys_Clock,
	input Reset_Raw,
	output [6:0] Display0,
	output [6:0] Display1,
	output [6:0] Display2,
	output [6:0] Display3,
	output [6:0] Display4,
	output [6:0] Display5,
	output [6:0] Display6,
	output [6:0] Display7,
	output Err_Out
);


//==============================================================


reg [7:0] NPPC;
wire Clock;
wire Halt;
wire [7:0] NextPC;
wire [7:0] PC;
wire [31:0] Instruction;
wire Interrupt;
wire IO_Enable;
wire IO_Selection;
wire Reg_Write;
wire R_Type;
wire Jump;
wire Stack_Enable;
wire Stack_Write;
wire Branch;
wire Mem_Write;
wire W_Only;
wire Mem_To_Reg;
wire [4:0] ALU_Op;
wire ALU_Src;
wire Long_Imm;
wire [5:0] Mux_RT_Out;
wire [5:0] Mux_WO_Out;
wire [31:0] Reg_Write_Data;
wire [31:0] Data_1;
wire [31:0] Data_2;
wire [31:0] Data_3;
wire [31:0] Out_Imm;
wire [31:0] Data_To_Reg;
wire [31:0] Data_In;
wire [31:0] Data_From_Mem;
wire [7:0] Ret_Add;
wire ALU_True;
wire [31:0] ALU_Result;
wire [31:0] ALU_Data_2;
wire DB_Button;
reg AND_Branch;
wire Branch_Out;
wire Jump_Out;
reg Stack_Mux_Control;
wire [31:0] Mem_Out;
wire [31:0] Debug;
wire Reset;


//======================================================================================


always @ (PC)
begin
	NPPC <= PC + 1;
end

always @ (Branch or ALU_True)
begin
	AND_Branch <= Branch & ALU_True;
end

always @ (Stack_Enable or Stack_Write)
begin
	Stack_Mux_Control <= Stack_Enable & !(Stack_Write);
end


//======================================================================================


endmodule