#include <iostream>

typedef unsigned int Vertex;
typedef float Weight;

class WeightedGraphAM {
    unsigned int num_vertices;
    unsigned int num_edges;
    Weight** adj_matrix;
public:
    WeightedGraphAM(unsigned int num_vertices);
    ~WeightedGraphAM();
    void add_edge(Vertex u, Vertex v, Weight w);
    void remove_edge(Vertex u, Vertex v);
    void input_graph(WeightedGraphAM &g, Vertex u, Vertex v);
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

    Weight get_weight(Vertex u, Vertex v) {
        return adj_matrix[u][v];
    }

};

WeightedGraphAM::WeightedGraphAM(unsigned int numVertices) {
    num_vertices = numVertices;
    num_edges = 0;

    adj_matrix = new Weight*[num_vertices];

    for (unsigned int i = 0; i < num_vertices; i++) {
        adj_matrix[i] = new Weight[num_vertices];
    }

    for (unsigned int i = 0; i < num_vertices; i++) {
        for (unsigned int j = 0; j < num_vertices; j++) {
            adj_matrix[i][j] = 0;
        }
    }
}

WeightedGraphAM::~WeightedGraphAM() {
    for (unsigned int i = 0; i < num_vertices; i++) {
        delete[] adj_matrix[i];
    }
    delete[] adj_matrix;
    num_vertices = num_edges = 0;
}

void WeightedGraphAM::add_edge(Vertex u, Vertex v, Weight w) {
    adj_matrix[u][v] = w;
    adj_matrix[v][u] = w;
    num_edges++;
}

void WeightedGraphAM::remove_edge(Vertex u, Vertex v) {
    adj_matrix[u][v] = 0;
    adj_matrix[v][u] = 0;
    num_edges--;
}

void WeightedGraphAM::input_graph(WeightedGraphAM &g, Vertex u, Vertex v) {
    g.add_edge(u, v, 1);
}

void WeightedGraphAM::display_graph() {
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
    GraphAM graph(num_vertices);

    unsigned int numEdges;
    std::cin >> numEdges;

    for (unsigned int i = 0; i < numEdges; i++) {
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
