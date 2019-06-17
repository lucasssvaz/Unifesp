module Decoder(input Up, input Down, input Reset, input [3:0] state, output reg [3:0] bin);

always @ (*)
begin
		if (Reset == 1)
		begin
			bin = 4'd4;
		end else if (Up == 1 && Down == 1)
		begin
			bin = 4'd15;
		end else if(state == 4'd0)
		begin
			if (Up == 1 && Down == 0)
			begin
				bin = 4'd5;
			end else if (Up == 0 && Down == 1)
			begin
				bin = 4'd2;
			end else
			begin
				bin = 4'd4;
			end
		end else if(state == 4'd1)
		begin
			if (Up == 1 && Down == 0)
			begin
				bin = 4'd6;
			end else if (Up == 0 && Down == 1)
			begin
				bin = 4'd4;
			end else
			begin
				bin = 4'd5;
			end
		end else if(state == 4'd2)
		begin
			if (Up == 1 && Down == 0)
			begin
				bin = 4'd4;
			end else if (Up == 0 && Down == 1)
			begin
				bin = 4'd5;
			end else
			begin
				bin = 4'd6;
			end
		end else if(state == 4'd3)
		begin
			if (Up == 1 && Down == 0)
			begin
				bin = 4'd8;
			end else if (Up == 0 && Down == 1)
			begin
				bin = 4'd6;
			end else
			begin
				bin = 4'd4;
			end
		end else if(state == 4'd4)
		begin
			if (Up == 1 && Down == 0)
			begin
				bin = 4'd0;
			end else if (Up == 0 && Down == 1)
			begin
				bin = 4'd4;
			end else
			begin
				bin = 4'd8;
			end
		end else if(state == 4'd5)
		begin
			if (Up == 1 && Down == 0)
			begin
				bin = 4'd1;
			end else if (Up == 0 && Down == 1)
			begin
				bin = 4'd8;
			end else
			begin
				bin = 4'd0;
			end
		end else if(state == 4'd6)
		begin
			if (Up == 1 && Down == 0)
			begin
				bin = 4'd9;
			end else if (Up == 0 && Down == 1)
			begin
				bin = 4'd0;
			end else
			begin
				bin = 4'd1;
			end
		end else if(state == 4'd7)
		begin
			if (Up == 1 && Down == 0)
			begin
				bin = 4'd2;
			end else if (Up == 0 && Down == 1)
			begin
				bin = 4'd1;
			end else
			begin
				bin = 4'd9;
			end
		end else if(state == 4'd8)
		begin
			if (Up == 1 && Down == 0)
			begin
				bin = 4'd4;
			end else if (Up == 0 && Down == 1)
			begin
				bin = 4'd9;
			end else
			begin
				bin = 4'd2;
			end
		end else if(state == 4'd15)
		begin
			if ((Up == 1 && Down == 0) || (Up == 0 && Down == 1))
			begin
				bin = 4'd4;
			end else
			begin
				bin = 4'd15;
			end
		end
end

endmodule
