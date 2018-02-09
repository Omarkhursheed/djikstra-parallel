#include <iostream>
#include <cstdlib>
#include <pthread.h>
using namespace std;

#define MAXV  1000 
#define MAXINT 65555
int parent[MAXV + 1] = {-1};



struct edgenode
{
    int y;
    int weight;
    struct edgenode *next;
};

struct graph
{
    edgenode *edges[MAXV+1];
    int degree[MAXV+1];
    int nvertices;
    int nedges;
    bool directed; 
};

void initialize_graph(graph *g, bool directed)
{
    int i;

    g -> nvertices = 0;
    g -> nedges = 0;
    g -> directed = directed;
    for (i = 1; i<=MAXV; i++) g -> degree[i] = 0;
    for (i = 1; i<=MAXV; i++) g -> edges[i] = NULL;
}

void insert_edge(graph *g, int x, int y, int weight, bool directed)
{
    edgenode *p;
    p = new edgenode;
    p -> weight = weight;
    p -> y = y;
    p -> next = g -> edges[x];

    g -> edges[x] = p;
    g -> degree[x]++;
    if (directed == false)
    {
        insert_edge(g, y, x, weight, true);
    }
    else
    {
        g -> nedges++;
    }
}


void read_graph(graph *g, bool directed)
{
    int i;
    int  m; 
    int x, y;
    int weight;
    initialize_graph(g, directed);
    cout << "Enter number of vertices";
    cin >> g ->  nvertices;
    cout << "Enter number of edges";
    cin >> m;
    for (i = 1; i <= m; i++)
    {
        cout << "Enter the vertex from: ";
        cin >> x;
        cout << "Enter the vertex to: ";
        cin >> y;
        cout << "Enter the weight of the edge: ";
        cin >> weight;
        insert_edge(g, x, y, weight, directed);
    }
}


void print_graph(graph *g)
{
    int i;
    edgenode *p;
    cout << "Vertex\tConnected " << endl;
    for (i = 1; i <= g->nvertices; i++)
    {
        cout << i << "\t";
        p = g -> edges[i];
        while (p != NULL)
        {
            cout << p->y << "\t" ;
            p = p -> next;
        }
        cout << endl;
    }
}
