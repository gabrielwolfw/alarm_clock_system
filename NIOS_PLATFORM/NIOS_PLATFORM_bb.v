
module NIOS_PLATFORM (
	clk_clk,
	reset_reset_n,
	pio_buttons_0_external_connection_export,
	pio_switches_0_external_connection_export,
	pio_7segments_0_external_connection_export);	

	input		clk_clk;
	input		reset_reset_n;
	input	[3:0]	pio_buttons_0_external_connection_export;
	input	[1:0]	pio_switches_0_external_connection_export;
	output	[31:0]	pio_7segments_0_external_connection_export;
endmodule
