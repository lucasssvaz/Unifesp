module Program_Counter
(
	input Interrupt, Reset, Slow_Clock, Halt,
	input [1:0] Proc_ID,
	input [12:0] NextPC, 
	output reg [12:0] PC
);

reg Lock = 0;

always @ (Halt)
begin
	if (Halt && (Proc_ID == 0))
		Lock = 1;
	else
		Lock = 0;
end

always @(posedge Slow_Clock)
begin
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