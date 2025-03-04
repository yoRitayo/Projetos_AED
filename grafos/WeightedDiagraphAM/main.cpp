#include <iostream>
#include <list>
#include <limits>

typedef unsigned int Vertex;
typedef float Weight;

class WeightedDigraphAM {
    unsigned int num_vertices;
    unsigned int num_edges;
    Weight** adj_matrix;
public:
    WeightedDigraphAM(unsigned int num_vertices);
    ~WeightedDigraphAM();
    void add_edge(Vertex u, Vertex v, Weight w);
    void remove_edge(Vertex u, Vertex v);
    void input_graph(WeightedDigraphAM &g, Vertex u, Vertex v, Weight w);
    void display_graph();

    unsigned int get_num_vertices() {
        return num_vertices;
    }
    unsigned int get_num_edges() {
        return num_edges;
    }

    Weight** get_adj_matrix() {
        return adj_matrix;
    }

    Weight get_weight_edge(Vertex u, Vertex v) {
        return adj_matrix[u][v];
    }

};

WeightedDigraphAM::WeightedDigraphAM(unsigned int numVertices) {
    num_vertices = numVertices;
    num_edges = 0;

    adj_matrix = new Weight*[num_vertices];

    float num = std::numeric_limits<float>::infinity();

    for (unsigned int i = 0; i < num_vertices; i++) {
        adj_matrix[i] = new Weight[num_vertices];
    }

    for (unsigned int i = 0; i < num_vertices; i++) {
        for (unsigned int j = 0; j < num_vertices; j++) {
            adj_matrix[i][j] = num;
        }
    }
}

WeightedDigraphAM::~WeightedDigraphAM() {
    for (unsigned int i = 0; i < num_vertices; i++) {
        delete[] adj_matrix[i];
    }
    delete[] adj_matrix;
    num_vertices = num_edges = 0;
}

void WeightedDigraphAM::add_edge(Vertex u, Vertex v, Weight w) {
    bool sentinela = true;
    if (adj_matrix[u][v] != std::numeric_limits<Weight>::infinity()) {
        sentinela = false;
    }

    if (sentinela) {
        adj_matrix[u][v] = w;
        num_edges++;
    }
}

void WeightedDigraphAM::remove_edge(Vertex u, Vertex v) {
    float num = std::numeric_limits<float>::infinity();

    adj_matrix[u][v] = num;
    num_edges--;
}

void WeightedDigraphAM::input_graph(WeightedDigraphAM &g, Vertex u, Vertex v, Weight w) {
    g.add_edge(u, v, w);
}

void WeightedDigraphAM::display_graph() {
    for (unsigned int i = 0; i < num_vertices; i++) {
        for (unsigned int j = 0; j < num_vertices; j++) {
            std::cout << adj_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    unsigned int num_vertices;
    std::cin >> num_vertices;
    WeightedDigraphAM graph(num_vertices);

    unsigned int numEdges;
    std::cin >> numEdges;

    for (unsigned int i = 0; i < numEdges; i++) {
        int vertex1, vertex2;
        float weight;

        std::cin >> vertex1;
        std::cin >> vertex2;
        std::cin >> weight;

        graph.input_graph(graph, vertex1, vertex2, weight);
    }

    std::cout << "num_vertices: " << graph.get_num_vertices() << std::endl;
    std::cout << "num_edges: " << graph.get_num_edges() << std:: endl;
    graph.display_graph();

    return 0;
}
