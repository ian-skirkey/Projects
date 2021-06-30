module NPCcolorstate ( input Clk,
							input [9:0] CarX,
							input [9:0] CarY,
							input [9:0] DrawX,
							input [9:0] DrawY,
							input VGA_HS,
							input Reset,
							input gamereset,
							input npcclk,
							input [7:0] keycode,
							output DrawCar,
							output [6:0] counter
						  );
						  
	//logic [6:0] counter;
	logic DrawingCar, start;
	
	/*always_ff @ (posedge Clk) begin
		if (Reset)
			counter <= 7'b0000000;
	end */
	
	always_ff @ (posedge Clk) begin
		if (keycode == 8'h15)
			start <= 1'b1;
	end
	
	always_ff @ (posedge Clk) begin
		if ((DrawY >= CarY) & (DrawY < (CarY+10'b0001001110)))
			DrawingCar <= 1'b1;
		else 
			DrawingCar <= 1'b0;
			
		end
						  
	always_ff @ (negedge VGA_HS) begin 
	
	if (DrawingCar)
	counter <= counter + 1'b1;
	
	if (counter == 7'b1001101)
	counter <= 7'b0000000;
	
	if (Reset)
			counter <= 7'b0000000;
			
	if (npcclk == 1'b0)
		counter <= 7'b0000000;
	
	end
						  
						  
	enum logic [1:0] {Wait, Draw} curr_state, next_state;
	
	always_ff @ (posedge Clk)

begin
        if (Reset)
            curr_state <= Wait;
        else 
            curr_state <= next_state;
    end

    // Assign outputs based on state
	always_comb
    begin
        
		  next_state  = curr_state;	//required because I haven't enumerated all possibilities below
        unique case (curr_state) 

            Wait : 
						 if ((DrawX >= CarX) & (DrawX < (CarX+10'b0000101000))  & (DrawY >= CarY) & (DrawY < (CarY+10'b0001001110)))					
						 next_state = Draw;
						 
						 
				Draw : 
						 if (DrawX >= (CarX+10'b0000101000))
						 next_state = Wait;
				
		endcase
		
		case (curr_state) 
			Wait :
			begin
			DrawCar = 1'b0;	
				
			end
			Draw :
			begin
			if (gamereset | (~start))
				DrawCar = 1'b0;
			else
				DrawCar = 1'b1;

			end
			
	   endcase
			
end
			
endmodule