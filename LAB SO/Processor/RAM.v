module RAM
#(parameter DATA_WIDTH=32, parameter ADDR_WIDTH=16)
(
	input [(DATA_WIDTH-1):0] Write_Data,
	input [(ADDR_WIDTH-1):0] Address,
	input Mem_Write, Fast_Clock, Slow_Clock, Snapshot,
	input signed [32*64-1:0] RegBank,
	input [1:0] Proc_ID,
	input [6:0] Display0,
	input [6:0] Display1,
	input [6:0] Display2,
	input [6:0] Display3,
	input [6:0] Display4,
	input [6:0] Display5,
	input [6:0] Display6,
	input [6:0] Display7,
	output Update_PC,
	output reg [(DATA_WIDTH-1):0] Read_Data,
	output reg [32*72-1:0] Load_Data
);
	
	reg [DATA_WIDTH-1:0] ram[1023:0];

	wire [31:0] in_aux[63:0];

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
	} = RegBank;
	

	assign Load_Data = {
		ram[Proc_ID*256+71],
		ram[Proc_ID*256+70],
		ram[Proc_ID*256+69],
		ram[Proc_ID*256+68],
		ram[Proc_ID*256+67],
		ram[Proc_ID*256+66],
		ram[Proc_ID*256+65],
		ram[Proc_ID*256+64],
		ram[Proc_ID*256+63],
		ram[Proc_ID*256+62],
		ram[Proc_ID*256+61],
		ram[Proc_ID*256+60],
		ram[Proc_ID*256+59],
		ram[Proc_ID*256+58],
		ram[Proc_ID*256+57],
		ram[Proc_ID*256+56],
		ram[Proc_ID*256+55],
		ram[Proc_ID*256+54],
		ram[Proc_ID*256+53],
		ram[Proc_ID*256+52],
		ram[Proc_ID*256+51],
		ram[Proc_ID*256+50],
		ram[Proc_ID*256+49],
		ram[Proc_ID*256+48],
		ram[Proc_ID*256+47],
		ram[Proc_ID*256+46],
		ram[Proc_ID*256+45],
		ram[Proc_ID*256+44],
		ram[Proc_ID*256+43],
		ram[Proc_ID*256+42],
		ram[Proc_ID*256+41],
		ram[Proc_ID*256+40],
		ram[Proc_ID*256+39],
		ram[Proc_ID*256+38],
		ram[Proc_ID*256+37],
		ram[Proc_ID*256+36],
		ram[Proc_ID*256+35],
		ram[Proc_ID*256+34],
		ram[Proc_ID*256+33],
		ram[Proc_ID*256+32],
		ram[Proc_ID*256+31],
		ram[Proc_ID*256+30],
		ram[Proc_ID*256+29],
		ram[Proc_ID*256+28],
		ram[Proc_ID*256+27],
		ram[Proc_ID*256+26],
		ram[Proc_ID*256+25],
		ram[Proc_ID*256+24],
		ram[Proc_ID*256+23],
		ram[Proc_ID*256+22],
		ram[Proc_ID*256+21],
		ram[Proc_ID*256+20],
		ram[Proc_ID*256+19],
		ram[Proc_ID*256+18],
		ram[Proc_ID*256+17],
		ram[Proc_ID*256+16],
		ram[Proc_ID*256+15],
		ram[Proc_ID*256+14],
		ram[Proc_ID*256+13],
		ram[Proc_ID*256+12],
		ram[Proc_ID*256+11],
		ram[Proc_ID*256+10],
		ram[Proc_ID*256+9],
		ram[Proc_ID*256+8],
		ram[Proc_ID*256+7],
		ram[Proc_ID*256+6],
		ram[Proc_ID*256+5],
		ram[Proc_ID*256+4],
		ram[Proc_ID*256+3],
		ram[Proc_ID*256+2],
		ram[Proc_ID*256+1],
		ram[Proc_ID*256+0]
	};

	always @ (negedge Slow_Clock)
	begin

		Update_PC = 0;

		if (Mem_Write)
			ram[Address] = Write_Data;

		if (Snapshot)
		begin
			ram[Proc_ID*256+0] = in_aux[0];
			ram[Proc_ID*256+1] = in_aux[1];
			ram[Proc_ID*256+2] = in_aux[2];
			ram[Proc_ID*256+3] = in_aux[3];
			ram[Proc_ID*256+4] = in_aux[4];
			ram[Proc_ID*256+5] = in_aux[5];
			ram[Proc_ID*256+6] = in_aux[6];
			ram[Proc_ID*256+7] = in_aux[7];
			ram[Proc_ID*256+8] = in_aux[8];
			ram[Proc_ID*256+9] = in_aux[9];
			ram[Proc_ID*256+10] = in_aux[10];
			ram[Proc_ID*256+11] = in_aux[11];
			ram[Proc_ID*256+12] = in_aux[12];
			ram[Proc_ID*256+13] = in_aux[13];
			ram[Proc_ID*256+14] = in_aux[14];
			ram[Proc_ID*256+15] = in_aux[15];
			ram[Proc_ID*256+16] = in_aux[16];
			ram[Proc_ID*256+17] = in_aux[17];
			ram[Proc_ID*256+18] = in_aux[18];
			ram[Proc_ID*256+19] = in_aux[19];
			ram[Proc_ID*256+20] = in_aux[20];
			ram[Proc_ID*256+21] = in_aux[21];
			ram[Proc_ID*256+22] = in_aux[22];
			ram[Proc_ID*256+23] = in_aux[23];
			ram[Proc_ID*256+24] = in_aux[24];
			ram[Proc_ID*256+25] = in_aux[25];
			ram[Proc_ID*256+26] = in_aux[26];
			ram[Proc_ID*256+27] = in_aux[27];
			ram[Proc_ID*256+28] = in_aux[28];
			ram[Proc_ID*256+29] = in_aux[29];
			ram[Proc_ID*256+30] = in_aux[30];
			ram[Proc_ID*256+31] = in_aux[31];
			ram[Proc_ID*256+32] = in_aux[32];
			ram[Proc_ID*256+33] = in_aux[33];
			ram[Proc_ID*256+34] = in_aux[34];
			ram[Proc_ID*256+35] = in_aux[35];
			ram[Proc_ID*256+36] = in_aux[36];
			ram[Proc_ID*256+37] = in_aux[37];
			ram[Proc_ID*256+38] = in_aux[38];
			ram[Proc_ID*256+39] = in_aux[39];
			ram[Proc_ID*256+40] = in_aux[40];
			ram[Proc_ID*256+41] = in_aux[41];
			ram[Proc_ID*256+42] = in_aux[42];
			ram[Proc_ID*256+43] = in_aux[43];
			ram[Proc_ID*256+44] = in_aux[44];
			ram[Proc_ID*256+45] = in_aux[45];
			ram[Proc_ID*256+46] = in_aux[46];
			ram[Proc_ID*256+47] = in_aux[47];
			ram[Proc_ID*256+48] = in_aux[48];
			ram[Proc_ID*256+49] = in_aux[49];
			ram[Proc_ID*256+50] = in_aux[50];
			ram[Proc_ID*256+51] = in_aux[51];
			ram[Proc_ID*256+52] = in_aux[52];
			ram[Proc_ID*256+53] = in_aux[53];
			ram[Proc_ID*256+54] = in_aux[54];
			ram[Proc_ID*256+55] = in_aux[55];
			ram[Proc_ID*256+56] = in_aux[56];
			ram[Proc_ID*256+57] = in_aux[57];
			ram[Proc_ID*256+58] = in_aux[58];
			ram[Proc_ID*256+59] = in_aux[59];
			ram[Proc_ID*256+60] = in_aux[60];
			ram[Proc_ID*256+61] = in_aux[61];
			ram[Proc_ID*256+62] = in_aux[62];
			ram[Proc_ID*256+63] = in_aux[63];

			ram[Proc_ID*256+64] = {{25{1'b0}},Display0};
			ram[Proc_ID*256+65] = {{25{1'b0}},Display1};
			ram[Proc_ID*256+66] = {{25{1'b0}},Display2};
			ram[Proc_ID*256+67] = {{25{1'b0}},Display3};
			ram[Proc_ID*256+68] = {{25{1'b0}},Display4};
			ram[Proc_ID*256+69] = {{25{1'b0}},Display5};
			ram[Proc_ID*256+70] = {{25{1'b0}},Display6};
			ram[Proc_ID*256+71] = {{25{1'b0}},Display7};

			Update_PC = 1;
			
		end
	end
	
	always @ (negedge Fast_Clock)
	begin
		// Read 
		Read_Data <= ram[Address];
	end

endmodule
