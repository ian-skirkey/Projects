module NPCCar (output [9:0] npcX, npcY,
					output dispNPC,
					input frame_clk,
					input reset,
					input [7:0] keycode,
					input [7:0] randnum
					 );
					 
parameter [9:0] NPC_X_Min=48;       
parameter [9:0] NPC_X_Max=232;
parameter [9:0] NPC_Y_Max=238;


logic bounceleft, bounceright;
logic direction;
logic [9:0] newrand;
logic start;

always_comb begin
	if (randnum > NPC_X_Max)
		newrand = NPC_X_Max - (randnum - NPC_X_Max);
	else if (randnum < NPC_X_Min)
		newrand = randnum + NPC_X_Min;
	else
		newrand = randnum;
end

always_ff @ (posedge frame_clk) begin
	if (reset)
		start <= 1'b0;
		
	if (keycode == 8'h15)
		start <= 1'b1;
		
	if (~dispNPC | ~start) begin
		npcX <= newrand;
		npcY <= 10'b0000000000;
		dispNPC <= 1'b1;
		direction <= randnum[0];
		bounceright <= 1'b0;
		bounceleft <= 1'b0;
	end
	else begin 
	if (~bounceleft & ~bounceright) begin
		if (direction) begin
		npcX <= npcX + 1'b1;
		npcY <= npcY +1'b1;
		end
		else begin
		npcX <= npcX - 1'b1;
		npcY <= npcY +1'b1;
		end
		end
	else if (bounceleft) begin
		npcX <= npcX + 1'b1;
		npcY <= npcY +1'b1;
		end
	else begin
		npcX <= npcX - 1'b1;
		npcY <= npcY +1'b1;
		end
		
	end
	
	if (npcY == 10'b0011101111) 
		dispNPC <= 1'b0;
	
	if (npcX == NPC_X_Min) begin
		bounceleft <= 1'b1;
		bounceright <= 1'b0;
		end
	if (npcX == NPC_X_Max) begin
		bounceleft <= 1'b0;
		bounceright <= 1'b1;
		end
end
endmodule 