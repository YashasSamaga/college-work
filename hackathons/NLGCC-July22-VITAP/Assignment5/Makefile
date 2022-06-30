.PHONY = all clean

all: sort

sort: main.cu ../helpers.hpp
	nvcc main.cu -o sort -arch=native -O3

clean:
	rm sort


