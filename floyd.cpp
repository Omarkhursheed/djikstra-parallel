#include <iostream>
#include <cstdlib>
#include <pthread.h>
using namespace std;

#define MAXV  1000 
#define MAXINT 65555
int parent[MAXV + 1] = {-1};


struct adjacency_matrix
{
    int weightMatrix[MAXV+1][MAXV+1];
    int nvertices;
};

void initialize_graph(graph *g, bool directed)
{
    int i;

    g -> nvertices = 0;
    for(int i = 0; i < g->nvertices; i++){
        for(int j = 0; j < g->nvertices; j++){
            g->weightMatrix[i][j]=MAXINT;
        }
    }
}

void insert_edge(graph *g, int x, int y, int weight, bool directed)
{
    g->weightMatrix[x][y] = weight;
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
    edgenode *p;
    cout << "Adjacency matrix" << endl;
    cout << '\t'
    for(int i = 0; i < g->nvertices; i++){
        cout << i << "\t";
    }
    cout << endl;
    for(int i = 0; i < g->nvertices; i++){
        for(int j = 0; j < g->nvertices; j++){
            if(j == 0){
                cout << j << '\t' << weightMatrix[i][j] << '\t';
            }
            else {
                cout << weightMatrix[i][j] << '\t';
            }
        }
    }
}

void floyd (adjacency_matrix *g, int thread_count p){
    int i, j;
    int k;
    int through_k;
    int size_of_block = sqrt(p);
    for(k = 0; k < g->nvertices; k++){
        for(i = 0; i < g->nvertices; i++){
            for(j = 0; j < g->nvertices; j++){
                through_k = g->weightMatrix[i][k]+ g->weightMatrix[k][j];
                if(through_k < g-> weightMatrix[i][j]){
                    g->weightMatrix[i][j] = through_k;
                }
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    graph g;
    read_graph(&g, true);
    print_graph(&g);
    int p;
    cout << "Enter the number of threads ";
    cin >> p;
    pthread_t threads[p];
    int ret[p];
    for(int i = 0; i < p; i++){
        ret[p]= pthread_create()
    }

    return 0;
}