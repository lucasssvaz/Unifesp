module Second(sys_clk_i, b_clk);
	input sys_clk_i;
	output b_clk;
	reg [26:0] d;
	wire [26:0] dInc = d[26] ? (1) : (1 - 50000000);
	wire [26:0] dN = d + dInc;
	always @(posedge sys_clk_i)
	begin
		d = dN;
	end
	wire b_clk = ~d[26];
	
endmodule