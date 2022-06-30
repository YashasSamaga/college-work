.PHONY = all clean

all: scan

scan: main.cu ../helpers.hpp
	nvcc main.cu -o scan -arch=native -O3

clean:
	rm scan


