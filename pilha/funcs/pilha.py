class No:
    def __init__(self, dado):
        self.dado = dado
        self.proximo = None


# novono = novo nó

class PilhaEstatica:
    def __init__(self):
        self.data = []

    def __len__(self):
        return len(self.data)

    def is_empty(self):
        return len(self.data) == 0

    def push(self, e):
        return self.data.append(e)

    def top(self):
        if self.is_empty() is False:
            return self.data[-1]

    def pop(self):
        if self.is_empty() is False:
            return self.data.pop()


class PilhaDinamica:
    def __init__(self):
        self.cabeca = None

    def __len__(self):
        soma = 0
        if self.cabeca is None:
            return soma
        noatual = self.cabeca
        while noatual is not None:
            noatual = noatual.proximo
            soma += 1
        return soma

    def is_empty(self):
        return self.cabeca is None

    def push(self, data):
        novono = No(data)
        if self.is_empty() is True:
            self.cabeca = novono
            return
        ultimono = self.cabeca
        while ultimono.proximo is not None:
            ultimono = ultimono.proximo
        ultimono.proximo = novono
        #Aqui cê pode retornar o novo nó ou printá-lo

    def top(self):
        if self.is_empty() is True:
            return
        ultimono = self.cabeca
        while ultimono.proximo is not None:
            ultimono = ultimono.proximo
        return ultimono.dado

    def pop(self):
        if self.is_empty() is True:
            return

        novono = self.cabeca
        anterior = None

        while novono.proximo is not None:
            anterior = novono
            novono = novono.proximo

        if anterior is not None:
            anterior.proximo = None
        else:
            self.cabeca = None

        return novono.dado

    def free(self):
        self.cabeca = None
        return
