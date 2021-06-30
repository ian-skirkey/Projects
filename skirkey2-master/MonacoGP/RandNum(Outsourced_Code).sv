// rand_num_generator.v
// created by : Meher Krishna Patel
// date : 22-Dec-16
// Feedback polynomial : x^3 + x^2 + 1
// maximum length : 2^3 - 1 = 7
// if parameter value is changed,
// then choose the correct Feedback polynomial i.e. change 'feedback_value' pattern


/* Code found at https://verilogguide.readthedocs.io/en/latest/verilog/designs.html (original header above)
	Modified by Ian Skirkey on 12/10/20 from .v to .sv and to include initial value setting capability
*/

module rand_num_generator

(
    input clk, reset, fastclk, Reset_h,
    output [7:0] q
);


logic [7:0] r_reg;
logic [7:0] r_next;
logic feedback_value;
logic [7:0] initval;

always_ff @ (posedge fastclk) begin
	if (initval == 8'b11111111)
		initval <= 8'b00000001;
	else
		initval <= initval + 1'b1;
end
                        
always_ff @ (negedge clk, posedge reset, posedge Reset_h)
begin 
    if (reset | Reset_h)
        begin
        // set initial value to 1
        //r_reg <= 1;  // use this or uncomment below two line
		  if (initval == 8'b00000000)
		  r_reg <= 8'b01001011;
		  else
		  r_reg <= initval;
        
      //r_reg[0] <= 1'b1; // 0th bit = 1
      //r_reg[7:1] <= 0;  // other bits are zero
        
        
        end     
    else if (clk == 1'b0)
        r_reg <= r_next;
end

//// N = 3
//// Feedback polynomial : x^3 + x^2 + 1
////total sequences (maximum) : 2^3 - 1 = 7
//assign feedback_value = r_reg[3] ^ r_reg[2] ^ r_reg[0];

//// N = 4
//assign feedback_value = r_reg[4] ^ r_reg[3] ^ r_reg[0];

// N = 5, maximum length = 28 (not 31)
//assign feedback_value = r_reg[5] ^ r_reg[3] ^ r_reg[0];

// N = 7
assign feedback_value = r_reg[7] ^ r_reg[6] ^ r_reg[0];

//// N = 9
//assign feedback_value = r_reg[9] ^ r_reg[5] ^ r_reg[0];


assign r_next = {feedback_value, r_reg[7:1]};
assign q = r_reg;
endmodule 