#include <iostream>
#include "graph.hpp"

node::node(){

    key = 0;
    mst_k = -1;
    in_the_graph = false;
    is_visit = false;
    neighbour.clear();
    neighbour.resize(0);
    edge_index.clear();
    edge_index.resize(0);

}

node::~node(){

    neighbour.clear();
    edge_index.clear();
}

edge::edge(){

    start = 0;
    end = 0;
    weight = 0.0;
    i_graph = false;

}

edge::~edge(){
    
}

graph::graph(){

    for(int i=0; i <23133; i++)
    {
        g_array[i] = new node;
        g_array[i]->key = i+1;
    }
    nov = 0;
    size = 0;
    g_edge.clear();
    g_edge.resize(0);

}

graph::~graph(){

    for(int i=0; i <23133; i++)
    {
        delete g_array[i];
        g_array[i] = nullptr;
    }
    g_edge.clear();
}

bool graph::find(int a, int b , double w)
{
    if(g_array[a-1]->in_the_graph == false)
    {
        return false;
    }
    if(g_array[a-1]->in_the_graph == true)
    {
        for(int i=0; i < g_array[a-1]->neighbour.size(); i++)
        {
            int m = g_array[a-1]->neighbour[i];
            int n = g_array[a-1]->edge_index[i];
            if(m == b)
            {
                if((g_edge[n].start == a) && (g_edge[n].i_graph == true))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void graph::insert(int a, int b, double w)
{

// insert the edge in the g_edge vector
        edge iedge;
        iedge.start = a;
        iedge.end = b;
        iedge.weight = w;
        iedge.i_graph = true;
        g_edge.push_back(iedge);
        // std::cout << g_edge[size].start << "  " << g_edge[size].i_graph << "  " << g_edge.size() << std::endl;

// insert the node/vertex in the array
        
        if(g_array[a-1]->in_the_graph == false){

            nov ++;
            g_array[a-1]->in_the_graph = true;
        }

        if(g_array[b-1]->in_the_graph == false){

            nov ++;
            g_array[b-1]->in_the_graph = true;
        }

        // g_array[a-1]->key = a;
        // std::cout << g_array[a-1]->key << std::endl;
        g_array[a-1]->neighbour.push_back(b);
        g_array[a-1]->edge_index.push_back(size);

        // g_array[b-1]->key = b;
        g_array[b-1]->neighbour.push_back(a);
        g_array[b-1]->edge_index.push_back(size);
        size ++;
}   

void graph::print(int a)
{
  
    for(int i = 0; i < g_array[a-1]->neighbour.size(); i++)
    {
        int m = g_array[a-1]->edge_index[i];
        int n = g_array[a-1]->neighbour[i];
        if((g_edge[m].start == a) && (g_array[n-1]->in_the_graph == true) && (g_edge[m].i_graph == true))
        {
            std::cout << n << " " ;
        }
    }

}

void graph::del(int a)
{
    if(g_array[a-1]->in_the_graph == false)
    {
        std::cout << "failure" << std::endl;
    }
    else
    {
        g_array[a-1]->in_the_graph = false;

        for(int i = 0; i < g_array[a-1]->edge_index.size(); i++)
        {
            int k = g_array[a-1]->edge_index[i];
            g_edge[k].i_graph = false;
        }

        g_array[a-1]->neighbour.clear();
        g_array[a-1]->neighbour.resize(0);
        g_array[a-1]->edge_index.clear();
        g_array[a-1]->edge_index.resize(0);
        nov --;
        std::cout << "success" << std::endl;
    }
}

int graph::num_of_v()
{
    return nov;
}

void graph::build_heap()
{
    for(int i = (heap.size()/2) - 1; i >= 0; i--)
    {
    heapify(i);
    }
}

void graph::heapify(int i)
{
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int max = i;

    if((l < heap.size()) && ( (heap[l]->mst_k) > (heap[i]->mst_k) ))
    {
        max = l;

    }else{
        max = i;
    }

    if((r < heap.size()) && ( (heap[r]->mst_k) > (heap[i]->mst_k) ))
    {
        max = r;
    }

    if(max != i)
    {
        std::swap(heap[i], heap[max]);
        if(max < (heap.size()/2))
        {
            heapify(max);
        }
    }
}
void graph::max_s(int a)
{
    mst.clear();
    mst.resize(0);
    heap.clear();
    heap.resize(0);

    g_array[a-1]->mst_k = 0.0;
    heap.push_back(g_array[a-1]);
    g_array[a-1]->is_visit = true;
    mst.push_back(a);
    for(int i = 0; i < 23133; i++)
    {
        if((g_array[i] != g_array[a-1]) && (g_array[i]->in_the_graph == true))
        {
            g_array[i]->mst_k = -1;
            heap.push_back(g_array[i]);
        }
    }

    build_heap();

    while(heap.size() != 0)
    {

        //extract the first node
        node* temp = heap[0];
        std::swap(heap[0], heap.back());
        heap.pop_back();
        heapify(0);

        // if the mst key is -1 means this is not in the spanning tree then we break
        if(temp->mst_k == -1)
        {
            break;
        }
        
        // if is not visited, we push_back the key to the mst vector
        // std::cout << temp->key << " is visit " << temp->is_visit << std::endl;

        if(temp->is_visit == false)
        {
            mst.push_back(temp->key);
            temp->is_visit = true;
        }
        // find next maximum weight edge
        int i = 0;
        while(i < temp->neighbour.size())
        {            
            int m = temp->edge_index[i];
            int n = temp->neighbour[i];

            if((g_edge[m].start == (temp->key)) && (g_array[n-1]->in_the_graph == true) && (g_edge[m].i_graph == true))
            {
                if((g_array[n-1]->mst_k) < (g_edge[m].weight))
                {
                    g_array[n-1]->mst_k = g_edge[m].weight;
                }
            }
            i ++;
        }

        build_heap();
        
    }

    std::cout << mst.size() << std::endl;
}


bool graph::vertex_in(int a)
{
    if(g_array[a-1]->in_the_graph == true)
    {
        return true;
    }
    
    return false;
}

void graph::clear_mst()
{   
    // std::cout << "clear" << std::endl;

    for(int i = 0; i < mst.size(); i++)
    {
        // std::cout << g_array[mst[i]-1]->is_visit << " mst " << mst[i] << std::endl;
        (g_array[mst[i]-1]->is_visit) = false;
    }

}
