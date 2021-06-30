module trackptr ( output logic [7:0] q,
						 input [7:0] d,
						 input [16:0] write_address, read_address,
						 input we, clk );
			
logic [7:0] track_ptr [76799:0];

initial begin
$readmemh("Racetracknew.mem", track_ptr); 
 end
 
always_ff @ (posedge clk) begin
		if (we)
			track_ptr[write_address] <= d;
		
		q <= track_ptr[read_address];
end
			
endmodule 