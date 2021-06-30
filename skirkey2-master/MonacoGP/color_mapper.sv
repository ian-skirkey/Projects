//-------------------------------------------------------------------------
//    Color_Mapper.sv                                                    --
//    Stephen Kempf                                                      --
//    3-1-06                                                             --
//                                                                       --
//    Modified by David Kesler  07-16-2008                               --
//    Translated by Joe Meng    07-07-2013                               --
//                                                                       --
//    Fall 2014 Distribution                                             --
//                                                                       --
//    For use with ECE 385 Lab 7                                         --
//    University of Illinois ECE Department                              --
//-------------------------------------------------------------------------


module  color_mapper ( input        [9:0] DrawX, DrawY,
							  input  logic [9:0] CarX,
								input logic [9:0] CarY,
								input logic [9:0] npcX,
								input logic [9:0] npcY,
								input 				DrawCar,
								input             DrawNPC,
								input             clk,
								input [6:0] counter,
								input [6:0] npccounter,
								input [7:0] TrackLine,
								output [7:0] car_addr, npc_addr,
                       output logic [7:0]  Red, Green, Blue,
							  output logic [23:0] color );
    
logic [7:0] dispcar_addr;
logic [23:0] car_color;
logic [7:0] track_addr;
logic [23:0] track_color;
 logic npcwhite, carwhite;
 
 trackptr ptr0(.q(track_addr), .read_address(((17'b00000000101000000)*(TrackLine+17'b00000000000000000)) + (DrawX+17'b00000000000000000)), .we(1'b0), .clk(clk) );
 trackpal pal0(.q(track_color), .read_address(track_addr), .we(1'b0), .clk(clk) );
 carptr ptr1(.q(car_addr), .read_address(((12'b000000101000)*counter) + (DrawX-CarX)), .we(1'b0), .clk(clk) );
 carptr ptr2(.q(npc_addr), .read_address(((12'b000000101000)*npccounter) + (DrawX-npcX)), .we(1'b0), .clk(clk) );
 carpal pal1(.q(car_color), .read_address(dispcar_addr), .we(1'b0), .clk(clk) );
 

assign npcwhite = ((npc_addr == 8'h00) | (npc_addr == 8'h01) | (npc_addr == 8'h02) | (npc_addr == 8'h03) | (npc_addr == 8'h04) | (npc_addr == 8'h05));
assign carwhite = ((car_addr == 8'h00) | (car_addr == 8'h01) | (car_addr == 8'h02) | (car_addr == 8'h03) | (car_addr == 8'h04) | (car_addr == 8'h05));
 
 
always_comb begin
	if ((DrawX < 10'b0101000000) & (DrawY < 10'b0011110000)) begin
	if (DrawCar ^ DrawNPC) begin
		if (DrawNPC)
			dispcar_addr = npc_addr;
		else
			dispcar_addr = car_addr;
		
	color = car_color;
	
	if ((dispcar_addr == 8'h00) | (dispcar_addr == 8'h01) | (dispcar_addr == 8'h02) | (dispcar_addr == 8'h03) | (dispcar_addr == 8'h04) | (dispcar_addr == 8'h05)) begin
		color = track_color;
		end
	Red = color [23:16];
	Green = color [15:8];
	Blue = color [7:0];
	end
	else begin
	if ((DrawCar & DrawNPC) & (npcwhite ^ carwhite)) begin
		if (npcwhite)
			dispcar_addr = car_addr;
		else
			dispcar_addr = npc_addr;
			
	color = car_color;
	end
	else begin
		color = track_color;
		dispcar_addr = 8'b00000000;
	end
	Red = color [23:16];
	Green = color [15:8];
	Blue = color [7:0];
	end
	end
	
	else begin
	color = 24'h000000;
	Red = 8'h00;
	Green = 8'h00;
	Blue = 8'h00;
	dispcar_addr = 8'b00000001;
	end
end

    
endmodule
