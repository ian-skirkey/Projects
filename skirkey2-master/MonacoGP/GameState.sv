module gamestate (input [9:0] DrawX, DrawY,
						input [9:0] CarX, CarY,
						input [9:0] npcX, npcY,
						input clk,
						input DrawCar,
						input DrawNPC,
						input [7:0] car_addr,
						input [7:0] npc_addr,
						input [7:0] keycode,
						output gamereset
						);
logic npcwhite, carwhite;

assign npcwhite = ((npc_addr == 8'h00) | (npc_addr == 8'h01) | (npc_addr == 8'h02) | (npc_addr == 8'h03) | (npc_addr == 8'h04) | (npc_addr == 8'h05));
assign carwhite = ((car_addr == 8'h00) | (car_addr == 8'h01) | (car_addr == 8'h02) | (car_addr == 8'h03) | (car_addr == 8'h04) | (car_addr == 8'h05));

always_ff @ (posedge clk) begin
	//if ((DrawX >= CarX) & (DrawX < (CarX + 10'b0000100111)) & (DrawY >= CarY) & (DrawY < (CarY + 10'b0001001101)) & (DrawX >= npcX) & (DrawX < (npcX + 10'b0000100111)) & (DrawY >= npcY) & (DrawY < (npcY + 10'b0001001101)))
	if ((DrawCar == 1'b1) & (DrawNPC == 1'b1) & (~npcwhite) & (~carwhite))
	gamereset <= 1'b1;
	if (keycode == 8'h15)
	gamereset <= 1'b0;
end


endmodule 