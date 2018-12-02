module Timer(input sysclock, output reg new_clock);

integer num;
reg [25:0] count;

initial begin
	num = 50000000;
	count = 0;
end

always@(posedge sysclock)
begin
	if (count<num)
	begin
		count = count + 1;
	end
	else begin
		count = 0;
		new_clock = ~new_clock;
	end
end


endmodule
