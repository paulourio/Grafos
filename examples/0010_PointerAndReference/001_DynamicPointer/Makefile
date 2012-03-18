MAIN=main.cpp

default: RunMain

Main: $(MAIN)
	g++ -lm -lcrypt -O2 -pipe -DONLINE_JUDGE $(MAIN) -o Main

Maindeb: $(MAIN)
	g++ -lm -lcrypt -O0 -pipe $(MAIN) -o Main

RunMain: Main
	./Main
	
debug: Maindeb
	./Main

valgrind: Maindeb
	valgrind ./Main

clean:
	$(RM) Main

