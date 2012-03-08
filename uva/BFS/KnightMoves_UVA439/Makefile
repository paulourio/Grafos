
default: c

test: rundiff

a.out: uva439.c
	gcc -lm -lcrypt -O2 -pipe -ansi -DONLINE_JUDGE uva439.c

c: a.out entrada.in
	./a.out < entrada.in

cuva.out: a.out entrada.in
	./a.out < entrada.in > uva439.out

rundiff: cuva.out
	diff resposta.out uva439.out

clean:
	$(RM) uva439.out a.out

