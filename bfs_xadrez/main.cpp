#include <iostream>
#include <list>

using namespace std;

class VertexTabuleiro {
    pair<int, int> coordenadas;
    string casaTabuleiro;

public:

    void setCoordenadas(int col, int lin){
        coordenadas.first = col;
        coordenadas.second = lin;

        char coluna = 'a' + (col - 1);
        char linha = '1' + (lin - 1);

        casaTabuleiro = string(1, coluna) + string(1, linha);
    }

    string getCasa() {
        return casaTabuleiro;
    }

    void setLin(int lin) {
        coordenadas.second = lin;
    }

    void setCol(int col) {
        coordenadas.first = col;
    }

    int getLin(){
        return coordenadas.second;
    }

    int getCol(){
        return coordenadas.first;
    }
};

class Vertex : public VertexTabuleiro {
    list<string> listaAdj;
    string cor = "Branco"; //
    unsigned int d = 0; //

    public:
    Vertex(int col, int lin){
        setCoordenadas(col, lin);
    }

    virtual ~Vertex() = default;

    list<string> &getListaAdj(){
        return listaAdj;
    }

    string getCor(){
        return cor;
    }

    unsigned int getD(){
        return d;
    }

    void setD(unsigned int dist) {
        d = dist;
    }

    void colorirCinza() {//
        cor = "Cinza";
    }

    void colorirPreto() {//
        cor = "Preto";
    }

    void adicionarAdj(string s) {
        listaAdj.push_back(s);
    }

};

class Tabuleiro {
public:
    Tabuleiro() = default;
    virtual ~Tabuleiro() = default;

    string coordPrString(int col, int lin) {
        if (col < 1 || col > 8 || lin < 1 || lin > 8) {
            return "";  // Valores fora do tabuleiro são inválidos
        }

        char coluna = 'a' + (col - 1);
        char linha = '1' + (lin - 1);

        string casaTabuleiro = string(1, coluna) + string(1, linha);
        return casaTabuleiro;
    }

    void montarTabuleiro(list<Vertex> &listaVertices) {
        for (int lin = 1; lin <= 8; lin++) {
            for (int col = 1; col <= 8; col++) {
                Vertex v(col, lin);
                listaVertices.push_back(v);
            }
        }
    }

    void setarListasAdj(list<Vertex> &listaVertices) {
        for (auto &v : listaVertices) {
            montarListaAdj(v);
        }
    }

    bool coordenadaValida(int col, int lin) {
        if (lin > 8 || lin < 1 || col > 8 || col < 1) {
            return false;
        }

        return true;
    }

    void moverEsquerdaNorte(Vertex &u) {
        int col = u.getCol();
        int lin = u.getLin();

        int linha = lin + 2;
        int coluna = col - 1;

        if (!coordPrString(coluna, linha).empty() && (coordenadaValida(coluna, linha))) {

            u.getListaAdj().push_back(coordPrString(coluna, linha));
        }
    }

    void moverEsquerdaNoroeste(Vertex &u) {
        int col = u.getCol();
        int lin = u.getLin();

        int linha = lin + 1;
        int coluna = col - 2;

        if (!coordPrString(coluna, linha).empty() && (coordenadaValida(coluna, linha))) {

            u.getListaAdj().push_back(coordPrString(coluna, linha));
        }
    }

    void moverDireitaNorte(Vertex &u) {
        int col = u.getCol();
        int lin = u.getLin();

        int linha = lin + 2;
        int coluna = col + 1;
        if (!coordPrString(coluna, linha).empty() && (coordenadaValida(coluna, linha))) {

            u.getListaAdj().push_back(coordPrString(coluna, linha));
        }
    }

    void moverDireitaNordeste(Vertex &u) {
        int col = u.getCol();
        int lin = u.getLin();

        int linha = lin + 1;
        int coluna = col + 2;
        if (!coordPrString(coluna, linha).empty() && (coordenadaValida(coluna, linha))) {

            u.getListaAdj().push_back(coordPrString(coluna, linha));
        }
    }

    void moverEsquerdaSul(Vertex &u) {
        int col = u.getCol();
        int lin = u.getLin();

        int linha = lin - 2;
        int coluna = col - 1;

        if (!coordPrString(coluna, linha).empty() && (coordenadaValida(coluna, linha))) {

            u.getListaAdj().push_back(coordPrString(coluna, linha));
        }
    }

    void moverEsquerdaSudoeste(Vertex &u) {
        int col = u.getCol();
        int lin = u.getLin();

        int linha = lin - 1;
        int coluna = col - 2;

        if (!coordPrString(coluna, linha).empty() && (coordenadaValida(coluna, linha))) {

            u.getListaAdj().push_back(coordPrString(coluna, linha));
        }

    }

    void moverDireitaSul(Vertex &u) {
        int col = u.getCol();
        int lin = u.getLin();

        int linha = lin - 2;
        int coluna = col + 1;
        if (!coordPrString(coluna, linha).empty() && (coordenadaValida(coluna, linha))) {
            u.getListaAdj().push_back(coordPrString(coluna, linha));
        }
    }

    void moverDireitaSudeste(Vertex &u) {
        int col = u.getCol();
        int lin = u.getLin();

        int linha = lin - 1;
        int coluna = col + 2;

        if (!coordPrString(coluna, linha).empty() && (coordenadaValida(coluna, linha))) {
            u.getListaAdj().push_back(coordPrString(coluna, linha));
        }
    }

    void montarListaAdj(Vertex &u) {
        moverEsquerdaSudoeste(u);
        moverEsquerdaNoroeste(u);
        moverEsquerdaSul(u);
        moverEsquerdaNorte(u);
        moverDireitaSul(u);
        moverDireitaNorte(u);
        moverDireitaSudeste(u);
        moverDireitaNordeste(u);
    }
};

class Grafo : public Tabuleiro{
    unsigned int numVertices;
    list<Vertex> vertices;

    public:
    explicit Grafo(unsigned int numVertices): Tabuleiro() {
        this->numVertices = numVertices;
    }

    virtual ~Grafo() = default;

    void adicionarVertex(Vertex u){
        vertices.push_back(u);
    }

    void displayGrafo(){
        for (auto v : vertices) {
            cout << v.getCasa() << ": ";
            for (auto it2 : v.getListaAdj()) {
                cout << it2 << ", ";
            }
            cout << endl;
        }
    }

    list<Vertex> &getVertices(){
        return vertices;
    }

    Vertex &buscarVertex(string rotulo) {
        for (auto &vertice : vertices) {
            if (vertice.getCasa() == rotulo) {
                return vertice;
            }
        }
        throw runtime_error("Não foi possível encontrar o vértice");
    }
};

void bfs(Grafo &g, Vertex &s) {
    list<Vertex*> fila;

    s.colorirCinza();
    fila.push_back(&s);

    //Checar as distâncias do vértices que contém cavalos após a busca.
    while (!fila.empty()) {
        Vertex *u = fila.front();
        fila.pop_front();

        for (auto &v: u->getListaAdj()) {
            Vertex *verticeAdj = &g.buscarVertex(v);
            if (verticeAdj->getCor() == "Branco"){
                verticeAdj->colorirCinza();
                verticeAdj->setD(u->getD() + 1);
                fila.push_back(verticeAdj);
            }
        }
        u->colorirPreto();
    }
        // cout << "bfs terminou" << endl;
    }

void printCaminhoMinimo(Grafo &g) {
    for (auto &u : g.getVertices()) {
        cout << "Movimentos mínimos de " << u.getCasa() << " até o vértice start (s): " << u.getD() << endl;
    }
}

list<string> obterAdjRei(Grafo &g, Vertex &posRei) {
    list<string> strings;
    for (auto &u : g.getVertices()) {
        if (u.getCasa() == posRei.getCasa()) {
            Vertex &rei = u;
            for (auto &s: rei.getListaAdj()) {
                strings.push_back(s);
            }
        }
    }
    return strings; //retorna as posições que serão usadas para a bsf do Rei.
}
//fazer o bfs em relação as posições nas quais o rei pode ser atacado, então subtrair de 1 para não contar o ataque do cavalo
 void obterDAtaque(Grafo &g,  string posCav1, string posCav2, string posCav3, string posCav4) {
     list <unsigned int> lista;

    //estou buscando para todos os cavalos, mas quero a menor
    //distancia

    for (auto &u : g.getVertices()) {
        if (u.getCasa() == posCav1 || u.getCasa() == posCav2 || u.getCasa() == posCav3 || u.getCasa() == posCav4) {
            unsigned int dis = u.getD();
            dis --;
            // cout << dis << " ";
            lista.push_back(dis);
        }
    }

    //considerando que todos os casos foram analisados
     // cout << endl;

     //Encontrando o mínimo
     unsigned int cont = 0;

     while (lista.size() != 1) {
         if (lista.front() < lista.back()) {
             lista.pop_back();
         }else if (lista.front() > lista.back()) {
             lista.pop_front();
             cont = 0;
         }else if (lista.front() == lista.back()) {
             cont ++;
             lista.pop_back();
         }
     }

     unsigned int min = lista.front();

     for (int i = 0; i <= cont; i++) {
         cout << min << " ";
     }

     cout << endl;
 }

//void solucao
pair<int, int> stringPrCoord(string s) {
    int coluna = s[0] - 'a' + 1;
    int linha = s[1] - '0';

    pair<int, int> coord;
    coord.first = coluna;
    coord.second = linha;

    return coord;
}

int main()
{
    // int numTestes;
    // cin >> numTestes;

    // for (int i = 0; i < numTestes; i++) {
        string rei;
        // string cav1, cav2, cav3, cav4;

        // cin >> numTestes;
        //
        // cout << "Numero de testes: " << numTestes << endl;

        // for (int i = 0; i <= numTestes; i++) {

        // cin >> cav1;
        // cin >> cav2;
        // cin >> cav3;
        // cin >> cav4;

        // pair<int, int> coordcav1 = stringPrCoord(cav1);
        // pair<int, int> coordcav2 = stringPrCoord(cav2);
        // pair<int, int> coordcav3 = stringPrCoord(cav3);
        // pair<int, int> coordcav4 = stringPrCoord(cav4);

        // cout << cav1 << " " << cav2 << " " << cav3 << " " << cav4 << " " << rei << endl;

        Grafo g(64);
        g.montarTabuleiro(g.getVertices());
        g.setarListasAdj(g.getVertices());

        g.displayGrafo();

        cin >> rei;
        Vertex &vRei = g.buscarVertex(rei);
        bfs(g, vRei);
        printCaminhoMinimo(g);
        // list<string> adjacencias = obterAdjRei(g, vRei);

        // for (auto &str: adjacencias) {
        //     cout << str << endl;
        // } //funciona

        // obterDAtaque(g, cav1, cav2, cav3, cav4);
    // }
    return 0;
}
