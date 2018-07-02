module data_mem(address, clk, write_data, wren, read_data);
  input [7:0] address;
  input clk, wren;
  input [7:0] write_data;
  output [7:0] read_data;

  reg [7:0] d_mem [0:255];

  always @ (posedge clk)
    if (wren == 0) d_mem[address] <= write_data;

  assign read_data = d_mem[address];
endmodule

module test_mem;
  reg [7:0] address;
  reg clk, wren;
  reg [7:0] write_data;
  wire [7:0] read_data;

  initial
    begin
      clk = 0;
      forever #50 clk = !clk;
    end

  initial
    begin
      #40 address = 0; write_data = 8'h21; wren = 0;
      #100 address = 1; write_data = 8'h43; wren = 0;
      #100 address = 2; write_data = 8'h65; wren = 1;
      #100 address = 2; write_data = 8'h87; wren = 0;
      #100 address = 3; write_data = 8'ha9; wren = 0;
      #100 address = 0; wren = 1;
      #100 address = 1; wren = 1;
      #100 address = 2; wren = 1;
      #100 address = 3; wren = 1;
    end

  initial
    $monitor($stime, " address=%d, clk=%d, write_data=%h, wren=%d, read_data=%h", address, clk, write_data, wren, read_data);

  data_mem data_mem_body(address, clk, write_data, wren, read_data);
endmodule

