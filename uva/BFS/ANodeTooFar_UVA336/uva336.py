#! /bin/python
import Queue

BRANCO = 1
CINZA = 2
PRETO = 3
INFINITO = -1
COR = 'cor'
TEMPO = 'tempo'
ARESTAS = 'arestas'

def consultar():
	return list(map(int, raw_input().split()))

def BFS(grafo):
	inicial, TTL = consultar()
	Q = Queue.Queue()
	caso = 0
	while inicial != 0 and TTL != 0:
		caso += 1
		for vert in grafo:
			grafo[vert][COR] = BRANCO
			grafo[vert][TEMPO] = INFINITO
		grafo[inicial][TEMPO] = 0
		grafo[inicial][COR] = CINZA
		Q.put(inicial)
		while not Q.empty():
			no = Q.get()
			for adj in grafo[no][ARESTAS]:
				if grafo[adj][COR] == BRANCO:
					grafo[adj][COR] = CINZA
					grafo[adj][TEMPO] = grafo[no][TEMPO] + 1
					if grafo[adj][TEMPO] < TTL:
						Q.put(adj)
			grafo[no][COR] = PRETO
		soma = sum([1 for v in grafo if grafo[v][TEMPO] == BRANCO])
		print "Case %d: %d nodes not reachable from node %d with TTL = %d." % (caso, soma, inicial, TTL)
		inicial, TTL = consultar()

def ler():
	NC = int(raw_input())
	if NC == 0:
		exit(0)
	grafo = dict()
	while NC > 0:
		de, para = list(map(int, raw_input().split()))
		print NC, 'Adding', de, '->', para
		if grafo.has_key(de):
			grafo[de][ARESTAS] += [para]
		else:
			grafo[de] = {ARESTAS: [para]}
		if not grafo.has_key(para):
			grafo[para] = {ARESTAS: list()}
		NC -= 1
	BFS(grafo)

while True:
	ler()

