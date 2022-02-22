module RegFile
(
    output signed [31:0] DebugSP,
    output signed [31:0] DebugGP,
    output signed [31:0] DebugJMP,
    output signed [31:0] DebugRA,
    output signed [31:0] DebugRET,
    output signed [31:0] DebugBR,
    output signed [31:0] DebugCTX,
    output signed [31:0] DebugAX1,
    output signed [31:0] DebugAX2,
    output signed [31:0] DebugCRT,
    input Reset,                //Makes sure Reg 0 is always 0
    input Slow_Clock,			  //Write Clock
    input Fast_Clock,
	input Reg_Write,            //Write to Reg Flag
    input signed [31:0] Write_Data,    //Data that will be written in the Reg selected by Reg_1
    input [5:0] Reg_1,          //First Register Selection (Read or Write)
    input [5:0] Reg_2,          //Second Register Selection (Read)
    input [5:0] Reg_3,         //Third Register Selection (Read)
    output signed [31:0] Data_1,   	  //Data that will outputted by the Reg selected by Reg_1
    output signed [31:0] Data_2,       //Data that will outputted by the Reg selected by Reg_2
    output signed [31:0] Data_3        //Data that will outputted by the Reg selected by Reg_3
);

reg [31:0] Aux_WD;
reg [5:0] Aux_Reg;
reg signed [31:0] RegBank[63:0];

assign Data_1 = RegBank[Reg_1];
assign Data_2 = RegBank[Reg_2];
assign Data_3 = RegBank[Reg_3];

assign DebugSP = RegBank[51];
assign DebugGP = RegBank[52];
assign DebugJMP = RegBank[53];
assign DebugRA = RegBank[54];
assign DebugRET = RegBank[55];
assign DebugBR = RegBank[56];
assign DebugCTX = RegBank[57];
assign DebugAX1 = RegBank[61];
assign DebugAX2 = RegBank[62];
assign DebugCRT = RegBank[63];

always @ (negedge Fast_Clock)
begin
	Aux_WD <= Write_Data;
	Aux_Reg <= Reg_1;
end

always @ (negedge Slow_Clock)
begin
	if (Reset)
	begin
		RegBank[0] <= {32{1'b0}};
	end
	else if (Reg_Write && (Aux_Reg != 6'b000000))
	begin
		RegBank[Aux_Reg] <= Aux_WD;
	end
end

endmodule