#! /bin/python
# -*- encoding: utf-8 -*-
from Queue import Queue

BRANCO = 1
CINZA = 2
PRETO = 3
INFINITO = -1
COR = 'cor'
TEMPO = 'tempo'
ARESTAS = 'arestas'
RESPOSTA = "Case %d: %d nodes not reachable from node %d with TTL = %d."

caso = 1

def print_grafo(grafo):
	print '{'
	for no in grafo:
		if grafo[no][COR] == BRANCO:
			c = '\033[30;47m'
		elif grafo[no][COR] == CINZA:
			c = '\033[1;31;47m' 
		elif grafo[no][COR] == PRETO:
			c = '\033[1;37;40m'
		print '\t', c, '%d:'%no, grafo[no], '\033[0m'
	print '}' 

# Retorna um objeto list() de inteiros
def ler_lista_inteiros():
	return list(map(int, raw_input().split()))

def ler_consulta():
	return ler_lista_inteiros()

# Inicializa o grafo, pintando tudo de branco e a raiz de cinza
def inicializar(grafo, inicial):
	for vert in grafo:
		grafo[vert][COR] = BRANCO
		grafo[vert][TEMPO] = INFINITO
	grafo[inicial][TEMPO] = 0
	grafo[inicial][COR] = CINZA
	Q = Queue()
	Q.put(inicial)
	return Q

# Adiciona à lista Q as arestas de Q, onde há tempo de descoberta
def descobrir_arestas(grafo, Q, TTL):
	no = Q.get()
	for adj in grafo[no][ARESTAS]:
		if grafo[adj][COR] == BRANCO:
			grafo[adj][COR] = CINZA
			grafo[adj][TEMPO] = grafo[no][TEMPO] + 1
			if grafo[adj][TEMPO] < TTL:
				Q.put(adj)
	grafo[no][COR] = PRETO

# Quantos vértices brancos existem no grafo
def contar_nos_brancos(grafo):
	return sum([1 for v in grafo if grafo[v][COR] == BRANCO])

# Busca em largura limitada pela TTL
def BFS(grafo, inicial, TTL):
	global caso
	if inicial == 0 and TTL == 0:
		return
	Q = inicializar(grafo, inicial)
	while not Q.empty():
		descobrir_arestas(grafo, Q, TTL)
		
	soma = contar_nos_brancos(grafo)
	print RESPOSTA % (caso, soma, inicial, TTL)
	#print_grafo(grafo)
	caso += 1
	BFS(grafo, *ler_consulta())

# Lê a lista de arestas e adiciona em grafo
# Formato: {Nó: {Arestas: [Nó1, Nó2], Cor: Branco, Tempo: 0}, ...}
def adicionar_aresta(grafo, de, para):
	#print NC, 'Adicionando', de, '->', para
	if grafo.has_key(de):
		grafo[de][ARESTAS] += [para]
	else:
		grafo[de] = {ARESTAS: [para]}
	# Como não é direcional, adicionamos para->de também.
	if not grafo.has_key(para):
		grafo[para] = {ARESTAS: [de]}
	else:
		grafo[para][ARESTAS] += [de]		

# Monta o grafo e executa o BFS
def ler():
	NC = int(raw_input())
	if NC == 0:
		exit(0)
	grafo = dict()
	while NC > 0:
		aresta = ler_lista_inteiros()
		adicionar_aresta(grafo, *aresta)
		NC -= 1
	BFS(grafo, *ler_consulta())

while True:
	try:
		ler()
	except (KeyboardInterrupt, EOFError):
		exit(1)
