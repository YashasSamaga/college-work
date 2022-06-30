
.PHONY = all clean

all: dotproduct

dotproduct: main.cu ../helpers.hpp
	nvcc main.cu -o dotproduct -arch=native -O3 -lcublas

clean:
	rm dotproduct


