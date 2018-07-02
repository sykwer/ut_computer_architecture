module computer(clk, rstd);
  input clk, rstd;

  wire [31:0] pc, ins, reg1, reg2, result, nextpc;
  wire [4:0] wra;
  wire [3:0] wren;

  fetch fetch_body(pc[7:0], ins);
  execute execute_body(clk, ins, pc, reg1, reg2, wra, result, nextpc);
  writeback writeback_body(clk, rstd, nextpc, pc);
  reg_file rf_body(clk, rstd, result, ins[25:21], ins[20:16], wra, (~|wra), reg1, reg2);

  initial
    $monitor($time, "rstd=%d, clk=%d, pc=%d, nextpc=%d, ins=%h, wra=%h, reg1=%h, reg2=%h", rstd, clk, pc, nextpc, ins, wra, reg1, reg2);
endmodule

module test_computer;
  reg clk, rstd;

  initial
    begin
      rstd = 1;
      #10 rstd = 0;
      #10 rstd = 1;
    end

  initial
    begin
      clk = 0;
      forever #50 clk = !clk;
    end

  computer computer_body(clk, rstd);
endmodule

