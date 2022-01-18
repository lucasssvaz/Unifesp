module ROM
#(parameter DATA_WIDTH=32, parameter ADDR_WIDTH=13)
(
	input [(ADDR_WIDTH-1):0] PC,
	input Sys_Clock, 
	output reg [(DATA_WIDTH-1):0] Instruction
);

	reg [DATA_WIDTH-1:0] rom[2**ADDR_WIDTH-1:0];

	initial
	begin
		$readmemb("single_port_rom_init.txt", rom);
	end

	always @ (posedge Sys_Clock)
	begin
		Instruction <= rom[PC];
	end

endmodule
