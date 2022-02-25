module RegFile
(
    output signed [31:0] DebugZERO,
    output signed [31:0] DebugT0,
    output signed [31:0] DebugT1,
    output signed [31:0] DebugT2,
    output signed [31:0] DebugT3,
    output signed [31:0] DebugT4,
    output signed [31:0] DebugT5,
    output signed [31:0] DebugT6,
    output signed [31:0] DebugT7,
    output signed [31:0] DebugT8,
    output signed [31:0] DebugT9,
    output signed [31:0] DebugT10,
    output signed [31:0] DebugT11,
    output signed [31:0] DebugT12,
    output signed [31:0] DebugT13,
    output signed [31:0] DebugT14,
    output signed [31:0] DebugT15,
    output signed [31:0] DebugT16,
    output signed [31:0] DebugT17,
    output signed [31:0] DebugT18,
    output signed [31:0] DebugT19,
    output signed [31:0] DebugT20,
    output signed [31:0] DebugT21,
    output signed [31:0] DebugT22,
    output signed [31:0] DebugT23,
    output signed [31:0] DebugT24,
    output signed [31:0] DebugT25,
    output signed [31:0] DebugT26,
    output signed [31:0] DebugT27,
    output signed [31:0] DebugT28,
    output signed [31:0] DebugT29,
    output signed [31:0] DebugT30,
    output signed [31:0] DebugT31,
    output signed [31:0] DebugT32,
    output signed [31:0] DebugT33,
    output signed [31:0] DebugT34,
    output signed [31:0] DebugT35,
    output signed [31:0] DebugT36,
    output signed [31:0] DebugT37,
    output signed [31:0] DebugT38,
    output signed [31:0] DebugT39,
    output signed [31:0] DebugR0,
    output signed [31:0] DebugR1,
    output signed [31:0] DebugR2,
    output signed [31:0] DebugR3,
    output signed [31:0] DebugR4,
    output signed [31:0] DebugR5,
    output signed [31:0] DebugR6,
    output signed [31:0] DebugR7,
    output signed [31:0] DebugR8,
    output signed [31:0] DebugR9,
    output signed [31:0] DebugSP,
    output signed [31:0] DebugGP,
    output signed [31:0] DebugJMP,
    output signed [31:0] DebugRA,
    output signed [31:0] DebugRET,
    output signed [31:0] DebugBR,
    output signed [31:0] DebugCTX,
    output signed [31:0] DebugK7,
    output signed [31:0] DebugK8,
    output signed [31:0] DebugK9,
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

assign DebugZERO = RegBank[0];
assign DebugT0 = RegBank[1];
assign DebugT1 = RegBank[2];
assign DebugT2 = RegBank[3];
assign DebugT3 = RegBank[4];
assign DebugT4 = RegBank[5];
assign DebugT5 = RegBank[6];
assign DebugT6 = RegBank[7];
assign DebugT7 = RegBank[8];
assign DebugT8 = RegBank[9];
assign DebugT9 = RegBank[10];
assign DebugT10 = RegBank[11];
assign DebugT11 = RegBank[12];
assign DebugT12 = RegBank[13];
assign DebugT13 = RegBank[14];
assign DebugT14 = RegBank[15];
assign DebugT15 = RegBank[16];
assign DebugT16 = RegBank[17];
assign DebugT17 = RegBank[18];
assign DebugT18 = RegBank[19];
assign DebugT19 = RegBank[20];
assign DebugT20 = RegBank[21];
assign DebugT21 = RegBank[22];
assign DebugT22 = RegBank[23];
assign DebugT23 = RegBank[24];
assign DebugT24 = RegBank[25];
assign DebugT25 = RegBank[26];
assign DebugT26 = RegBank[27];
assign DebugT27 = RegBank[28];
assign DebugT28 = RegBank[29];
assign DebugT29 = RegBank[30];
assign DebugT30 = RegBank[31];
assign DebugT31 = RegBank[32];
assign DebugT32 = RegBank[33];
assign DebugT33 = RegBank[34];
assign DebugT34 = RegBank[35];
assign DebugT35 = RegBank[36];
assign DebugT36 = RegBank[37];
assign DebugT37 = RegBank[38];
assign DebugT38 = RegBank[39];
assign DebugT39 = RegBank[40];
assign DebugR0 = RegBank[41];
assign DebugR1 = RegBank[42];
assign DebugR2 = RegBank[43];
assign DebugR3 = RegBank[44];
assign DebugR4 = RegBank[45];
assign DebugR5 = RegBank[46];
assign DebugR6 = RegBank[47];
assign DebugR7 = RegBank[48];
assign DebugR8 = RegBank[49];
assign DebugR9 = RegBank[50];
assign DebugSP = RegBank[51];
assign DebugGP = RegBank[52];
assign DebugJMP = RegBank[53];
assign DebugRA = RegBank[54];
assign DebugRET = RegBank[55];
assign DebugBR = RegBank[56];
assign DebugCTX = RegBank[57];
assign DebugK7 = RegBank[58];
assign DebugK8 = RegBank[59];
assign DebugK9 = RegBank[60];
assign DebugAX1 = RegBank[61];
assign DebugAX2 = RegBank[62];
assign DebugCRT = RegBank[63];

initial 
begin
    RegBank[0] <= 0;
    RegBank[1] <= 0;
    RegBank[2] <= 0;
    RegBank[3] <= 0;
    RegBank[4] <= 0;
    RegBank[5] <= 0;
    RegBank[6] <= 0;
    RegBank[7] <= 0;
    RegBank[8] <= 0;
    RegBank[9] <= 0;
    RegBank[10] <= 0;
    RegBank[11] <= 0;
    RegBank[12] <= 0;
    RegBank[13] <= 0;
    RegBank[14] <= 0;
    RegBank[15] <= 0;
    RegBank[16] <= 0;
    RegBank[17] <= 0;
    RegBank[18] <= 0;
    RegBank[19] <= 0;
    RegBank[20] <= 0;
    RegBank[21] <= 0;
    RegBank[22] <= 0;
    RegBank[23] <= 0;
    RegBank[24] <= 0;
    RegBank[25] <= 0;
    RegBank[26] <= 0;
    RegBank[27] <= 0;  
    RegBank[28] <= 0;  
    RegBank[29] <= 0;  
    RegBank[30] <= 0;  
    RegBank[31] <= 0;  
    RegBank[32] <= 0;  
    RegBank[33] <= 0;  
    RegBank[34] <= 0;  
    RegBank[35] <= 0;  
    RegBank[36] <= 0;  
    RegBank[37] <= 0;  
    RegBank[38] <= 0;  
    RegBank[39] <= 0;  
    RegBank[40] <= 0;  
    RegBank[41] <= 0;  
    RegBank[42] <= 0;  
    RegBank[43] <= 0;  
    RegBank[44] <= 0;  
    RegBank[45] <= 0;  
    RegBank[46] <= 0;  
    RegBank[47] <= 0;  
    RegBank[48] <= 0;  
    RegBank[49] <= 0;  
    RegBank[50] <= 0;  
    RegBank[51] <= 0;  
    RegBank[52] <= 0;  
    RegBank[53] <= 0;  
    RegBank[54] <= 0;  
    RegBank[55] <= 0;  
    RegBank[56] <= 0;  
    RegBank[57] <= 0;  
    RegBank[58] <= 0;  
    RegBank[59] <= 0;  
    RegBank[60] <= 0;  
    RegBank[61] <= 0;  
    RegBank[62] <= 0;  
    RegBank[63] <= 0;
end

always @ (negedge Fast_Clock)
begin
	Aux_WD <= Write_Data;
	Aux_Reg <= Reg_1;
end

always @ (negedge Slow_Clock)
begin
	if (Reset)
	begin
        RegBank[0] <= 0;
        RegBank[1] <= 0;
        RegBank[2] <= 0;
        RegBank[3] <= 0;
        RegBank[4] <= 0;
        RegBank[5] <= 0;
        RegBank[6] <= 0;
        RegBank[7] <= 0;
        RegBank[8] <= 0;
        RegBank[9] <= 0;
        RegBank[10] <= 0;
        RegBank[11] <= 0;
        RegBank[12] <= 0;
        RegBank[13] <= 0;
        RegBank[14] <= 0;
        RegBank[15] <= 0;
        RegBank[16] <= 0;
        RegBank[17] <= 0;
        RegBank[18] <= 0;
        RegBank[19] <= 0;
        RegBank[20] <= 0;
        RegBank[21] <= 0;
        RegBank[22] <= 0;
        RegBank[23] <= 0;
        RegBank[24] <= 0;
        RegBank[25] <= 0;
        RegBank[26] <= 0;
        RegBank[27] <= 0;  
        RegBank[28] <= 0;  
        RegBank[29] <= 0;  
        RegBank[30] <= 0;  
        RegBank[31] <= 0;  
        RegBank[32] <= 0;  
        RegBank[33] <= 0;  
        RegBank[34] <= 0;  
        RegBank[35] <= 0;  
        RegBank[36] <= 0;  
        RegBank[37] <= 0;  
        RegBank[38] <= 0;  
        RegBank[39] <= 0;  
        RegBank[40] <= 0;  
        RegBank[41] <= 0;  
        RegBank[42] <= 0;  
        RegBank[43] <= 0;  
        RegBank[44] <= 0;  
        RegBank[45] <= 0;  
        RegBank[46] <= 0;  
        RegBank[47] <= 0;  
        RegBank[48] <= 0;  
        RegBank[49] <= 0;  
        RegBank[50] <= 0;  
        RegBank[51] <= 0;  
        RegBank[52] <= 0;  
        RegBank[53] <= 0;  
        RegBank[54] <= 0;  
        RegBank[55] <= 0;  
        RegBank[56] <= 0;  
        RegBank[57] <= 0;  
        RegBank[58] <= 0;  
        RegBank[59] <= 0;  
        RegBank[60] <= 0;  
        RegBank[61] <= 0;  
        RegBank[62] <= 0;  
        RegBank[63] <= 0;
	end
	else if (Reg_Write && (Aux_Reg != 6'b000000))
	begin
		RegBank[Aux_Reg] <= Aux_WD;
	end
end

endmodule