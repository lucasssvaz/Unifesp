module Program_Counter (input Reset, input Sys_Clock, input Halt, input [7:0] NextPC, output reg [7:0] PC);

always @(posedge Sys_Clock or posedge Reset) begin
	if (Reset)
	begin
		PC <= 0;
	end
	else if (!Halt) 
	begin
		PC <= NextPC[7:0];
	end
end


endmodule