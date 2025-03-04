//
// Created by ritab on 09/11/2024.
//

#include <iostream>
#include <list>
#include <limits>

class Aresta;
class Grafo;

using namespace std;

//Será utilizado no grafo de neurônios.
typedef pair<int , int> parVertices;

class SetDisjunto{
    int *parente, *rank;
    int n;

    public:

    explicit SetDisjunto(int n) {
        this->n = n;
        parente = new int[n+1]; //array com índices de 0 a n
        rank = new int[n+1]; //array com índices de 0 a n
        makeSet();
    }
    ~SetDisjunto() {
        delete[] parente;
        delete[] rank;
    }
    void makeSet() {
        for (int i = 0; i <= n; i++) {
            rank[i] = 0;
            parente[i] = i;
        }
    }

    int find(int i) {
        if (parente[i] == i) {
            return i; //se o i é o representante dele mesmo
        }
        int resultado = find(parente[i]);
        parente[i] = resultado;
        return resultado;
    }

    void unionByRank(int i, int j) {
        int u = find(i);  //irank
        int v = find(j); //jrank

        if (u == v)
            return; //elementos no mesmo set não precisam ser unidos

        if (rank[u] < rank[v]) {
            parente[u] = v;
        }else if (rank[v] < rank[u]) {
            parente[v] = u;
        }else {
            parente[u] = v;
            rank[v]++;
        }
    }
};

//kruskal está dentro de um grafo neurônio
class GrafoNeuronio {
    int numVertices, numArestas;
    list<pair<float, parVertices>> arestas;

    public:
    GrafoNeuronio(int v, int a) {
        this->numVertices = v;
        this->numArestas = a;
    }
    ~GrafoNeuronio() = default;

    list<pair<float, parVertices>> &getArestas() {
        return arestas;
    }

    void adicionarAresta(int u, int v, float peso) {
        arestas.push_back({peso, {u, v}});
    }

    float kruskalMST() {
        float mst_soma = 0.0;
        arestas.sort();
        SetDisjunto d(numVertices); //olhar o construtor do setDisjunto

        list<pair<float, parVertices>>::iterator it;
        for (it = arestas.begin(); it != arestas.end(); ++it) {
            int u = it->second.first; //pega o índice do vértice 1
            int v = it->second.second; //pega o índice do vértice 2

            int set_u = d.find(u);
            int set_v = d.find(v);

            //Checar se as arestas do set estão criando um ciclo ou não (Ciclo é criado se u e v pertencem ao mesmo set)
            if (set_u != set_v) {
                cout << u << " - " << v << endl; //essa aresta entra na mst e por agora vou printar
                mst_soma += it->first; //pega o peso da aresta
                d.unionByRank(set_u, set_v);
            }
        }
        return mst_soma;
    }
};

class Vertice {
    int index;
    bool doente = false;
    float distancia = numeric_limits<float>::infinity();
    list<Vertice*> verticesAdj;
    Vertice *pi = nullptr;
    GrafoNeuronio *subgrafo = nullptr;
    list<Vertice*> caminhoMinimo;

    public:
    explicit Vertice(int indexVertice): index(indexVertice){}
    ~Vertice() = default;

    [[nodiscard]] int getIndex() const {
        return index;
    }
    void setDoente() {
        doente = true;
    }
    [[nodiscard]] bool getDoente() const {
        return doente;
    }
    void setDistancia(float distancia) {
        this->distancia = distancia;
    }
    [[nodiscard]] float getDistancia() const {
        return distancia;
    }
    list<Vertice*>& getVerticesAdj(){
        return verticesAdj;
    }
    void setPi(Vertice &v) {
        this->pi = &v;
    }

    void setSubgrafo(GrafoNeuronio &gn) {
        this->subgrafo = &gn;
    }

    GrafoNeuronio &getSubgrafo() {
        return *subgrafo;
    }

    [[nodiscard]] Vertice* getPi() const {
        return pi;
    }

    void printarCaminhoMin() {
        if (this-> getPi() == nullptr) {
            cout << "Caminho mínimo não existe";
        }else {
            if (this == this->getPi()) { //se o vértice atual é o mesmo que o predecessor, chegou-se ao vértice inicial
                cout << this->getPi()->getIndex() << " " << "(" << this->getDistancia() << ")";
            }else {
                this->getPi()->printarCaminhoMin();
                cout << " -> " << this->getIndex() << " " << "(" << this->getDistancia() << ")";
            }
        }
    }

    void adicionarCaminhoMin(list<Vertice*>&caminho) {
        if (this->getPi() == nullptr) {
            cout << "Caminho mínimo não existe";
        } else {
            if (this != this->getPi()) {
                this->getPi()->adicionarCaminhoMin(caminho);
            }
            caminho.push_back(this);
        }
    }

};

class Aresta {
    Vertice *v1;
    Vertice *v2;
    float distancia;

public:
    Aresta(Vertice &vertice1, Vertice &vertice2, float distancia) : v1(&vertice1), v2(&vertice2), distancia(distancia) {}
    ~Aresta() = default;
    [[nodiscard]] float getPeso() const{
        return distancia;
    }
    [[nodiscard]] Vertice* getV1() const {
        return v1;
    }
    [[nodiscard]] Vertice* getV2() const {
        return v2;
    }
};

class Grafo{
    int numeroVertices;
    int numeroArestas;
    list<Vertice*> vertices;
    list<Aresta*> arestas;

    public:
    Grafo(): numeroVertices(0), numeroArestas(0){}

    ~Grafo(){
        for (auto &v: vertices) {
            delete v;
        }
        for (auto &a: arestas) {
            delete a;
        }
    }

    void insertVertice(Vertice *v) {
        vertices.push_back(v);
        numeroVertices++;
    }

    void insertAresta(Aresta *a) {
        a->getV1()->getVerticesAdj().push_back(a->getV2());
        a->getV2()->getVerticesAdj().push_back(a->getV1());

        this->arestas.push_back(a);
        numeroArestas++;
    }
    int getNumeroVertices(){
        return numeroVertices;
    }
    int getNumeroArestas(){
        return numeroArestas;
    }
    list<Vertice*>&getVertices(){
        return vertices;
    }
    list<Aresta*>&getArestas(){
        return arestas;
    }

    Aresta& getAresta(Vertice &v1, Vertice &v2) {
        for (auto &a : arestas) {
            if ((a->getV1() == &v1 && a->getV2() == &v2) || (a->getV1() == &v2 && a->getV2() == &v1)) {
                return *a;
            }
        }
        throw runtime_error("Aresta não encontrada");
    }

    Vertice& getVertice(int indexSaida) {
        for (auto &v: vertices) {
            if (v->getIndex() == indexSaida) {
                return *v;
            }
        }
        throw runtime_error("Vértice não encontrado");
    }

    void printarCaminho(int indexSaida) {
        getVertice(indexSaida).printarCaminhoMin();
    }
};

class FP{
    pair<Vertice*, float> *heap;
    int size;
    int heapSize;

public:
    explicit FP(int n) {
        heapSize = 0;
        size = n;
        heap = new pair<Vertice*, float>[n];
    }
    ~FP() {
        delete[] heap;
    }

    static void trocar(pair<Vertice*, float>&x, pair<Vertice*, float>&y) {
        pair<Vertice*, float> temp = x;
        x = y;
        y = temp;
    }

    void minHeapify(int i) {
        int e = esquerda(i);
        int d = direita(i);
        int menor = i;

        if (e < heapSize && heap[e].second < heap[menor].second){
            menor = e;
        }
        if (d < heapSize && heap[d].second < heap[menor].second){
            menor = d;
        } if (menor != i) {
            trocar(heap[i], heap[menor]);
            minHeapify(menor);
        }
    }

    Vertice* extrairMinimo() {
        if (estaVazio() == true) {
            return nullptr;
        }
        if (heapSize == 1) {
            heapSize--;
            return heap[0].first;
        }
        pair<Vertice*, float> raiz= heap[0];
        heap[0]= heap[heapSize - 1];
        heapSize--;
        minHeapify(0);
        return raiz.first;
    }

    void inserir(pair<Vertice*, float> a) {
        if (heapSize == size) {
            return;
        }
        heapSize++;
        int i = heapSize - 1;
        heap[i] = a;
        while (i != 0 && heap[parente(i)].second > heap[i].second) {
            trocar(heap[i], heap[parente(i)]);
            i = parente(i);
        }
    }
    void decrescerChave(int a, float n) {
        int i = encontrarElemento(a);
        if (i != -1) {
            heap[i].second = n;
            while (i != 0 && heap[parente(i)].second > heap[i].second) {
                trocar(heap[i], heap[parente(i)]);
                i = parente(i);
            }
        }
    }

    void buildMinHeap(){
        for (int i = heapSize / 2; i >= 0; i--) {
            minHeapify(i);
        }
    }

    [[nodiscard]] bool estaVazio() const {
        if (heapSize == 0) {
            return true;
        }
        return false;
    }

    int encontrarElemento(int index) {
        for (int i = 0; i < heapSize; i++) {
            if (heap[i].first->getIndex() == index) {
                return i;
            }
        }
        return -1;
    }

    int parente(int i) {
        return (i) / 2;
    }
    int esquerda (int i) {
        return 2*i;
    }
    int direita (int i) {
        return 2*i+1;
    }

};


class Djikstra {
    Grafo *g;
    FP fila;
    list<Vertice*> caminhoMinimo;

    public:
    explicit Djikstra(Grafo &grafo): g(&grafo), fila(grafo.getNumeroVertices()) {
        this->g = &grafo;
    }
    void inserirVerticesHeap() {
        for (auto &v: g->getVertices()) {
            pair<Vertice*,float> a = make_pair(v, v->getDistancia());
            fila.inserir(a);
        }
    }
    void iniciarDijkstra(int indexEntrada) {
        Vertice &s = g->getVertice(indexEntrada);
        s.setDistancia(0.0);
        s.setPi(s);
        inserirVerticesHeap();
        while (fila.estaVazio() == false) {
            Vertice *u = fila.extrairMinimo();
            for (Vertice *v: u->getVerticesAdj()) {
                Aresta a = g->getAresta(*u, *v);
                relaxa(*u, *v, a.getPeso());
            }
        }
    }

    void relaxa(Vertice &v1, Vertice &v2, float distancia) {
        if (v2.getDistancia() > v1.getDistancia() + distancia) {
            v2.setDistancia(v1.getDistancia() + distancia);
            v2.setPi(v1);
            fila.decrescerChave(v2.getIndex(), v2.getDistancia());
        }
    }

    void imprimirResultado(Grafo &grafo, int indexSaida) {
        float Mst_total = 0.0;
        grafo.getVertice(indexSaida).adicionarCaminhoMin(caminhoMinimo);
        for (auto *v: caminhoMinimo) {
            if (v->getDoente() == true) {
                float mst_peso = v->getSubgrafo().kruskalMST();
                Mst_total += mst_peso;
            }
        }
        cout << Mst_total;
    }
};

int main() {
    Grafo cerebro;
    int ordemCerebro, tamanhoCerebro, index1, index2, indexEntrada, indexSaida;
    int ordemBloco, tamanhoBloco, numNeuroniosDoentes, indexNeuronioDoente;
    float distancia;
    cin >> ordemCerebro >> tamanhoCerebro;

    for (int i = 1; i <= ordemCerebro; i++) {
        auto bloco = new Vertice(i);
        cerebro.insertVertice(bloco);
    }

    for (int i = 1; i <= tamanhoCerebro; i++) {
        cin >> index1 >> index2 >> distancia;
        Vertice &v1 = cerebro.getVertice(index1);
        Vertice &v2 = cerebro.getVertice(index2);

        auto a = new Aresta(v1, v2, distancia);
        cerebro.insertAresta(a);
    }

    cin >> indexEntrada >> indexSaida;

    //Criando um grafo de neurônios para cada vértice do cérebro
    for (auto v: cerebro.getVertices()) {
        cin >> ordemBloco >> tamanhoBloco;
        auto *gn = new GrafoNeuronio(ordemBloco, tamanhoBloco);
        v->setSubgrafo(*gn);
        cin >> numNeuroniosDoentes;

        if (numNeuroniosDoentes != 0) {
            v->setDoente();
            for (int i = 0; i < numNeuroniosDoentes; i++) {
                cin >> indexNeuronioDoente;
            }
        }

        for (int i =1; i <= tamanhoBloco; i++) {
            cin >> index1 >> index2 >> distancia;
            v->getSubgrafo().adicionarAresta(index1, index2, distancia);
        }
    }

    cout << "Index Entrada: " << indexEntrada << " Index Saida: " << indexSaida << endl;

    Djikstra djikstra(cerebro);
    djikstra.iniciarDijkstra(indexEntrada);
    cerebro.printarCaminho(indexSaida);
    cout << endl;
    djikstra.imprimirResultado(cerebro, indexSaida);
}