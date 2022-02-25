module ClockManager
#(parameter N_COUNT = 2500) //If N_COUNT is too low, the program might not work on the physical board
(
	input Reset, Fast_Clock,
	output reg Slow_Clock
);

initial
begin
	Slow_Clock = 1;
end

integer count = 0;

always@(posedge Fast_Clock)
begin
	if (Reset)
	begin
		count <= 0;
		Slow_Clock <= 1;
	end
	else
	begin		
		if (count<N_COUNT)
		begin
			count <= count + 1;
		end
		else begin
			count <= 0;
			Slow_Clock <= ~Slow_Clock;
		end
	end
end


endmodule
