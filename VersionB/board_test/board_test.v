// DE2-115 board input test (no Nios II): proves whether the slide switches
// and push buttons reach the FPGA at all.
//   LEDR[17:0] follows SW[17:0]      (switch up  -> red LED on)
//   LEDG[3:0]  lights while KEY[3:0] is pressed (keys are active low)
//   LEDG[8]    blinks at ~1.5 Hz from CLOCK_50 (proves the image is running)
// AI Use Declaration: Harold and Lucas designed the system and made all design decisions.
// They discussed the structure of the code with Claude (Anthropic), which helped write
// parts of this file; Harold and Lucas reviewed, tested and verified all of it.
module board_test (
    input         CLOCK_50,
    input  [17:0] SW,
    input  [3:0]  KEY,
    output [17:0] LEDR,
    output [8:0]  LEDG
);
    reg [24:0] cnt = 0;
    always @(posedge CLOCK_50) cnt <= cnt + 1'b1;

    assign LEDR      = SW;
    assign LEDG[3:0] = ~KEY;
    assign LEDG[7:4] = 4'b0000;
    assign LEDG[8]   = cnt[24];
endmodule
