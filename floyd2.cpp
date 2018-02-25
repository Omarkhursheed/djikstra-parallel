#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define MAXV  1000 
#define MAXINT 999
int nvertices;
int positions[MAXV][2];
int p;
int weightMatrix[MAXV][MAXV];
int throughMatrix[MAXV][MAXV];

pthread_barrier_t calc_barrier;


void *floyd (void* input){
    int i, j;
    int k;
    int through_k;
    int thread_number = *(int *) input;
    /*cout << "id " << id << endl;  
    int start = id * nvertices/p;
    int end = (id+1)*nvertices/p;
    cout << "start" << start << endl;
    cout << "end" << end << endl;*/
   // pthread_detach(pthread_self());
    int first = thread_number * nvertices/p;
    int last = (thread_number+1) * nvertices/p;
    for(k = 0; k < nvertices; k++){
        pthread_barrier_wait(&calc_barrier);
        for(int i = first; i < last; i++){

            for(int j = 0; j < nvertices; j++){
                
                through_k = weightMatrix[i][k]+ weightMatrix[k][j];
                if(through_k < weightMatrix[i][j]){
                    weightMatrix[i][j] = through_k;
                    throughMatrix[i][j] = k;
                }
        
            }
        }
    }
    //cout << "Thread " << id << "finished calculations for rows " << start << " to " << endl;

    //pthread_exit(NULL);
}

void getPath(int start, int end){
    int wentThrough = throughMatrix[start][end];
    if(wentThrough == -1){ 
        cout << start << " to " << end << " distance " << weightMatrix[start][end] << endl;
    } else {
        getPath(start, wentThrough);
        getPath(wentThrough, end);
    }
}
int main(int argc, char const *argv[])
{
    int i;
    int  m; 
    int x, y;
    int weight;


    cout << "Enter number of vertices";
    cin >> nvertices;
    cout << "Enter number of edges";
    cin >> m;
    for(int i = 0; i < nvertices; i++){
        for(int j = 0; j < nvertices; j++){
            weightMatrix[i][j]=MAXINT;
            throughMatrix[i][j] = -1;
            if(i == j){
                weightMatrix[i][j] = 0;
            }
        }
    }


    for (i = 1; i <= m; i++)
    {
        cout << "Enter the vertex from: ";
        cin >> x;
        cout << "Enter the vertex to: ";
        cin >> y;
        cout << "Enter the weight of the edge: ";
        cin >> weight;
        weightMatrix[x][y] = weight;
    }

    cout << "Adjacency matrix" << endl;
    cout << '\t';
    for(int i = 0; i < nvertices; i++){
        cout << i << "\t";
    }
    
    cout << endl;

    cout << endl;
    for(int i = 0; i < nvertices; i++){
        for(int j = 0; j < nvertices; j++){
            if(j == 0){
                cout << i << "|\t" << weightMatrix[i][j] << '\t';
            }
            else {
                cout << weightMatrix[i][j] << '\t';
            }
        }

            cout << endl;
    }



    
    cout << "Enter the number of threads now";

    cin >> p;
    pthread_t threads[100];
    cout << p;

    pthread_barrier_init(&calc_barrier, NULL, p);
    int ret[p];
  if(nvertices%p != 0){
        return 0;
    }
    for(int i = 0; i < p; i++){
        ret[i] = i;
        pthread_create(&threads[i], NULL, floyd, &ret[i]);
        
    }

    for(int i = 0; i < p; pthread_join(threads[i++], NULL));

    cout << "Adjacency matrix" << endl;
    cout << '\t';
    for(int i = 0; i < nvertices; i++){
        cout << i << "\t";
    }
    
    cout << endl;
    
    for(int i = 0; i < nvertices; i++){
        for(int j = 0; j < nvertices; j++){
            if(j == 0){
                cout << i << '\t' << weightMatrix[i][j] << '\t';
            }
            else {
                cout << weightMatrix[i][j] << '\t';
            }
        }
        cout << endl;
    }

    for(int i = 0; i < nvertices; i++){
        for(int j = 0; j < nvertices; j++){
            cout << "Path from " << i << " to " << j << ":"<< endl;
            getPath(i, j);
        }
    }
    //pthread_exit(NULL);
    return 0;
}

