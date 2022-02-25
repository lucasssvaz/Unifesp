module Program_Counter (
	input Interrupt, 
	input Reset, 
	input Slow_Clock, 
	input Halt, 
	input [12:0] NextPC, 
	output reg [12:0] PC
);

reg Lock = 0;

always @ (Halt)
begin
	if (Halt)
		Lock = 1;
	else
		Lock = 0;
end

always @(posedge Slow_Clock) begin
	if (Reset)
	begin
		PC = 0;
	end
	else if (!Lock && !Interrupt) 
	begin
		PC = NextPC[12:0];
	end
end


endmodule