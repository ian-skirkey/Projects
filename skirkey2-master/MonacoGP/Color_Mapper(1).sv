//-------------------------------------------------------------------------
//    Color_Mapper.sv                                                    --
//    Stephen Kempf                                                      --
//    3-1-06                                                             --
//                                                                       --
//    Modified by David Kesler  07-16-2008                               --
//    Translated by Joe Meng    07-07-2013                               --
//                                                                       --
//    Fall 2014 Distribution                                             --
//                                                                       --
//    For use with ECE 385 Lab 7                                         --
//    University of Illinois ECE Department                              --
//-------------------------------------------------------------------------


module  color_mapper ( input        [9:0] DrawX, DrawY,
                       output logic [7:0]  Red, Green, Blue,
							  output logic [7:0] track_ptr [16:0],
							  output logic [7:0] car_ptr [11:0],
							  output logic	[23:0] car_pal [7:0],
							  output logic [23:0] track_pal [7:0],
							  output logic [7:0] track_addr,
							  output logic [23:0] color );
    

/*logic [7:0] track_ptr [16:0];
logic [7:0] car_ptr [11:0];
logic	[23:0] car_pal [7:0];
logic [23:0] track_pal [7:0];
logic [7:0] track_addr;
logic [23:0] color;*/

initial begin
$readmemh("racetrack320.mem", track_ptr); 
$readmemh("racetrack320_palette.mem", track_pal);
$readmemh("racecar320.mem", car_ptr); 
$readmemh("racecar320_palette.mem", car_pal);
 end
 

 
always_comb begin
	if ((DrawX < 10'b0101000000) & (DrawY < 10'b0011110000)) begin
	track_addr = track_ptr[((10'b0101000000)*DrawY) + DrawX];
	color = track_pal [track_addr];
	Red = color [23:16];
	Green = color [15:8];
	Blue = color [7:0];
	end
	else begin
	track_addr = 8'h00;
	color = 24'h000000;
	Red = 8'h00;
	Green = 8'h00;
	Blue = 8'h00;
	end
end

    
endmodule
