module trackmotion( input frame_clk,
						  input hs,
						  input reset,
						  input [9:0] DrawY,
						  input [7:0] keycode,
						  output [7:0] line
						   );
						  
	logic [7:0] sum;
	logic [7:0] startline;
	logic seam;
	logic [2:0] speed;
	logic start;

	always_ff @ (posedge frame_clk) begin
		if (reset) begin
			speed <= 3'b000;
			start <= 1'b0;
			end
		if (keycode == 8'h00)
			start <= 1'b1;
		
		if (keycode == 8'h15)
			speed <= 3'b101;
			
		if ((keycode == 8'h1A) & (speed < 3'b111) & start & (~reset)) 
			speed <= speed + 1'b1;
		else if ((keycode == 8'h16) & (speed > 3'b101) & start & (~reset))
			speed <= speed - 1'b1;
			
		if ((sum + speed) > 8'b11101111)
			sum <= (sum + speed) - 8'b11101111;
		else
			sum <= sum + speed;
		
		startline <= 8'b11101111 - sum;
		
	end
	
	always_ff @ (negedge hs) begin
		if (DrawY < 10'b0011110000) begin
		if (line == 8'b11101111) begin
			line <= 8'b00000000;
			seam <= 1'b1;
			end
		else if (~seam)	
		line <= startline + DrawY;
		else if (seam)
		line <= line + 1'b1;
		
		if (DrawY == 10'b0011101111) begin
			seam <= 1'b0;
			line <= startline;
			end
		end
	end
	
endmodule
						 
						 