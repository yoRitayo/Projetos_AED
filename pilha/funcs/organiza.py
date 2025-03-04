import pilha

# Considerando que uma pilha vai ser inserida
def organize(pilha_esta):

    pilha_temp = pilha.PilhaDinamica()

    while not (pilha_esta.is_empty()):

        if (pilha_temp.is_empty()):
            pilha_temp.push(pilha_esta.pop())

        else:

            topo = pilha_temp.top()
            num_a_inserir = pilha_esta.pop()

            while not (topo <= num_a_inserir):

                topo_anterior = pilha_temp.pop()
                var_temp = topo_anterior
                pilha_esta.push(var_temp)

                topo = pilha_temp.top()

                if (pilha_temp.is_empty()):
                    break

            pilha_temp.push(num_a_inserir)

    while not (pilha_temp.is_empty()):
        pilha_esta.push(pilha_temp.pop())

    print(pilha_esta.data)