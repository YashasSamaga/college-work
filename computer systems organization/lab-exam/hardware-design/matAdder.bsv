package matAdder;
import FIFO::*;

interface Adder;
	method Action put(Bit#(16) dat, Int#(16) r, Int#(16) c);
	method Bit#(16) result;
endinterface

module mkmatAdder(Adder);
Reg#(Bit#(16)) mat[10][10];
Reg#(Bit#(16)) _result <- mkReg(0);
Reg#(Bool) _enable <- mkReg(False);
Reg#(Bit#(16)) row <- mkReg(0);
Reg#(Bit#(16)) col <- mkReg(0);
//############################# INITS ########################################
for(int i=0; i< 10 ; i = i+1) begin
	for(int j=0 ;j<10; j = j +1)
		mat[i][j] <- mkReg(0);
end

//#############################################################################


	//################## PUT YOUR LOGIC HERE USE THE _enable signal ###############
	rule add (_enable == True);
		Bit#(16) bus[6];
		bus[0] = _result;
		
		if(col == 0)
		begin
			for(Integer i = 0; i < 5; i = i + 1)
				bus[i+1] = bus[i] + mat[row][i];
		end
		
		if(col == 1)
		begin
			for(Integer i = 0; i < 5; i = i + 1)
				bus[i+1] = bus[i] + mat[row][5 + i];
			row <= row + 1;
		end
		
		if(row == 10 && col == 1)
			_enable <= False;
		
		col <= col ^ 1;
		_result <= bus[5];
	endrule
	
	//################### PUT THE RESULT IN THE _result REGISTER##################


	//###########Interface methods ###############################################	
	method Action put(Bit#(16) dat, Int#(16) r, Int#(16) c);
		mat[r][c] <= dat;
		if( r== 9 && c == 9)
		begin
			_enable <= True;
		end
	endmethod
	
	method Bit#(16) result;
			return _result;
	endmethod
	
endmodule
endpackage
