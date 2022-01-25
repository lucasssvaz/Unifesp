module ExecManager
#(parameter CLOCK_COUNT = 250000, parameter INST_COUNT = 100)
(
	input Reset, Fast_Clock, Exec_Proc, Update_PC, Halt,
	input reg [12:0] Next_PC,
	input [31:0] Data1,
	output reg [12:0] New_PC,
	output reg Slow_Clock, Snapshot, Load_Proc,
	output reg [1:0] Proc_ID
);

reg [12:0] Proc_PC[3:0];

initial
begin
	Slow_Clock = 1;
	Snapshot = 0;
	Load_Proc = 0;
	Proc_PC[0] = 0;
	Proc_PC[1] = 512;
	Proc_PC[2] = 1024;
	Proc_PC[3] = 1536;
end

integer clk_count = 0;
integer context_count = 0;

always@(posedge Fast_Clock)
begin

	if (Reset)
	begin
		clk_count <= 0;
		Slow_Clock <= 1;
	end
	else
	begin		
		if (clk_count<CLOCK_COUNT)
		begin
			clk_count <= clk_count + 1;
		end
		else
		begin
			clk_count <= 0;
			Slow_Clock <= ~Slow_Clock;
		end
	end
end


always @ (Slow_Clock)
begin

	if (Reset)
	begin
		context_count <= 0;
	end

	if (Slow_Clock)
	begin
		if (Proc_ID != 0)
		begin
			if ((context_count > INST_COUNT) || Halt)
			begin
				Snapshot <= 1;
				context_count <= 0;
			end
			else
			begin
				context_count <= context_count + 1;
			end
		end
		else if (Exec_Proc)
		begin
			Snapshot <= 1;
		end
	end
	else
	begin
		Snapshot <= 0;
	end
end

always @ (posedge Update_PC)
begin

	if (Reset)
	begin
		Proc_PC[0] = 0;
		Proc_PC[1] = 512;
		Proc_PC[2] = 1024;
		Proc_PC[3] = 1536;
		Load_Proc = 0;
	end

	Load_Proc = 0;
	
	if (Exec_Proc)
	begin
		Proc_PC[0] = Next_PC;
		Proc_ID = Data1[1:0];
		New_PC = Proc_PC[Proc_ID];
	end
	else
	begin
		Proc_PC[Proc_ID] = Next_PC;
		Proc_ID = 0;
		New_PC = Proc_PC[0];
	end

	Load_Proc = 1;

end

endmodule
