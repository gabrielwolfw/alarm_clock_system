module nios_alarm (
		input logic clk,                                    
		input logic reset_n, 
		input logic [3:0] buttons_n,   
		input logic [1:0] switches_n,  
		output logic [31:0] n_7segments		
);
	NIOS_PLATFORM plat(
		.clk_clk(clk),
		.pio_7segments_0_external_connection_export(n_7segments),
		.pio_buttons_0_external_connection_export(buttons_n),
		.pio_switches_0_external_connection_export(switches_n),
		.reset_reset_n(reset_n)
	);

endmodule	