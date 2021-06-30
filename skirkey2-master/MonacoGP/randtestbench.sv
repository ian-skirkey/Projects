module randtestbench();

timeunit 10ns ;

timeprecision 1ns ;

logic clk, reset, fastclk, Reset_h; 
logic [7:0] q;





rand_num_generator rand0(.*);

always begin : CLOCK_GENERATION
#1 clk = ~clk;
end

initial begin : CLOCK_INITIALIZATION
	clk = 0;
end 


initial begin : TEST_VECTORS

#1 reset = 1'b1;
#2 reset = 1'b0;
#60;


end






endmodule 