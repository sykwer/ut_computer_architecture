module fetch(pc, ins);
  input [7:0] pc;
  output [31:0] ins;

  reg [31:0] ins_mem [0:255];

  initial
    $readmemb("test.bnr", ins_mem);

  assign ins = ins_mem[pc];
endmodule

module test_fetch;
  reg clk, rstd;
  reg [7:0] pc;
  wire [31:0] ins;

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

  always @ (negedge rstd or posedge clk)
    begin
      if (rstd == 0) pc <= 0;
      else if (clk == 1) pc <= pc+1;
    end

  initial
    $monitor($stime, " rstd=%b, clk=%b, pc=%d, ins=%b", rstd, clk, pc, ins);

  fetch fetch_body(pc, ins);
endmodule

