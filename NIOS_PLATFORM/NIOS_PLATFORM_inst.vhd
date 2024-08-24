	component NIOS_PLATFORM is
		port (
			clk_clk                                    : in  std_logic                     := 'X';             -- clk
			reset_reset_n                              : in  std_logic                     := 'X';             -- reset_n
			pio_buttons_0_external_connection_export   : in  std_logic_vector(3 downto 0)  := (others => 'X'); -- export
			pio_switches_0_external_connection_export  : in  std_logic_vector(1 downto 0)  := (others => 'X'); -- export
			pio_7segments_0_external_connection_export : out std_logic_vector(31 downto 0)                     -- export
		);
	end component NIOS_PLATFORM;

	u0 : component NIOS_PLATFORM
		port map (
			clk_clk                                    => CONNECTED_TO_clk_clk,                                    --                                 clk.clk
			reset_reset_n                              => CONNECTED_TO_reset_reset_n,                              --                               reset.reset_n
			pio_buttons_0_external_connection_export   => CONNECTED_TO_pio_buttons_0_external_connection_export,   --   pio_buttons_0_external_connection.export
			pio_switches_0_external_connection_export  => CONNECTED_TO_pio_switches_0_external_connection_export,  --  pio_switches_0_external_connection.export
			pio_7segments_0_external_connection_export => CONNECTED_TO_pio_7segments_0_external_connection_export  -- pio_7segments_0_external_connection.export
		);

