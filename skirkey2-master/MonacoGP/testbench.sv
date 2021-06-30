module testbench1();
						 
timeunit 10ns ;

timeprecision 1ns ;

//logic [7:0] track_ptr [76799:0];
//logic [7:0] car_ptr [11:0];
//logic	[23:0] car_pal [7:0];
//logic [23:0] track_pal [255:0];
/*logic [7:0] track_addr;
logic [23:0] color;
logic [9:0] DrawX, DrawY;
logic [7:0]  Red, Green, Blue;
logic [8:0] CarX;
logic [7:0] CarY;
logic DrawCar;
logic [6:0] counter;
logic clk;
logic [7:0] TrackLine;
logic [9:0] npcX, npcY;
logic [6:0] npccounter;
logic DrawNPC;
logic [7:0] car_addr;
logic [7:0] npc_addr;*/

logic Clk;
							logic [9:0] CarX;
							logic [9:0] CarY;
							logic [9:0] DrawX;
							logic [9:0] DrawY;
							logic VGA_HS;
							logic Reset;
							logic [7:0] keycode;
							logic DrawCar;
							logic [6:0] counter;


colorstate map(.*);

always begin : CLOCK_GENERATION
#1 Clk = ~Clk;
end

initial begin : CLOCK_INITIALIZATION
	Clk = 0;
end 

initial begin : TEST_VECTORS
#1 Reset = 1'b1;
#2 Reset = 1'b0;
#2 CarX = 10'b0000000010;
#1 CarY = 10'b0000000010;
#1 DrawX = 10'b0000000010;
#1 DrawY = 10'b0000000010;
#10;


end
						 
						 
						 
						 
endmodule 