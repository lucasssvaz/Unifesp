module Moore_Verilog(input Up, input Down, input Reset, input Clock, output [6:0] Display, output [3:0] Disp_Value);

wire New_Clock;
wire [3:0] Current_State;
//wire [3:0] DispValue;

Timer Div(.sysclock(Clock), .new_clock(New_Clock));
Transition Logic(.Up(Up), .Down(Down), .Reset(Reset), .clock(Clock), .CurrentState(Current_State), .NextState(Current_State));
Decoder ToBin(.state(Current_State), .bin(Disp_Value));
SeteSeg Disp(.bin(Disp_Value), .out(Display));

endmodule
