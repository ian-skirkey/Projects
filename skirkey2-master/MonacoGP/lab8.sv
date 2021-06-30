//-------------------------------------------------------------------------
//                                                                       --
//                                                                       --
//      For use with ECE 385 Lab 8                                       --
//      UIUC ECE Department                                              --
//-------------------------------------------------------------------------


module lab8 (

      ///////// Clocks /////////
      input              Clk,

      ///////// KEY /////////
      input    [ 1: 0]   KEY,

      ///////// SW /////////
      input    [ 9: 0]   SW,

      ///////// LEDR /////////
      output   [ 9: 0]   LED,

      ///////// HEX /////////
      output   [ 7: 0]   HEX0,
      output   [ 7: 0]   HEX1,
      output   [ 7: 0]   HEX2,
      output   [ 7: 0]   HEX3,
      output   [ 7: 0]   HEX4,
      output   [ 7: 0]   HEX5,

      ///////// SDRAM /////////
      output             DRAM_CLK,
      output             DRAM_CKE,
      output   [12: 0]   DRAM_ADDR,
      output   [ 1: 0]   DRAM_BA,
      inout    [15: 0]   DRAM_DQ,
      output             DRAM_LDQM,
      output             DRAM_UDQM,
      output             DRAM_CS_N,
      output             DRAM_WE_N,
      output             DRAM_CAS_N,
      output             DRAM_RAS_N,

      ///////// VGA /////////
      output             VGA_HS,
      output             VGA_VS,
      output   [ 3: 0]   VGA_R,
      output   [ 3: 0]   VGA_G,
      output   [ 3: 0]   VGA_B,


      ///////// ARDUINO /////////
      inout    [15: 0]   ARDUINO_IO,
      inout              ARDUINO_RESET_N 

);




logic Reset_h, vssig, blank, sync, VGA_Clk;


//=======================================================
//  REG/WIRE declarations
//=======================================================
	logic SPI0_CS_N, SPI0_SCLK, SPI0_MISO, SPI0_MOSI, USB_GPX, USB_IRQ, USB_RST;
	logic [3:0] hex_num_4, hex_num_3, hex_num_1, hex_num_0; //4 bit input hex digits
	logic [1:0] signs;
	logic [1:0] hundreds;
	logic [9:0] drawxsig, drawysig, carxsig, carysig, npcxsig, npcysig;
	logic drawcarsig, drawnpcsig;
	logic [6:0] carcounter, npccounter;
	logic [7:0] Red, Blue, Green;
	logic [7:0] keycode;
	logic [7:0] trackline, randnum, caraddrsig, npcaddrsig;
	logic npcclk;
	logic gamereset;

//=======================================================
//  Structural coding
//=======================================================
	assign ARDUINO_IO[10] = SPI0_CS_N;
	assign ARDUINO_IO[13] = SPI0_SCLK;
	assign ARDUINO_IO[11] = SPI0_MOSI;
	assign ARDUINO_IO[12] = 1'bZ;
	assign SPI0_MISO = ARDUINO_IO[12];
	
	assign ARDUINO_IO[9] = 1'bZ; 
	assign USB_IRQ = ARDUINO_IO[9];
	
	
	//Assignments specific to Circuits At Home UHS_20
	assign ARDUINO_RESET_N = USB_RST;
	assign ARDUINO_IO[7] = USB_RST;//USB reset
	assign ARDUINO_IO[8] = 1'bZ; //this is CS for the SD Card, prevents SD card from activating
	//GPX is unconnected to shield, not needed for standard USB host - set to 0 to prevent interrupt
	assign USB_GPX = 1'b0;
	
	//Assign uSD CS to '1' to prevent uSD card from interfering with USB Host (if uSD card is plugged in)
	assign ARDUINO_IO[6] = 1'b1;
	
	//HEX drivers to convert numbers to HEX output
	HexDriver hex_driver4 (hex_num_4, HEX4[6:0]);
	assign HEX4[7] = 1'b1;
	
	HexDriver hex_driver3 (hex_num_3, HEX3[6:0]);
	assign HEX3[7] = 1'b1;
	
	HexDriver hex_driver1 (hex_num_1, HEX1[6:0]);
	assign HEX1[7] = 1'b1;
	
	HexDriver hex_driver0 (hex_num_0, HEX0[6:0]);
	assign HEX0[7] = 1'b1;
	
	//fill in the hundreds digit as well as the negative sign
	assign HEX5 = {1'b1, ~signs[1], 3'b111, ~hundreds[1], ~hundreds[1], 1'b1};
	assign HEX2 = {1'b1, ~signs[0], 3'b111, ~hundreds[0], ~hundreds[0], 1'b1};
	
	
	//Assign one button to reset
	assign {Reset_h}=~ (KEY[0]);
	

	//Our A/D converter is only 12 bit
	assign VGA_R = Red[7:4];
	assign VGA_B = Blue[7:4];
	assign VGA_G = Green[7:4];
	
	
	lab8_soc u0 (
		.clk_clk                           (Clk),            //clk.clk
		.reset_reset_n                     (1'b1),           //reset.reset_n
		.altpll_0_locked_conduit_export    (),               //altpll_0_locked_conduit.export
		.altpll_0_phasedone_conduit_export (),               //altpll_0_phasedone_conduit.export
		.altpll_0_areset_conduit_export    (),               //altpll_0_areset_conduit.export
		.key_external_connection_export    (KEY),            //key_external_connection.export

		//SDRAM
		.sdram_clk_clk(DRAM_CLK),                            //clk_sdram.clk
		.sdram_wire_addr(DRAM_ADDR),                         //sdram_wire.addr
		.sdram_wire_ba(DRAM_BA),                             //.ba
		.sdram_wire_cas_n(DRAM_CAS_N),                       //.cas_n
		.sdram_wire_cke(DRAM_CKE),                           //.cke
		.sdram_wire_cs_n(DRAM_CS_N),                         //.cs_n
		.sdram_wire_dq(DRAM_DQ),                             //.dq
		.sdram_wire_dqm({DRAM_UDQM,DRAM_LDQM}),              //.dqm
		.sdram_wire_ras_n(DRAM_RAS_N),                       //.ras_n
		.sdram_wire_we_n(DRAM_WE_N),                         //.we_n

		//USB SPI	
		.spi0_SS_n(SPI0_CS_N),
		.spi0_MOSI(SPI0_MOSI),
		.spi0_MISO(SPI0_MISO),
		.spi0_SCLK(SPI0_SCLK),
		
		//USB GPIO
		.usb_rst_export(USB_RST),
		.usb_irq_export(USB_IRQ),
		.usb_gpx_export(USB_GPX),
		
		//LEDs and HEX
		.hex_digits_export({hex_num_4, hex_num_3, hex_num_1, hex_num_0}),
		.leds_export({hundreds, signs, LED}),
		.keycode_export(keycode)
		
	 );


//instantiate a vga_controller, ball, and color_mapper here with the ports.

	vga_controller vga(         .Clk(Clk),       // 50 MHz clock
                               .Reset(Reset_h),     // reset signal
										 .hs(VGA_HS),        // Horizontal sync pulse.  Active low
								       .vs(VGA_VS),        // Vertical sync pulse.  Active low
										 .pixel_clk(VGA_Clk), // 25 MHz pixel clock output
										 .blank(blank),     // Blanking interval indicator.  Active low.
										 .sync(sync),      // Composite Sync signal.  Active low.  We don't use it in this lab,
												             //   but the video DAC on the DE2 board requires an input for it.
								       .DrawX(drawxsig),     // horizontal coordinate
								       .DrawY(drawysig)      // vertical coordinate
										 ); 
										
	rand_num_generator rand1(.clk(npcclk), .fastclk(VGA_VS), .reset(gamereset), .q(randnum), .Reset_h(Reset_h) );	
										 
	trackmotion mov(.frame_clk(VGA_VS), .hs(VGA_HS), .DrawY(drawysig), .line(trackline), .keycode(keycode), .reset(gamereset) );
												  
	Car cars(.Reset(gamereset), .frame_clk(VGA_VS), .keycode(keycode), .CarX(carxsig), .CarY(carysig) );
	
	NPCCar npc(.frame_clk(VGA_VS), .npcX(npcxsig), .npcY(npcysig), .randnum(randnum), .dispNPC(npcclk), .reset(gamereset), .keycode(keycode) );
	
	NPCcolorstate s2(.Clk(Clk), .DrawX(drawxsig), .DrawY(drawysig), .CarX(npcxsig), .CarY(npcysig), .VGA_HS(VGA_HS), .Reset(Reset_h), .DrawCar(drawnpcsig), .counter(npccounter), .npcclk(npcclk), .gamereset(gamereset), .keycode(keycode) );
	
	colorstate s1(.Clk(Clk), .DrawX(drawxsig), .DrawY(drawysig), .CarX(carxsig), .CarY(carysig), .VGA_HS(VGA_HS), .Reset(Reset_h), .DrawCar(drawcarsig), .counter(carcounter), .keycode(keycode) );
					
	color_mapper map1(.DrawX(drawxsig), .DrawY(drawysig), .CarX(carxsig), .CarY(carysig), .Red(Red), .Green(Green), .Blue(Blue), .DrawCar(drawcarsig), .counter(carcounter), .clk(Clk), .TrackLine(trackline), .npcX(npcxsig), .npcY(npcysig), .npccounter(npccounter), .DrawNPC(drawnpcsig), .car_addr(caraddrsig), .npc_addr(npcaddrsig) );
	
	gamestate game0(.DrawX(drawxsig), .DrawY(drawysig), .CarX(carxsig), .CarY(carysig), .npcX(npcxsig), .npcY(npcysig), .gamereset(gamereset), .clk(VGA_Clk), .keycode(keycode), .DrawCar(drawcarsig), .DrawNPC(drawnpcsig), .car_addr(caraddrsig), .npc_addr(npcaddrsig) );

endmodule
