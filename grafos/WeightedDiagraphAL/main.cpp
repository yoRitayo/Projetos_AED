#include <iostream>
#include <list>

typedef unsigned int Vertex;
typedef float Weight;
typedef std::pair<Vertex, Weight> Pair;

class VertexWeightPair {
    Vertex vertex;
    Weight weight;

    public:
    VertexWeightPair(Vertex v, Weight w){
        vertex = v;
        weight = w;
    }

    Vertex getVertex() {
        return vertex;
    }
    Weight getWeight() {
        return weight;
    }
};

class WeightedDigraphAL {
    unsigned int num_vertices;
    unsigned int num_edges;
    std::list<VertexWeightPair> *adj_list;

public:
    WeightedDigraphAL(unsigned int numVertices);
    ~WeightedDigraphAL();
    void add_edge(Vertex u, Vertex v, Weight w);
    void remove_edge(Vertex u, Vertex v);
    void input_graph(WeightedDigraphAL &g, Vertex u, Vertex v, Weight w);
    void display_graph();

    unsigned int get_num_vertices() {
        return num_vertices;
    }

    unsigned int get_num_edges() {
        return num_edges;
    }
    std::list<VertexWeightPair> *get_adj_list() {
        return adj_list;
    }

};

WeightedDigraphAL::WeightedDigraphAL(unsigned int numVertices) {
    num_vertices = numVertices;
    num_edges = 0;
    adj_list = new std::list<VertexWeightPair>[numVertices];
}

WeightedDigraphAL::~WeightedDigraphAL() {
    for (unsigned int i = 0; i < num_vertices; ++i) {
        adj_list[i].clear();
    }
    delete[] adj_list;
    adj_list = nullptr;
    num_vertices = num_edges = 0;
}

void WeightedDigraphAL::add_edge(Vertex u, Vertex v, Weight w) {
    bool sentinela = true;
    if (u == v) {
        sentinela = false;
        num_vertices--;
    }

    for (auto it = adj_list[u].begin(); it != adj_list[u].end(); it++) {
        if ((*it).getVertex() == v) {
            sentinela = false;
            num_edges++;
        }
    }

    if (sentinela) {
        adj_list[u].push_back({v, w});
        num_edges++;
    }
}

void WeightedDigraphAL::remove_edge(Vertex u, Vertex v) {
    for (auto it = adj_list[u].begin(); it != adj_list[u].end(); ++it) {
        if (it->getVertex() == u) {
            adj_list[u].erase(it);
        }
    }

    num_edges--;
}

void WeightedDigraphAL::input_graph(WeightedDigraphAL &g, Vertex u, Vertex v, Weight w) {
    g.add_edge(u, v, w);
}

void WeightedDigraphAL::display_graph() {
    for (unsigned int i = 0; i < num_vertices; ++i) {
        std::cout << i << ": ";
        for (auto it = adj_list[i].begin(); it != adj_list[i].end(); ++it) {
            std::cout << "(" << it->getVertex() << ", " << it->getWeight() << "), ";
        }
        std::cout << std::endl;
    }
}


int main()
{
    unsigned int num_vertices;
    std::cin >> num_vertices;
    WeightedDigraphAL graph(num_vertices);

    unsigned int num_edges;
    std::cin >> num_edges;

    for (unsigned int i = 0; i < num_edges; ++i) {
        int vertex1, vertex2;
        float weight;

        std::cin >> vertex1;
        std::cin >> vertex2;
        std::cin >> weight;

        graph.input_graph(graph, vertex1, vertex2, weight);
    }
    std::cout << "num_vertices: " << graph.get_num_vertices() << std::endl;
    std::cout << "num_edges: " << num_edges << std:: endl;
    graph.display_graph();

    return 0;
}
