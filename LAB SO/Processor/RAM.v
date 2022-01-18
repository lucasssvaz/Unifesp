module RAM
#(parameter DATA_WIDTH=32, parameter ADDR_WIDTH=16)
(
	input [(DATA_WIDTH-1):0] Write_Data,
	input [(ADDR_WIDTH-1):0] Address,
	input Mem_Write, Fast_Clock, Slow_Clock,
	output reg [(DATA_WIDTH-1):0] Read_Data
);
	
	reg [DATA_WIDTH-1:0] ram[2**ADDR_WIDTH-1:0];
	
	always @ (negedge Slow_Clock)
	begin
		// Write
		if (Mem_Write)
			ram[Address] = Write_Data;
	end
	
	always @ (negedge Fast_Clock)
	begin
		// Read 
		Read_Data = ram[Address];
	end
	
endmodule
