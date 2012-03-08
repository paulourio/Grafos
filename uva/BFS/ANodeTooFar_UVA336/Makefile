
default: uva336.py entrada.in
	@python uva336.py < entrada.in

RUNuva336.out:
	python uva336.py < entrada.in > uva336.out

rundiff: RUNuva336.out resposta.out
	diff resposta.out uva336.out

test: default rundiff

cuva336.out: uva336.c
	gcc uva336.c
	./a.out < entrada.in > uva336.out

crundiff: cuva336.out
	diff resposta.out uva336.out

ctest: crundiff

clean:
	$(RM) uva336.out a.out

