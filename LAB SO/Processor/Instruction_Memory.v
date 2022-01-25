module Instruction_Memory
#(parameter DATA_WIDTH=32, parameter ADDR_WIDTH=13)
(
	input [(ADDR_WIDTH-1):0] PC,
	input Fast_Clock, 
	output reg [(DATA_WIDTH-1):0] Instruction
);

	reg [DATA_WIDTH-1:0] rom[2047:0];

	initial
	begin
		$readmemb("SO.txt", rom, 0, 511);
		$readmemb("Prog1.txt", rom, 512, 1023);
		$readmemb("Prog2.txt", rom, 1024, 1535);
		$readmemb("Prog3.txt", rom, 1536, 2047);
	end

	always @ (posedge Fast_Clock)
	begin
		Instruction <= rom[PC];
	end

endmodule
