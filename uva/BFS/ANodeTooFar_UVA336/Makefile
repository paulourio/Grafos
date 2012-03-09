
default: py

py: uva336.py entrada.in
	@python uva336.py < entrada.in

RUNuva336.out:
	python uva336.py < entrada.in > uva336.out

rundiff: RUNuva336.out resposta.out
	diff resposta.out uva336.out

test: default rundiff

a.out: uva336.c
	cc -lm -lcrypt -O2 -pipe -ansi -DONLINE_JUDGE uva336.c

c: a.out entrada.in
	./a.out < entrada.in

cpp.out: uva336.cpp
	g++ -Wall -lm -lcrypt -O2 -pipe -DONLINE_JUDGE uva336.cpp -o cpp.out

cpp: cpp.out
	./cpp.out < entrada.in

cppuva336.out: cpp.out
	./cpp.out < entrada.in > uva336.out

cpprundiff: cpp.out cppuva336.out
	diff resposta.out uva336.out

cuva336.out: a.out entrada.in
	./a.out < entrada.in > uva336.out

crundiff: cuva336.out
	diff resposta.out uva336.out

ctest: crundiff

clean:
	$(RM) uva336.out a.out cpp.out

