RUN=Ordering
CXX=clang++

default: $(RUN)

$(RUN): main.cpp
	$(CXX) -lm -lcrypt -Wall -Wextra -pipe main.cpp -o $(RUN)

run: $(RUN)
	./$(RUN)

clean:
	$(RM) *.o $(RUN)

