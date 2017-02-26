EXE = lawnmower

$(EXE) : $(EXE).cpp
	g++ -Werror -Wall -std=c++11 -pthread -O2 -g -o $@ $<

debug : $(EXE).cpp
	g++ -Werror -Wall -std=c++11 -pthread -g $<
	gdb a.out

.PHONY : clean run

run : $(EXE)
	./$<

clean :
	rm -f $(EXE) *.o *.d a.out
