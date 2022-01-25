module Reaper_Processor
(
	input Raw_Button_I,
	input signed [17:0] Raw_Input,
	input Fast_Clock,
	input Raw_Reset_I,
	output [6:0] Display0,
	output [6:0] Display1,
	output [6:0] Display2,
	output [6:0] Display3,
	output [6:0] Display4,
	output [6:0] Display5,
	output [6:0] Display6,
	output [6:0] Display7,
	output Err_Out,
	output signed [31:0] DebugSP,
	output signed [31:0] DebugGP,
	output signed [31:0] DebugJMP,
	output signed [31:0] DebugRA,
	output signed [31:0] DebugRET,
	output signed [31:0] DebugBR,
	output signed [31:0] Out_Int,
	output [12:0] PC,
	output [31:0] Instruction,
	output Slow_Clock,
	output reg [1:0] Proc_ID
);


//==============================================================

//reg [1:0] Proc_ID;
reg [12:0] NextPC;
reg [12:0] NextPC_Mux;
reg [12:0] NPPC;
reg OR_Branch;
reg Stack_Mux_Control;
wire [12:0] Branch_Out;
wire [12:0] Jump_Out;
wire [12:0] Ret_Add;
wire [4:0] ALU_Op;
wire ALU_Src;
wire ALU_True;
wire Branch;
wire Button;
wire Exec_Proc;
wire Halt;
wire Interrupt;
wire IO_Enable;
wire IO_Selection;
wire Jump_I;
wire Jump_R;
wire Load_Proc;
wire Long_Imm;
wire Mem_To_Reg;
wire Mem_Write;
wire Raw_Button;
wire Raw_Reset;
wire Reg_Write;
wire Reset;
wire signed [31:0] ALU_Data_3;
wire signed [31:0] ALU_Result;
wire signed [31:0] Data_1;
wire signed [31:0] Data_2;
wire signed [31:0] Data_3;
wire signed [31:0] Data_From_Mem;
wire signed [31:0] Data_In;
wire signed [31:0] Data_To_Reg;
wire signed [32*72-1:0] Load_Data; 
wire signed [31:0] Mem_Out;
wire signed [31:0] Out_Imm;
wire signed [31:0] Reg_Write_Data;
wire signed [32*64-1:0] Save_Data;
wire Snapshot;
wire Stack_Enable;
wire Stack_Write;
wire Update_PC;

initial
begin
	Proc_ID = 0;
	Snapshot = 0;
	Update_PC = 0;
	Load_Proc = 0;
end

assign Reset = ~Raw_Reset_I;
assign Button = ~Raw_Button_I;

assign DebugSP = Save_Data[52*32-1:51*32];
assign DebugGP = Save_Data[53*32-1:52*32];
assign DebugJMP = Save_Data[54*32-1:53*32];
assign DebugRA = Save_Data[55*32-1:54*32];
assign DebugRET = Save_Data[56*32-1:55*32];
assign DebugBR = Save_Data[57*32-1:56*32];

//======================================================================================


always @ (PC)
begin
	NPPC <= PC + 13'b1;
end

always @ (Branch or Jump_R or ALU_True)
begin
	OR_Branch <= (Branch & ALU_True) | Jump_R;
end

always @ (Stack_Enable or Stack_Write)
begin
	Stack_Mux_Control <= Stack_Enable & !(Stack_Write);
end


//======================================================================================

Program_Counter Program_Counter0 
(
	.Interrupt(Interrupt),
	.Reset(Reset),
	.Slow_Clock(Slow_Clock),
	.Halt(Halt),
	.NextPC(NextPC),
	.PC(PC),
	.Proc_ID(Proc_ID)
);

Instruction_Memory IM0 
(
	.PC(PC),
	.Fast_Clock(Fast_Clock),
	.Instruction(Instruction)
);

ExecManager ExecManager0
(
	.Exec_Proc(Exec_Proc), 
	.Update_PC(Update_PC), 
	.Halt(Halt),
	.Next_PC(NextPC),
	.New_PC(New_PC),
	.Reset(Reset),
	.Snapshot(Snapshot), 
	.Load_Proc(Load_Proc), 
	.Proc_ID(Proc_ID),
	.Fast_Clock(Fast_Clock),
	.Slow_Clock(Slow_Clock),
	.Data1(Data_1)
);

Ctrl_Module Ctrl_Module0 
(
	.Instruction(Instruction[31:26]),
	.IO_Enable(IO_Enable), 
	.IO_Selection(IO_Selection), 
	.Reg_Write(Reg_Write), 
	.Jump_R(Jump_R), 
	.Jump_I(Jump_I), 
	.Stack_Enable(Stack_Enable), 
	.Stack_Write(Stack_Write), 
	.Branch(Branch), 
	.Mem_Write(Mem_Write), 
	.Mem_To_Reg(Mem_To_Reg), 
	.ALU_Op(ALU_Op), 
	.ALU_Src(ALU_Src), 
	.Halt(Halt), 
	.Long_Imm(Long_Imm),
	.Exec_Proc(Exec_Proc)
);

RegFile RegFile0 
(
	.Reset(Reset), 
	.Slow_Clock(Slow_Clock), 
	.Fast_Clock(Fast_Clock), 
	.Reg_Write(Reg_Write), 
	.Write_Data(Reg_Write_Data), 
	.Reg_1(Instruction[25:20]), 
	.Reg_2(Instruction[19:14]), 
	.Reg_3(Instruction[13:8]), 
	.Data_1(Data_1), 
	.Data_2(Data_2), 
	.Data_3(Data_3),
	.Load_Proc(Load_Proc),
	.Load_Data(Load_Data[32*64-1:0]),
	.Save_Data(Save_Data)
);

Extend_Imm Extend_Imm0 
(
	.In_Imm(Instruction[19:0]), 
	.Long_Imm(Long_Imm), 
	.Out_Imm(Out_Imm)
);

ALU ALU0 
(
	.True(ALU_True), 
	.Result(ALU_Result), 
	.Fast_Clock(Fast_Clock), 
	.Op1(Data_2), 
	.Op2(ALU_Data_3), 
	.ALU_Op(ALU_Op)
);

Mux32 Mux_ALU 
(
	.Switch(ALU_Src), 
	.Data_0(Data_3), 
	.Data_1(Out_Imm), 
	.Data_Out(ALU_Data_3)
);

StackFile StackFile0 
(
	.Reset(Reset), 
	.Slow_Clock(Slow_Clock), 
	.Stack_Write(Stack_Write), 
	.Stack_Enable(Stack_Enable), 
	.NPPC(NPPC), 
	.Ret_Add(Ret_Add), 
	.Err_Out(Err_Out)
);

RAM RAM0 
(
	.Write_Data(Data_1), 
	.Address(ALU_Result[15:0]), 
	.Mem_Write(Mem_Write), 
	.Fast_Clock(Fast_Clock), 
	.Slow_Clock(Slow_Clock), 
	.Snapshot(Snapshot),
	.Update_PC(Update_PC), 
	.Proc_ID(Proc_ID),
	.RegBank(Save_Data),
	.Read_Data(Mem_Out),
	.Display0(Display0),
	.Display1(Display1),
	.Display2(Display2),
	.Display3(Display3),
	.Display4(Display4),
	.Display5(Display5),
	.Display6(Display6),
	.Display7(Display7),
	.Load_Data(Load_Data)
);

Mux32 Mux_Mem 
(
	.Switch(Mem_To_Reg),
	.Data_0(ALU_Result), 
	.Data_1(Mem_Out), 
	.Data_Out(Data_From_Mem)
);

IO_Module IO_Module0 
(
	.Slow_Clock(Slow_Clock), 
	.Reset(Reset), 
	.Enable(IO_Enable), 
	.IO(IO_Selection), 
	.Confirm(Button), 
	.Data_In(Data_In), 
	.Data_Out(Data_1), 
	.Data_Debug(Out_Int), 
	.Raw_Input(Raw_Input), 
	.Interrupt(Interrupt), 
	.Display0(Display0),
	.Display1(Display1),
	.Display2(Display2),
	.Display3(Display3),
	.Display4(Display4),
	.Display5(Display5),
	.Display6(Display6),
	.Display7(Display7),
	.Load_Data(Load_Data[32*72-1:32*64]),
	.Load_Proc(Load_Proc)
);

Mux32 Mux_IO 
(
	.Switch(IO_Enable), 
	.Data_0(Data_From_Mem), 
	.Data_1(Data_In), 
	.Data_Out(Reg_Write_Data)
);

Mux13 Mux_Branch 
(
	.Switch(OR_Branch), 
	.Data_0(NPPC), 
	.Data_1(Data_1[12:0]), 
	.Data_Out(Branch_Out)
);

Mux13 Mux_Jump 
(
	.Switch(Jump_I),
	.Data_0(Branch_Out),
	.Data_1(Out_Imm[12:0]),
	.Data_Out(Jump_Out)
);

Mux13 Mux_Stack 
(
	.Switch(Stack_Mux_Control), 
	.Data_0(Jump_Out), 
	.Data_1(Ret_Add), 
	.Data_Out(NextPC_Mux)
);

Mux13 Mux_Proc 
(
	.Switch(Snapshot), 
	.Data_0(NextPC_Mux), 
	.Data_1(New_PC), 
	.Data_Out(NextPC)
);

/*
Debounce DB0 
(
	Fast_Clock, 
	0, 
	Raw_Button, 
	Button
);

Debounce DB1 
(
	Fast_Clock, 
	0, 
	Raw_Reset, 
	Reset
);

assign Reg_Write_Data = Data_From_Mem;
*/

endmodule