RUN=Prim
CXX=clang++
CXXFLAGS=-lm -lcrypt -Wall -Wextra -pipe

$(RUN): main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $(RUN)

run: $(RUN)
	./$(RUN)

release:
	make CXXFLAGS=-pipe\ -lm\ -lcrypt\ -Wall\ -Wextra\ -O2\ -DONLINE_JUDGE run

clean:
	$(RM) *.o $(RUN)

