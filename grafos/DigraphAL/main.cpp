#include <iostream>
#include <list>

typedef unsigned int Vertex;

class DiagraphAL {
    unsigned int num_vertices;
    unsigned int num_edges;
    std::list<Vertex> *adj_list;

public:
    DiagraphAL(unsigned int numVertices);
    ~DiagraphAL();
    void add_edge(Vertex u, Vertex v);
    void remove_edge(Vertex u, Vertex v);
    void input_graph(DiagraphAL &g, Vertex u, Vertex v);
    void display_graph();

    unsigned int get_num_vertices() {
        return num_vertices;
    }

    unsigned int get_num_edges() {
        return num_edges;
    }
    std::list<Vertex> *get_adj_list() {
        return adj_list;
    }

};

DiagraphAL::DiagraphAL(unsigned int numVertices) {
    num_vertices = numVertices;
    num_edges = 0;
    adj_list = new std::list<Vertex>[numVertices];
}

DiagraphAL::~DiagraphAL() {
    for (unsigned int i = 0; i < num_vertices; ++i) {
        adj_list[i].clear();
    }
    delete[] adj_list;
    adj_list = nullptr;
    num_vertices = num_edges = 0;
}

void DiagraphAL::add_edge(Vertex u, Vertex v) {
    bool sentinela = true;

    if (u == v) {
        sentinela = false;
        num_edges--;
    }

    for (auto i = adj_list[u].begin(); i != adj_list[u].end(); ++i) {
        if (*i == v) {
            sentinela = false;
            num_edges++;
        }
    }

    if (sentinela) {
        adj_list[u].push_back(v);
        num_edges++;
    }
}

void DiagraphAL::remove_edge(Vertex u, Vertex v) {
    for (auto it = adj_list[u].begin(); it != adj_list[u].end(); ++it) {
        if (*it == v) {
            adj_list[u].erase(it);
            break;
        }
    }

    num_edges--;
}

void DiagraphAL::input_graph(DiagraphAL &g, Vertex u, Vertex v) {
    g.add_edge(u, v);
}

void DiagraphAL::display_graph() {
    for (unsigned int i = 0; i < num_vertices; ++i) {
        std::cout << i << ": ";
        for (auto it = adj_list[i].begin(); it != adj_list[i].end(); ++it) {
            std::cout << *it << ", ";
        }
        std::cout << std::endl;
    }
}


int main()
{
    unsigned int num_vertices;
    std::cin >> num_vertices;
    DiagraphAL graph(num_vertices);

    unsigned int num_edges;
    std::cin >> num_edges;

    for (unsigned int i = 0; i < num_edges; ++i) {
        int vertex1, vertex2;

        std::cin >> vertex1;
        std::cin >> vertex2;

        graph.input_graph(graph, vertex1, vertex2);
    }
    std::cout << "num_vertices: " << graph.get_num_vertices() << std::endl;
    std::cout << "num_edges: " << graph.get_num_edges() << std:: endl;
    graph.display_graph();

    return 0;
}
