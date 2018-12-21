# This Makefile can be used from each of the Part subdirectories
# For example:    'make s1'

BSC=bsc

# ----------------------------------------------------------------
# Bluesim targets

.PHONY: mat

mat:
	$(BSC)  -sim  -u -g mkTestBench  -show-schedule -cpp  TestBench.bsv
	$(BSC)  -sim  -e mkTestBench  -o run  *.ba


# -----------------------------------------------------------------

.PHONY: clean fullclean

# Clean all intermediate files
clean:
	rm -f  *~  *.bi  *.bo  *.ba  *.h  *.cxx  *.o

# Clean all intermediate files, plus Verilog files, executables, schedule outputs
fullclean:
	rm -f  *~  *.bi  *.bo  *.ba  *.h  *.cxx  *.o
	rm -f  *.exe   *.so  *.sched  webtalk*  *.vcd xsim_* xe* *.jou

