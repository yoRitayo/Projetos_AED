#include <iostream>
#include <vector>
using namespace std;

const int TAM_ALFABETO_ASCII = 256;

class StringMatching {
    string p;
    string t_encriptado;
    string t_descriptografado;
    int chaveK;
    int *array = new int[TAM_ALFABETO_ASCII - 1];

public:
    explicit StringMatching(const string &texto, const string &padrao): p(padrao), t_encriptado(texto) {}
    ~StringMatching() {
        delete[] array;
    }

    void encontrarChaveK() {
        int cont = 0;
        string palavra_inicial;
        string palavra_inicial_copiada;

        for (size_t i = 0; i < t_encriptado.size(); i++) {
            if (t_encriptado[i] == ' ') {
                palavra_inicial = t_encriptado.substr(0, cont);
                break;
            } else {
                cont++;
            }
        }

        for (size_t i = 0; i < TAM_ALFABETO_ASCII; i++) {
            palavra_inicial_copiada = palavra_inicial;

            for (size_t j = 0; j < palavra_inicial.size(); j++) {
                if (palavra_inicial_copiada[j] != ' ') {
                    if (palavra_inicial_copiada[j] - i < 'A') {
                        palavra_inicial_copiada[j] = 'Z' - ('A' - (palavra_inicial_copiada[j] - i - 1)) + 2;
                    } else {
                        palavra_inicial_copiada[j] -= i;
                    }
                }
            }

            if (palavra_inicial_copiada == "MENSAGEM") {
                chaveK = i;
                break;
            }
        }
    }

    void decodificar() {
       string decodificado;
        for (char c: t_encriptado) {
            if (c != ' ' && c!= '.') {
                decodificado += char((c - 'A' - chaveK + 26) % 26 + 'A');
            }else {
                decodificado += c;
            }
        }
        t_descriptografado = decodificado;
    }

    void computarTabelaSaltos() {
        for (size_t i = 0; i < TAM_ALFABETO_ASCII; i++) {
            array[i] = -1;
        }
        for (size_t j = 0; j < p.length(); j++) {
            array[p[j]] = j;
        }
    }

    void boyerMoore() {
        cout << p << ": ";
        computarTabelaSaltos();

        int n = t_descriptografado.length();
        int m = p.length();
        int salto;

        for (int i = 0; i <= n - m; i += salto) {
            salto = 0;
            for (int j = m - 1; j >= 0; j--) {
                if (p[j] != t_descriptografado[i + j]) {
                    salto = j - array[t_descriptografado[i + j]];
                    if (salto < 1) {
                        salto = 1;
                    }
                    break;
                }
            }
            cout << salto << " ";
            if (salto == 0) {
                cout << "(" << i << ")" << " ";
                salto = 1;
            }
        }
        cout << endl;
    }

    void execSM() {
        encontrarChaveK();
        decodificar();
        boyerMoore();
    }
};

int potencia(int base, int expoente) {
    int resultado = 1;
    for (int i = 0; i < expoente; ++i) {
        resultado *= base;
    }
    return resultado;
}

void Hash(vector<pair<string, char>> tabela[], const string &palavra, char letra) {
    int chaveH = (static_cast<int>(palavra[0]) * potencia(5, 2)) +
                 (static_cast<int>(palavra[1]) * potencia(5, 1)) +
                 (static_cast<int>(palavra[2]) * potencia(5, 0));
    chaveH = chaveH % 11;
    tabela[chaveH].push_back({palavra, letra});
}

void tabelaHash(vector<pair<string, char>> tabela[]) {
    Hash(tabela, ":::", 'A');
    Hash(tabela, ".::", 'B');
    Hash(tabela, ":.:", 'C');
    Hash(tabela, "::.", 'D');
    Hash(tabela, ":..", 'E');
    Hash(tabela, ".:.", 'F');
    Hash(tabela, "..:", 'G');
    Hash(tabela, "...", 'H');
    Hash(tabela, "|::", 'I');
    Hash(tabela, ":|:", 'J');
    Hash(tabela, "::|", 'K');
    Hash(tabela, "|.:", 'L');
    Hash(tabela, ".|:", 'M');
    Hash(tabela, ".:|", 'N');
    Hash(tabela, "|:.", 'O');
    Hash(tabela, ":|.", 'P');
    Hash(tabela, ":.|", 'Q');
    Hash(tabela, "|..", 'R');
    Hash(tabela, ".|.", 'S');
    Hash(tabela, "..|", 'T');
    Hash(tabela, ".||", 'U');
    Hash(tabela, "|.|", 'V');
    Hash(tabela, "||.", 'W');
    Hash(tabela, "-.-", 'X');
    Hash(tabela, ".--", 'Y');
    Hash(tabela, "--.", 'Z');
    Hash(tabela, "---", ' ');
    Hash(tabela, "~~~", '.');
}

string ArtefatoLatim(vector<pair<string, char>> tabela[], const string &texto) {
    string traducao;
    for (size_t i = 0; i < texto.length(); i += 3) {
        string parte = texto.substr(i, 3);
        for (int j = 0; j < 11; ++j) {
            for (const auto &par : tabela[j]) {
                if (parte == par.first) {
                    traducao += par.second;
                    break;
                }
            }
        }
    }
    return traducao;
}

string upperCase(string &texto) {
    for (auto &c : texto) {
        c = toupper(c);
    }
    return texto;
}

int main() {
    vector<pair<string, char>> tabela[11];
    tabelaHash(tabela);
    string textoCodificado;
    getline(cin, textoCodificado);
    string resultado = ArtefatoLatim(tabela, textoCodificado);

    string padrao;
    while (true) {
        getline(cin, padrao);
        upperCase(padrao);
        if (padrao == "FIM") {
            break;
        }
        StringMatching sm(resultado, padrao);
        sm.execSM();
    }
    return 0;
}