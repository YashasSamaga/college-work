
.PHONY = all clean

all: convolver

convolver: main.cu ../helpers.hpp
	nvcc main.cu -o convolver -arch=native -O3

clean:
	rm convolver


