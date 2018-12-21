package TestBench;
import FIFOF::*;
import LFSR::*;
import matAdder::*;

module mkTestBench();

LFSR#(Bit#(16)) lfsr <- mkLFSR_16;
Reg#(Bool) init <- mkReg(True);
Reg#(int) inputs <- mkReg(0);
Reg#(int) clk <- mkReg(0);
Reg#(Bit#(16)) mat[10][10];
Reg#(Bit#(16)) expected <- mkReg(-1);
Reg#(Int#(16)) row <- mkReg(0);
Reg#(Int#(16)) col <- mkReg(0);
Adder madd <- mkmatAdder;

for(int i=0 ;i<10; i = i+1)
	for(int j=0 ;j< 10 ; j = j + 1)
		mat[i][j] <- mkReg(0);
	
	rule _clk;
			clk <= clk + 1;
			inputs <= inputs + 1;
	endrule	
	rule _init(init == True);
		lfsr.seed('h11);
	endrule


	rule _putValues (row < 10);
			Bit#(16) ra = lfsr.value;
			col <= (col + 1)%10;
			if(col == 9)
				row <= row + 1;
			mat[row][col] <= ra + pack(row*3 + col);
			madd.put(ra + pack(row*3 + col), row, col);
			lfsr.next();
	endrule

	rule _print (row == 10);
			Bit#(16) d = 0;
			for(int i = 0; i< 10 ; i = i + 1)
				for(int j=0 ;j< 10 ; j = j +1)
					d = d + mat[i][j];
			expected <= d;
	endrule

	rule _checkAnswer (clk == 120);
			Bit#(16) d = madd.result;
			if(d == expected) 
				$display(" ############### PASSED ##############");
			else
				$display(" ############### FAIL ##############");
			
			$finish(0);
	endrule
		
endmodule
endpackage
