
default: c

test: rundiff

a.out: uva439.c
	cc -lm -lcrypt -O2 -pipe -ansi -DONLINE_JUDGE uva439.c

c: a.out entrada.in
	./a.out < entrada.in

cuva.out: a.out entrada.in
	./a.out < entrada.in > uva439.out

rundiff: cuva.out
	diff resposta.out uva439.out

cpp.out: uva439.cpp
	g++ -lm -lcrypt -O2 -pipe -DONLINE_JUDGE uva439.cpp -o cpp.out

cpp.out0: uva439.cpp
	g++ -lm -lcrypt -g -O0 -pipe uva439.cpp -o cpp.out


cpp: cpp.out entrada.in
	./cpp.out < entrada.in

cppdeb:
	g++ -lm -lcrypt -O2 -pipe uva439.cpp -o cpp.out
	./cpp.out < entrada.in

cpprundiff: cpp.out entrada.in resposta.out
	./cpp.out < entrada.in > uva439.out
	diff resposta.out uva439.out

cppvalgrind: cpp.out0
	echo "e2 e4"| valgrind --leak-check=full ./cpp.out

clean:
	$(RM) uva439.out a.out cpp.out

