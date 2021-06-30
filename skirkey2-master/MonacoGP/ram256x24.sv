module trackpal ( output logic [23:0] q,
						 input [23:0] d,
						 input [7:0] write_address, read_address,
						 input we, clk );
			
logic [23:0] track_pal [255:0];

initial begin
$readmemh("Racetracknew_palette.mem", track_pal);
 end

always_ff @ (posedge clk) begin
		if (we)
			track_pal[write_address] <= d;
		
		q <= track_pal[read_address];
end
			
endmodule 