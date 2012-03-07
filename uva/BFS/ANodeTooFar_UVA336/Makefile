
default: uva336.py entrada.in
	@python uva336.py < entrada.in

RUNuva336.out:
	python uva336.py < entrada.in > uva336.out

rundiff: RUNuva336.out resposta.out
	diff resposta.out uva336.out

test: default rundiff

