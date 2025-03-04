#include <iostream>
#include <list>
using namespace std;

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


int main() {
    // //a = 1, b = 2, c = 3, d= 4, e= 5, f = 6, g = 7, h = 8, i = 9, 10 = j
    // SetDisjunto obj(10);
    // obj.unionByRank(1, 2);
    // obj.unionByRank(2, 4);
    // obj.unionByRank(3, 6);
    // obj.unionByRank(6, 9);
    // obj.unionByRank(5, 7);
    // obj.unionByRank(10, 5);
    //
    // if (obj.find(1) != obj.find(9)) {
    //     cout << "Correto" << endl;
    // }
    // if (obj.find(2) != obj.find(10)) {
    //     cout << "Correto" << endl;
    // }
    // if (obj.find(3) != obj.find(10)) {
    //     cout << "Correto" << endl;
    // }
    // if (obj.find(3) != obj.find(4)) {
    //     cout << "Correto" << endl;
    // }else {
    //     cout << "Nao consegui" << endl;
    // }
    // if (obj.find(5) == obj.find(10)) {
    //     cout << "Correto" << endl;
    // }
    // if (obj.find(8) != obj.find(6)) {
    //     cout << "Correto" << endl;
    // }

    int num_vertice = 9, num_arestas = 14;
    GrafoNeuronio gn(num_vertice, num_arestas);

    gn.adicionarAresta(0, 1, 4);
    gn.adicionarAresta(0, 7, 8);
    gn.adicionarAresta(1, 2, 8);
    gn.adicionarAresta(1, 7, 11);
    gn.adicionarAresta(2, 3, 7);
    gn.adicionarAresta(2, 8, 2);
    gn.adicionarAresta(2, 5, 4);
    gn.adicionarAresta(3, 4, 9);
    gn.adicionarAresta(3, 5, 14);
    gn.adicionarAresta(4, 5, 10);
    gn.adicionarAresta(5, 6, 2);
    gn.adicionarAresta(6, 7, 1);
    gn.adicionarAresta(6, 8, 6);
    gn.adicionarAresta(7, 8, 7);

    cout << "Arestas das mst sao \n";

    float mst_peso = gn.kruskalMST();
    cout << "Peso da MST e " << mst_peso;
    return 0;
}



