EXE = main

$(EXE) : $(EXE).cpp
	g++ -lm -lcrypt -O2 -std=c++11 -pipe -DONLINE_JUDGE -Werror -Wall \
		-std=c++11 -o $@ $<

.PHONY : clean run

run : $(EXE)
	./$< < sample_input

clean :
	rm -f $(EXE) *.o *.d
