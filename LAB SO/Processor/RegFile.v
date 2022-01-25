module RegFile
(
	output signed [31:0] Data_1,   	  //Data that will outputted by the Reg selected by Reg_1
	output signed [31:0] Data_2,       //Data that will outputted by the Reg selected by Reg_2
	output signed [31:0] Data_3,        //Data that will outputted by the Reg selected by Reg_3
	output signed [32*64-1:0] Save_Data,
	input Reset,                //Makes sure Reg 0 is always 0
	input Slow_Clock,			  //Write Clock
	input Fast_Clock,
	input Load_Proc,
	input Reg_Write,            //Write to Reg Flag
	input signed [31:0] Write_Data,    //Data that will be written in the Reg selected by Reg_1
	input [5:0] Reg_1,          //First Register Selection (Read or Write)
	input [5:0] Reg_2,          //Second Register Selection (Read)
	input [5:0] Reg_3,         //Third Register Selection (Read)
	input [32*64-1:0] Load_Data
);

reg [31:0] Aux_WD;
reg [5:0] Aux_Reg;
reg signed [31:0] RegBank[63:0];

wire [31:0] in_aux[63:0];

assign Save_Data = {
	RegBank[63],
	RegBank[62],
	RegBank[61],
	RegBank[60],
	RegBank[59],
	RegBank[58],
	RegBank[57],
	RegBank[56],
	RegBank[55],
	RegBank[54],
	RegBank[53],
	RegBank[52],
	RegBank[51],
	RegBank[50],
	RegBank[49],
	RegBank[48],
	RegBank[47],
	RegBank[46],
	RegBank[45],
	RegBank[44],
	RegBank[43],
	RegBank[42],
	RegBank[41],
	RegBank[40],
	RegBank[39],
	RegBank[38],
	RegBank[37],
	RegBank[36],
	RegBank[35],
	RegBank[34],
	RegBank[33],
	RegBank[32],
	RegBank[31],
	RegBank[30],
	RegBank[29],
	RegBank[28],
	RegBank[27],
	RegBank[26],
	RegBank[25],
	RegBank[24],
	RegBank[23],
	RegBank[22],
	RegBank[21],
	RegBank[20],
	RegBank[19],
	RegBank[18],
	RegBank[17],
	RegBank[16],
	RegBank[15],
	RegBank[14],
	RegBank[13],
	RegBank[12],
	RegBank[11],
	RegBank[10],
	RegBank[9],
	RegBank[8],
	RegBank[7],
	RegBank[6],
	RegBank[5],
	RegBank[4],
	RegBank[3],
	RegBank[2],
	RegBank[1],
	RegBank[0]
};

assign {
	in_aux[63],
	in_aux[62],
	in_aux[61],
	in_aux[60],
	in_aux[59],
	in_aux[58],
	in_aux[57],
	in_aux[56],
	in_aux[55],
	in_aux[54],
	in_aux[53],
	in_aux[52],
	in_aux[51],
	in_aux[50],
	in_aux[49],
	in_aux[48],
	in_aux[47],
	in_aux[46],
	in_aux[45],
	in_aux[44],
	in_aux[43],
	in_aux[42],
	in_aux[41],
	in_aux[40],
	in_aux[39],
	in_aux[38],
	in_aux[37],
	in_aux[36],
	in_aux[35],
	in_aux[34],
	in_aux[33],
	in_aux[32],
	in_aux[31],
	in_aux[30],
	in_aux[29],
	in_aux[28],
	in_aux[27],
	in_aux[26],
	in_aux[25],
	in_aux[24],
	in_aux[23],
	in_aux[22],
	in_aux[21],
	in_aux[20],
	in_aux[19],
	in_aux[18],
	in_aux[17],
	in_aux[16],
	in_aux[15],
	in_aux[14],
	in_aux[13],
	in_aux[12],
	in_aux[11],
	in_aux[10],
	in_aux[9],
	in_aux[8],
	in_aux[7],
	in_aux[6],
	in_aux[5],
	in_aux[4],
	in_aux[3],
	in_aux[2],
	in_aux[1],
	in_aux[0]
} = Load_Data;

assign Data_1 = RegBank[Reg_1];
assign Data_2 = RegBank[Reg_2];
assign Data_3 = RegBank[Reg_3];

always @ (negedge Fast_Clock)
begin
	Aux_WD <= Write_Data;
	Aux_Reg <= Reg_1;
end

always @ (negedge Slow_Clock or posedge Load_Proc or posedge Reset)
begin
	if (Reset)
	begin
		RegBank[0] <= {32{1'b0}};
	end
	else if (Load_Proc)
	begin
		RegBank[63:0] <= in_aux[63:0];
	end
	else if (Reg_Write && (Aux_Reg != 6'b000000))
	begin
		RegBank[Aux_Reg] <= Aux_WD;
	end
end

endmodule