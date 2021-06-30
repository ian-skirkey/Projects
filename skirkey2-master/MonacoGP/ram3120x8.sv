module carptr ( output logic [7:0] q,
						 input [7:0] d,
						 input [11:0] write_address, read_address,
						 input we, clk );
			
logic [7:0] car_ptr [3119:0];

initial begin
$readmemh("racecar320new.mem", car_ptr); 
 end

always_ff @ (posedge clk) begin
		if (we)
			car_ptr[write_address] <= d;
		
		q <= car_ptr[read_address];
end
			
endmodule 