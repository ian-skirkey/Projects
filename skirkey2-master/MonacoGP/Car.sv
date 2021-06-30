//-------------------------------------------------------------------------
//    Car.sv                                                            --
//    Viral Mehta                                                        --
//    Spring 2005                                                        --
//                                                                       --
//    Modified by Stephen Kempf 03-01-2006                               --
//                              03-12-2007                               --
//    Translated by Joe Meng    07-07-2013                               --
//    Fall 2014 Distribution                                             --
//                                                                       --
//    For use with ECE 298 Lab 7                                         --
//    UIUC ECE Department                                                --
//-------------------------------------------------------------------------


module  Car ( input Reset, frame_clk,
					input [7:0] keycode,
               output [9:0]  CarX, CarY );
    
    logic [9:0] Car_X_Pos, Car_X_Motion, Car_Y_Pos, Car_Y_Motion;
	 logic start;
	
	 
    parameter [9:0] Car_X_Center= 140;  // Center position on the X axis
    parameter [9:0] Car_Y_Center=155;  // Center position on the Y axis
    parameter [9:0] Car_X_Min=47;       // Leftmost point on the X axis
    parameter [9:0] Car_X_Max=233;     // Rightmost point on the X axis
    parameter [9:0] Car_Y_Min=5;       // Topmost point on the Y axis
    parameter [9:0] Car_Y_Max=155;     // Bottommost point on the Y axis
    parameter [9:0] Car_X_Step=1;      // Step size on the X axis
    parameter [9:0] Car_Y_Step=1;      // Step size on the Y axis
	 

   
    always_ff @ ( negedge frame_clk )
    begin: Move_Car
		
		if (Reset) begin
			Car_Y_Pos <= 155;
			Car_X_Pos <= 140;
			Car_Y_Motion <= 0;
			Car_X_Motion <= 0;
			start <= 1'b0;
		end
		
		if (keycode == 8'h00)
			start <= 1'b1;
			
			if (start & (~Reset)) begin

				 case (keycode)
					8'h04 : begin
							if (Car_X_Pos > Car_X_Min) begin
								Car_X_Motion <= -2;//A
								Car_Y_Motion<= 0;
							  end
							 else begin
								Car_Y_Motion <= 0;
								Car_X_Motion <= 0;
							 end
							  end
					        
					8'h07 : begin
							if (Car_X_Pos < Car_X_Max) begin	
					        Car_X_Motion <= 2;//D
							  Car_Y_Motion <= 0;
							  end
							else begin
								Car_Y_Motion <= 0;
								Car_X_Motion <= 0;
							end
							  end

							  
					8'h16 : begin
							if (Car_Y_Pos < Car_Y_Max) begin
					        Car_Y_Motion <= 2;//S
							  Car_X_Motion <= 0;
							  end
							else begin
								Car_Y_Motion <= 0;
								Car_X_Motion <= 0;
							end
							 end
							  
					8'h1A : begin
							if (Car_Y_Pos > Car_Y_Min) begin
					        Car_Y_Motion <= -1;//W
							  Car_X_Motion <= 0;
							  end
							else begin
								Car_Y_Motion <= 0;
								Car_X_Motion <= 0;
							end
							 end
				  8'h00 : begin
								Car_Y_Motion <= 0;
								Car_X_Motion <= 0;
				  end

			   endcase
				
				end
				 
				 if (keycode == 8'h15) begin
				 Car_Y_Pos <= 155;
				 Car_X_Pos <= 140;	
				 end
				 else begin
				 Car_Y_Pos <= (Car_Y_Pos + Car_Y_Motion);  // Update Car position
				 Car_X_Pos <= (Car_X_Pos + Car_X_Motion);
				 end
			
			
	  /**************************************************************************************
	    ATTENTION! Please answer the following quesiton in your lab report! Points will be allocated for the answers!
		 Hidden Question #2/2:
          Note that Car_Y_Motion in the above statement may have been changed at the same clock edge
          that is causing the assignment of Car_Y_pos.  Will the new value of Car_Y_Motion be used,
          or the old?  How will this impact behavior of the Car during a bounce, and how might that 
          interact with a response to a keypress?  Can you fix it?  Give an answer in your Post-Lab.
      **************************************************************************************/
      
			
		end  
    
       
    assign CarX = Car_X_Pos;
   
    assign CarY = Car_Y_Pos;
    

endmodule
