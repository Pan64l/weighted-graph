#include <iostream>
#include <string>
#include <vector>

class node{

    private:

    friend class graph;
    int key;
    double mst_k;
    std::vector<int> neighbour;
    std::vector<int> edge_index;
    bool in_the_graph;
    bool is_visit;

    public:
 
    node();
    ~node();

};

class edge{

    private:

    friend class graph;
    int start;
    int end;
    double weight;
    bool i_graph;

    public:

    edge();
    ~edge();
};

class graph{

    private:

    int nov;
    unsigned long size;
    node *g_array[23133];
    std::vector<edge> g_edge;
    std::vector<int> mst;
    std::vector<node*> heap;
    // int m_size;
    public:

    graph();
    ~graph();
    
    bool find(int a, int b, double w);
    int num_of_v();
    void insert(int a, int b, double w);
    void print(int a);
    void del(int a); 
    void build_heap();
    void heapify(int a);
    void max_s(int a);
    bool vertex_in(int i);
    void clear_mst();

};

class illegal_exception
{
    
};