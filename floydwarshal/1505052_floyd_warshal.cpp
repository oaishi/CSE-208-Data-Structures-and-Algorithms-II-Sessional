#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
using namespace std;

//******************Graph class starts here**************************

class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    int ** matrix ;
    int ** distmatrix ;
    int ** path ;

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v,int w);
    void removeEdge(int u, int v);
    void printGraph();
    void floyd();
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    matrix = 0 ;
    distmatrix = 0;
    path = 0;
    directed = dir ;
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    //allocate space for the matrix
    matrix = new int*[nVertices];
    distmatrix = new int*[nVertices];
    path = new int*[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        matrix[i] = new int[nVertices];
        distmatrix[i] = new int[nVertices];
        path[i] = new int[nVertices];
        for(int j=0; j<nVertices; j++)
        {
            path[i][j] = INFINITY;
            if(i!=j)
            {
                matrix[i][j] = INFINITY;
                distmatrix[i][j] = INFINITY;
            }
            else
            {
                matrix[i][j] = 0;
                distmatrix[i][j] = 0;
            }
        }//initialize the matrix cells to 0
    }
}

void Graph::addEdge(int u,int v,int w)
{
    u--;
    v--;//write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    if(matrix[u][v] == INFINITY)
    {
        matrix[u][v] = w;
        distmatrix[u][v] = w;
        nEdges++;
        path[u][v] = u;
    }
    else if(matrix[u][v]>w && w>=0)
    {
        matrix[u][v] = w;
        distmatrix[u][v] = w;
        path[u][v] = u;
    }
}

void Graph::removeEdge(int u, int v)
{
    u--;
    v--;
    //write this function
    if(u<0 || u>=nVertices || v<0 || v>=nVertices || nEdges ==0) return;
    if(matrix[u][v]!=0 || matrix[u][v]!=INFINITY )
        nEdges--;
    matrix[u][v] = INFINITY;
    distmatrix[u][v] = INFINITY;
    path[u][v] = INFINITY;
}

void Graph::floyd()
{
    printf("Original Graph\n");
    printGraph();
    for(int k=0; k<nVertices; k++)
    {
        for(int i=0; i<nVertices; i++)
        {
            for(int j=0; j<nVertices; j++)
            {
                if(distmatrix[i][j]>distmatrix[i][k]+distmatrix[k][j]){
                    distmatrix[i][j]=distmatrix[i][k]+distmatrix[k][j];
                    path[i][j] = path[k][j];
                }
            }
        }
    }
    printf("Minimum Distance Path\n");
    printf("  ");
    for(int k=1; k<=nVertices; k++)
    {
        printf(" %10d",k);
    }
    printf("\n");
    printf("--");
    for(int k=1; k<=nVertices; k++)
    {
        printf("-----------");
    }
    printf("\n");
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i+1);
        for(int j=0; j<nVertices; j++)
        {
            printf(" %10d", distmatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("Predecessor Graph\n");
    printf("  ");
    for(int k=1; k<=nVertices; k++)
    {
        printf(" %10d",k);
    }
    printf("\n");
    printf("--");
    for(int k=1; k<=nVertices; k++)
    {
        printf("-----------");
    }
    printf("\n");
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i+1);
        for(int j=0; j<nVertices; j++)
        {
            if(path[i][j]!=INFINITY)
            printf(" %10d", path[i][j]+1);
            else
                printf(" %10d",INFINITY);
        }
        printf("\n");
    }
    printf("\n");
}

void Graph::printGraph()
{
    int k=-1;
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i+1);
        for(int j=0; j<nVertices; j++)
        {
            printf(" %10d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

Graph::~Graph()
{
    for(int i=0; i<nVertices; i++)
    {
        delete[] matrix[i];
        delete[] distmatrix[i];
        delete[] path[i];
    }
    matrix =0;
    distmatrix =0;
    path = 0;
}



//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n;
    int k;
    Graph g;
    ifstream inFile;
    inFile.open("test.txt");
    if (!inFile)
    {
        cout << "Unable to open file";
        exit(1);
    }
    inFile >> n;
    inFile >> k;
    g.setnVertices(n);
    for(int m=0; m<k; m++)
    {
        int u, v, w;
        inFile >> u;
        inFile >> v;
        inFile >> w;
        g.addEdge(u,v,w);
    }
    inFile.close();
    g.printGraph();
    g.floyd();

    g.addEdge(1,5,1);
    g.printGraph();
    g.floyd();

    g.removeEdge(1,5);
    g.printGraph();
    g.floyd();
    return 0;
}
