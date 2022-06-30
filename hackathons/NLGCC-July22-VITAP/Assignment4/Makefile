
.PHONY = all clean

all: spmv

spmv: main.cu ../helpers.hpp
	nvcc main.cu -o spmv -arch=native -O3

clean:
	rm spmv


