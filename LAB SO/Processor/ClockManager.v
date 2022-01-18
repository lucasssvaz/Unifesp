module ClockManager
#(parameter N_COUNT = 250000)
(
	input Reset, Clk,
	output reg New_Clock
);

initial
begin
	New_Clock = 1;
end

integer count = 0;

always@(posedge Clk)
begin
	if (Reset)
	begin
		count <= 0;
		New_Clock <= 1;
	end
	else
	begin		
		if (count<N_COUNT)
		begin
			count <= count + 1;
		end
		else begin
			count <= 0;
			New_Clock <= ~New_Clock;
		end
	end
end


endmodule
