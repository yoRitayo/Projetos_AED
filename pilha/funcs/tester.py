import pilha
import organiza

numeroElementos = int(input("Digite o número de elementos a inserir: "))

pilhaUsuario = pilha.PilhaEstatica()

for i in range(numeroElementos):
    numInserido = int(input("Digite um número:"))
    pilhaUsuario.push(numInserido)

# Reorganizando a lista utilizando as pilhas no método organize  de organiza.py

print("A lista inserida em ordem decrescente é:")
organiza.organize(pilhaUsuario)