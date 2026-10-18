// DIAGNOSTIC top level (lab1_rebuild only; the real design stays COMPSYS303_Lab1.bdf).
// Same nios2_system connections as COMPSYS303_Lab1.bdf, plus a hardware-only mirror
// of the inputs on HEX0 (segments are active low), independent of the Nios II:
//   HEX0[3:0] (a,b,c,d) lit while SW[3:0] is up
//   HEX0[6:4] (g,f,e)   lit while KEY[2:0] is held
// AI Use Declaration: written with the assistance of Claude (Anthropic).
module COMPSYS303_Lab1_diag (
    input         CLOCK_50,
    input  [3:0]  KEY,
    input  [17:0] SW,
    output [17:0] LEDR,
    output [8:0]  LEDG,
    output [6:0]  HEX0,
    output [11:0] DRAM_ADDR,
    output [1:0]  DRAM_BA,
    output        DRAM_CAS_N,
    output        DRAM_CKE,
    output        DRAM_CLK,
    output        DRAM_CS_N,
    inout  [15:0] DRAM_DQ,
    output [1:0]  DRAM_DQM,
    output        DRAM_RAS_N,
    output        DRAM_WE_N,
    inout  [7:0]  LCD_DATA,
    output        LCD_EN,
    output        LCD_RS,
    output        LCD_RW,
    output        LCD_ON,
    output        LCD_BLON,
    input         UART_RXD,
    output        UART_TXD
);
    assign LCD_ON   = 1'b1;     // inst2 (VCC) in the schematic
    assign LCD_BLON = 1'b1;

    assign HEX0[3:0] = ~SW[3:0];
    assign HEX0[6:4] = KEY[2:0];

    nios2_system inst1 (
        .clk_clk                               (CLOCK_50),
        .keys_external_connection_export       (KEY[2:0]),
        .reset_reset_n                         (KEY[3]),
        .switches_external_connection_export   (SW),
        .leds_red_external_connection_export   (LEDR),
        .leds_green_external_connection_export (LEDG),
        .lcd_external_RS                       (LCD_RS),
        .lcd_external_RW                       (LCD_RW),
        .lcd_external_data                     (LCD_DATA),
        .lcd_external_E                        (LCD_EN),
        .sdram_pll_sdram_clk_clk               (DRAM_CLK),
        .sdram_wire_addr                       (DRAM_ADDR),
        .sdram_wire_ba                         (DRAM_BA),
        .sdram_wire_cas_n                      (DRAM_CAS_N),
        .sdram_wire_cke                        (DRAM_CKE),
        .sdram_wire_cs_n                       (DRAM_CS_N),
        .sdram_wire_dq                         (DRAM_DQ),
        .sdram_wire_dqm                        (DRAM_DQM),
        .sdram_wire_ras_n                      (DRAM_RAS_N),
        .sdram_wire_we_n                       (DRAM_WE_N),
        .uart_external_connection_rxd          (UART_RXD),
        .uart_external_connection_txd          (UART_TXD)
    );
endmodule
