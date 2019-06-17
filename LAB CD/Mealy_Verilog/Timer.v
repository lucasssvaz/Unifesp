module Timer(input sysclock, output reg new_clock);

reg [25:0] count;
parameter num = 50000000;

initial begin
	count = 0;
end

always@(posedge sysclock)
begin
	if (count<num-1)
	begin
		count = count + 1;
	end
	else begin
		count = 0;
		new_clock = ~new_clock;
	end
end


endmodule
