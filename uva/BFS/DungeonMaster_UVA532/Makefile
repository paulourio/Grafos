
INPUT=example.in
OUTPUT=example.out

default: diff

Main: main.cpp
	g++ -lm -lcrypt -O2 -pipe -DONLINE_JUDGE main.cpp -o Main

Maindeb: main.cpp
	g++ -lm -lcrypt -O0 -pipe main.cpp -o Main

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

