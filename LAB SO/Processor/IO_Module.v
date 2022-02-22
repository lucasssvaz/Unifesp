module IO_Module (
	input Slow_Clock,
	input Reset, 
	input Enable, 
	input IO, 
	input Confirm, 
	output reg signed [31:0] Data_In, 
	input signed [31:0] Data_Out, 
	output reg signed [31:0] Data_Debug, 
	input signed [17:0] Raw_Input, 
	output reg Interrupt, 
	output reg [6:0] Display0, 
	output reg [6:0] Display1, 
	output reg [6:0] Display2, 
	output reg [6:0] Display3, 
	output reg [6:0] Display4, 
	output reg [6:0] Display5, 
	output reg [6:0] Display6, 
	output reg [6:0] Display7
);

reg State = 0;
wire In_Op;
wire Out_Op;

assign Out_Op = (Enable & IO);
assign In_Op = (Enable & (~IO));

always @ (Data_Out)
begin
	Data_Debug <= Data_Out;
end

task To_Display;

	input [3:0] Bin;
	output [6:0] Disp_Hex;

	case (Bin)
		0: Disp_Hex <= 7'b100_0000;
		1: Disp_Hex <= 7'b111_1001;
		2: Disp_Hex <= 7'b010_0100;
		3: Disp_Hex <= 7'b011_0000;
		4: Disp_Hex <= 7'b001_1001;
		5: Disp_Hex <= 7'b001_0010;
		6: Disp_Hex <= 7'b000_0010;
		7: Disp_Hex <= 7'b111_1000;
		8: Disp_Hex <= 7'b000_0000;
		9: Disp_Hex <= 7'b001_0000;
		10: Disp_Hex <= 7'b000_1000;
		11: Disp_Hex <= 7'b000_0011;
		12: Disp_Hex <= 7'b100_0110;
		13: Disp_Hex <= 7'b010_0001;
		14: Disp_Hex <= 7'b000_0110;
		15: Disp_Hex <= 7'b000_1110;
		default: Disp_Hex <= 7'b111_1111;

	endcase

endtask

always @ (negedge Confirm)
begin
	if (Enable && (!IO))
	begin
		Data_In = {{14{Raw_Input[17]}},Raw_Input};
	end
end

always @ (negedge Slow_Clock)
begin
	if (Reset)
	begin
		Interrupt = 0;
		State = 0;
	end
	else if (In_Op)
	begin
		if (!State && !Confirm)
		begin
			Interrupt = 1;
			State = 0;
		end
		else if (!State && Confirm)
		begin
			Interrupt = 1;
			State = 1;
		end
		else if (State && !Confirm)
		begin
			Interrupt = 0;
			State = 0;
		end
		else if (State && Confirm)
		begin
			Interrupt = 1;
			State = 1;
		end
	end
end


always @ (negedge Slow_Clock or posedge Reset)
begin
	if (Reset)
	begin
		Display0 <= 7'b100_0000;
		Display1 <= 7'b100_0000;
		Display2 <= 7'b100_0000;
		Display3 <= 7'b100_0000;
		Display4 <= 7'b100_0000;
		Display5 <= 7'b100_0000;
		Display6 <= 7'b100_0000;
		Display7 <= 7'b100_0000;
	end
	else if (Out_Op)	//WRITE OUTPUT
	begin
		To_Display(Data_Out[31:28], Display7);
		To_Display(Data_Out[27:24], Display6);
		To_Display(Data_Out[23:20], Display5);
		To_Display(Data_Out[19:16], Display4);
		To_Display(Data_Out[15:12], Display3);
		To_Display(Data_Out[11:8], Display2);
		To_Display(Data_Out[7:4], Display1);
		To_Display(Data_Out[3:0], Display0);
	end
end


endmodule