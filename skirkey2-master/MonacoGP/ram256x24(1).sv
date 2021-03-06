module carpal ( output logic [23:0] q,
						 input [23:0] d,
						 input [7:0] write_address, read_address,
						 input we, clk );
			
logic [23:0] car_pal [255:0];

initial begin
$readmemh("racecar320new_palette.mem", car_pal);
 end

always_ff @ (posedge clk) begin
		if (we)
			car_pal[write_address] <= d;
		
		q <= car_pal[read_address];
end
			
endmodule 