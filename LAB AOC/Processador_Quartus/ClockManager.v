module ClockManager
#(parameter N_COUNT = 5)
(
	input Reset, Clk, Interrupt,
	output reg New_Clock
);

integer num = N_COUNT;
integer count = 0;

always@(posedge Clk or posedge Reset)
begin
	if (Reset)
	begin
		num <= N_COUNT;
		count <= 0;
	end
	else if (!Interrupt)
	begin		
		if (count<num)
		begin
			count = count + 1;
		end
		else begin
			count = 0;
			New_Clock = ~New_Clock;
		end
	end
end


endmodule
