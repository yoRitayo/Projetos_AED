#include <iostream>
#include <list>

typedef unsigned int Vertex;

class GraphAL {
    unsigned int num_vertices;
    unsigned int num_edges;
    std::list<Vertex> *adj_list;

public:
    GraphAL(unsigned int numVertices);
    ~GraphAL();
    void add_edge(Vertex u, Vertex v);
    void remove_edge(Vertex u, Vertex v);
    void input_graph(GraphAL &g, Vertex u, Vertex v);
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

GraphAL::GraphAL(unsigned int numVertices) {
    num_vertices = numVertices;
    num_edges = 0;
    adj_list = new std::list<Vertex>[numVertices];
}

GraphAL::~GraphAL() {
    for (unsigned int i = 0; i < num_vertices; ++i) {
        adj_list[i].clear();
    }
    delete[] adj_list;
    adj_list = nullptr;
    num_vertices = num_edges = 0;
}

void GraphAL::add_edge(Vertex u, Vertex v) {
    adj_list[u].push_back(v);
    adj_list[v].push_back(u);
    num_edges++;
}

void GraphAL::remove_edge(Vertex u, Vertex v) {
    for (auto it = adj_list[u].begin(); it != adj_list[u].end(); ++it) {
        if (*it == v) {
            adj_list[u].erase(it);
            break;
        }
    }

    for (auto it = adj_list[v].begin(); it != adj_list[v].end(); ++it) {
        if (*it == u) {
            adj_list[v].erase(it);
            break;
        }
    }

    num_edges--;
}

void GraphAL::input_graph(GraphAL &g, Vertex u, Vertex v) {
    g.add_edge(u, v);
}

void GraphAL::display_graph() {
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
    GraphAL graph(num_vertices);

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
