module writeback(clk, rstd, nextpc, pc);
  input clk, rstd;
  input [31:0] nextpc;
  output [31:0] pc;

  reg [31:0] pc;

  always @ (negedge rstd or posedge clk)
    begin
      if (rstd == 0) pc <= 32'h00000000;
      else if (clk == 1) pc <= nextpc;
    end
endmodule

module test_writeback;
  reg clk, rstd;
  reg [31:0] nextpc;
  wire [31:0] pc;

  initial
    begin
      clk = 0;
      forever #50 clk = !clk;
    end

  initial
    begin
      rstd = 1;
      #10 rstd = 0;
      #20 rstd = 1;
    end

  initial
    begin
      #30 nextpc = 0'h00000001;
      #100 nextpc = 0'h12345678;
      #100 nextpc = 0'h87654321;
      #100 nextpc = 0'hffffffff;
    end

  writeback writeback_body(clk, rstd, nextpc, pc);

  initial
    $monitor($stime, " rstd=%d, clk=%d, nextpc=%h, pc=%h", rstd, clk, nextpc, pc);
endmodule

