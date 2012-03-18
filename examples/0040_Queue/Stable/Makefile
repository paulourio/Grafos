MAIN=main.cpp
INPUT=example.in
OUTPUT=example.out

default: diff

Main: $(MAIN)
	g++ -lm -lcrypt -O2 -pipe -DONLINE_JUDGE $(MAIN) -o Main

Maindeb: $(MAIN)
	g++ -lm -lcrypt -O0 -pipe $(MAIN) -o Main

main.out: Main $(INPUT)
	./Main < $(INPUT) > main.out

diff: main.out $(OUTPUT)
	diff main.out $(OUTPUT)

debug: Maindeb
	./Main < $(INPUT)

valgrind: Maindeb
	valgrind ./Main < $(INPUT)

clean:
	$(RM) Main main.out

