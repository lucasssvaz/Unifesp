import sys

def dfs(grafo,start,finish,caminho=[]):
	caminho = caminho + [start]
	if start==finish:
		return caminho
	if start not in grafo:
		return []
	for node in grafo[start]:
		if node not in caminho:
			novo_caminho=busca(grafo,node,finish,caminho)
			if len(novo_caminho)>0: return novo_caminho
	return []

def bfs(grafo, inicio, fim):
    fila = []
    fila.append([inicio])
    while fila:
        caminho = fila.pop(0)
        no = caminho[-1]
        if no == fim:
            return caminho
        for adjacente in grafo.get(no, []):
            if adjacente not in caminho:
               novo_caminho = list(caminho)
               novo_caminho.append(adjacente)
               fila.append(novo_caminho)
               if adjacente == fim:
                   return (novo_caminho)
    return []

########################## MAIN ##############################

grafo = {}


input = sys.stdin.readline().strip().split(' ')

start = input[0]
finish = input[1]

for input in sys.stdin:
	input = input.strip().split(' ')
	if input:
		grafo[input[0]]=input[1:]
	else:
		break

print(busca(grafo,start,finish,caminho=[]))