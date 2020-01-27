#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 0
#define BLACK 3
#define GREY 2
#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
using namespace std;
class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
    if (length == queueMaxSize)
    {
        int * tempData ;
        //allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize ;
        tempData = new int[queueMaxSize] ;
        int i, j;
        j = 0;
        for( i = rear; i < length ; i++ )
        {
            tempData[j++] = data[i] ; //copy items from rear
        }
        for( i = 0; i < rear ; i++ )
        {
            tempData[j++] = data[i] ; //copy items before rear
        }
        rear = 0 ;
        front = length ;
        delete[] data ; //free the memory allocated before
        data = tempData ; //make list to point to new memory
    }

    data[front] = item ; //store new item
    front = (front + 1) % queueMaxSize ;
    length++ ;
}


bool Queue::empty()
{
    if(length == 0) return true ;
    else return false ;
}


int Queue::dequeue()
{
    if(length == 0) return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;
    length-- ;
    return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************


//******************Graph class starts here**************************
typedef struct edge
{
    int source, dest, weight;
} edge;

typedef struct subset
{
    int parent, rank;
} makeset;
class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    int ** matrix ;
    int *color;
    int *dist;
    int *parent;
    int *reach;
    int *out;
    int time;
    edge *edges;
    int *krus;
    int **smst;
    int *weight;
    int krusval;
    int taken;
    makeset *make_set;

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v,int w);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source);
    void dfs();
    void dfs(int i); //will run bfs in the graph
    void KruscalMST();
    void SMST();
    void Union(int u,int v);
    int FIND_SET(int u);
    void sort(int l, int r);
    void merge(int l, int m, int r);
    void KruscalMST(int u,int j);
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    matrix = 0 ;
    color = 0 ;
    dist = 0;
    parent = 0;
    time=0;
    directed = dir ;
    reach = 0;
    out = 0;
    edges = 0;
    krus = 0;
    make_set = 0;
    smst = 0;
    weight = 0;
    krusval = 0;
    taken = 0;
    //set direction of the graph
    //define other variables to be initialized
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    //allocate space for the matrix
    matrix = new int*[nVertices];
    smst = new int*[2];
    weight = new int[2];
    color = new int[nVertices];
    dist = new int[nVertices];
    parent = new int[nVertices];
    reach = new int[nVertices];
    out = new int[nVertices];
    edges = new edge[nVertices*nVertices];
    krus = new int[nVertices-1];
    make_set = new makeset[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0; j<nVertices; j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }
    for(int i=0; i<2; i++)
        smst[i] = new int[nVertices-1];
}

void Graph::addEdge(int u, int v,int w)
{
    u--;
    v--;
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = w;
    edge temp;
    temp.source = u;
    temp.dest = v;
    temp.weight = w;
    edges[nEdges] = temp;
    nEdges++;
    if(!directed && u!=v)
        matrix[v][u] = w;

}

void Graph::removeEdge(int u, int v)
{
    u--;
    v--;
    //write this function
    if(u<0 || u>=nVertices || v<0 || v>=nVertices || nEdges ==0) return;
    if(matrix[u][v])
        nEdges--;
    matrix[u][v] = 0;
    if(!directed) matrix[v][u] = 0;
}

bool Graph::isEdge(int u, int v)
{
    u--;
    v--;
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    if (matrix[u][v] || matrix[v][u] )
    {
        return true;
    }
    return false;
}

int Graph::getDegree(int u)
{
    u--;
    if(u<0 || u>=nVertices )
        return NULL_VALUE;
    int degree=0;
    for(int i=0; i<nVertices; i++)
    {
        if(matrix[u][i])
            degree++;
    }
    if(directed)
    {
        for(int i=0; i<nVertices, i!= u ; i++)
        {
            if(matrix[i][u])
                degree++;
        }
    }
    return degree;
    //returns the degree of vertex u
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    u--;
    v--;
    //returns true if vertices u and v have common adjacent vertices
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    for(int i=0; i<nVertices ; i++)
    {
        if(matrix[u][i] || matrix[i][u])
        {
            if(matrix[v][i] || matrix[i][v])
                return true;
        }
    }
    return false;
}

void Graph::bfs(int source)
{
    source--;
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i]= -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;
    color[source] = GREY;
    dist[source] = 0 ;
    q.enqueue(source) ;
    while( !q.empty() )
    {
        //complete this part
        int pop = q.dequeue();
        for(int i =0; i<nVertices; i++)
        {
            if(isEdge(pop,i)&& (color[i]==WHITE || dist[i]>dist[pop]+1))
            {
                parent[i]=pop;
                color[i]=GREY;
                dist[i]=dist[pop]+1;
                q.enqueue(i);
            }
        }
        color[pop]=BLACK;
    }
}

void Graph::dfs(int u)
{
    time++;
    reach[u]=time;
    color[u]=GREY;
    for(int j=0; j<nVertices; j++)
    {
        if(matrix[u][j]==1 && color[j]==WHITE)
        {
            parent[j]=u;
            dist[j]=dist[u]+1;
            dfs(j);
        }
    }
    color[u]=BLACK;
    time++;
    out[u]=time;
}

void Graph::dfs()
{
    //write this function
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i]= -1 ;
        dist[i] = INFINITY ;
        reach[i]=-1;
        out[i]=-1;
    }
    dist[0]=0;
    time =0;
    for(int i=0; i<nVertices; i++)
    {
        if(color[i]==WHITE)
            dfs(i);
    }
}

void Graph::merge(int l, int m, int r)
{
    int i, j, k;
    int low = m - l + 1;
    int high =  r - m;
    edge L[low], R[high];
    for (i = 0; i < low ; i++)
    {
        L[i].source = edges[l + i].source;
        L[i].dest = edges[l + i].dest;
        L[i].weight = edges[l + i].weight;
    }
    for (j = 0; j < high ; j++)
    {
        R[j].source = edges[m + 1+ j].source;
        R[j].dest = edges[m + 1+ j].dest;
        R[j].weight = edges[m + 1+ j].weight;
    }
    i = 0;
    j = 0;
    k = l;
    while (i < low && j < high)
    {
        if (L[i].weight < R[j].weight)
        {
            edges[k].source = L[i].source;
            edges[k].dest = L[i].dest;
            edges[k].weight =L[i].weight;
            i++;
        }
        else
        {
            edges[k].source = R[j].source;
            edges[k].dest = R[j].dest;
            edges[k].weight = R[j].weight;
            j++;
        }
        k++;
    }
    while (i < low)
    {
        edges[k].source = L[i].source;
        edges[k].dest = L[i].dest;
        edges[k].weight =L[i].weight;
        i++;
        k++;
    }

    while (j < high)
    {
        edges[k].source = R[j].source;
        edges[k].dest = R[j].dest;
        edges[k].weight = R[j].weight;
        j++;
        k++;
    }
}
void Graph::sort(int l,int r)
{
    if (l < r)
    {
        int m = (l+r)/2;
        sort( l, m);
        sort(  m+1, r);
        merge( l, m, r);
    }
}

void Graph:: Union(int u, int v)
{
    int x = FIND_SET(u);
    int y = FIND_SET(v);
    if(make_set[x].rank>make_set[y].rank)
        make_set[y].parent = x;
    else
    {
        make_set[x].parent = y;
        if(make_set[x].rank == make_set[y].rank)
            make_set[y].rank = make_set[y].rank + 1 ;
    }
}

int Graph::FIND_SET(int u)
{
    if((make_set[u].parent)!=u)
        make_set[u].parent = FIND_SET(make_set[u].parent);
    return make_set[u].parent;
}

void Graph::KruscalMST()
{
    if(nEdges< nVertices-1)
    {
        cout<<"Not a valid input"<<endl;
        return;
    }
    memset(krus,0,nEdges);
    makeset temp;
    for(int i=0; i<nVertices; i++)
    {
        temp.parent = i;
        temp.rank = 0;
        make_set[i] = temp;
    }
    sort(0,nEdges-1);
    int weight = 0;
    for(int i=0; i<nEdges; i++)
    {
        if(FIND_SET(edges[i].source)!=FIND_SET(edges[i].dest))
        {
            Union(edges[i].source,edges[i].dest);
            krus[taken]=i;
            taken++;
            weight += edges[i].weight;
            if(taken == nVertices-1)
                break;
        }
    }
    if(taken < nVertices-1)
    {
        cout<<"Invalid Output"<<endl;
    }
    else
    {
        cout<<"KRUSCAL_MST"<<endl;
        for(int i=0; i<nVertices-1; i++)
        {
            cout<<edges[krus[i]].source+1<<" ";
            cout<<edges[krus[i]].dest+1<<" ";
            cout<<edges[krus[i]].weight<<endl;
        }
        cout<<weight<<endl;
    }
    krusval = weight;
}

void Graph::KruscalMST(int u,int j)
{
    makeset temp;
    for(int i=0; i<nVertices; i++)
    {
        temp.parent = i;
        temp.rank = 0;
        make_set[i] = temp;
    }
    int taken=0;
    weight[u] = 0;
    for(int i=0; i<nEdges; i++)
    {
        if(i!=j && FIND_SET(edges[i].source)!=FIND_SET(edges[i].dest))
        {
            Union(edges[i].source,edges[i].dest);
            smst[u][taken]=i;
            taken++;
            weight[u] += edges[i].weight;
            if(taken == nVertices-1)
                break;
        }
    }
    if(taken != nVertices-1)
        weight[u]=INT_MAX;
}

void Graph::SMST()
{
    if(nEdges< nVertices-1 || taken < nVertices-1)
    {
        cout<<"Not a valid input"<<endl;
        return;
    }
    int foo = 0;
    cout<<"Second Minimum Spanning Tree"<<endl;
    weight[0]=INT_MAX;
    weight[1]=INT_MAX;
    for(int i=0; i<nVertices-1; i++)
    {
        KruscalMST(foo,krus[i]);
        if(weight[foo]<weight[1-foo])
            foo = 1-foo;
    }
    if(weight[0] == INT_MAX && weight[1] == INT_MAX)
    {
        for(int i=0; i<nVertices-1; i++)
        {
            cout<<edges[krus[i]].source+1<<" ";
            cout<<edges[krus[i]].dest+1<<" ";
            cout<<edges[krus[i]].weight<<endl;
        }
        cout<<krusval<<endl;
        return;
    }
    if(weight[0]<weight[1])
        foo = 0;
    else
        foo = 1;
    for(int i=0; i<nVertices-1; i++)
    {
        cout<<edges[smst[foo][i]].source+1<<" ";
        cout<<edges[smst[foo][i]].dest+1<<" ";
        cout<<edges[smst[foo][i]].weight<<endl;
    }
    cout<<weight[foo]<<endl;
}

int Graph::getDist(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return NULL_VALUE;
    bfs(u);
    return dist[v]-dist[u] ;
}


void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices; j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    //write your destructor here
    if(color) delete[] color; //deallocate memory
    color = 0;
    if(dist) delete[] dist; //deallocate memory
    dist = 0;
    if(parent) delete[] parent; //deallocate memory
    parent = 0;
    if(out) delete[] out; //deallocate memory
    out = 0;
    if(reach) delete[] reach; //deallocate memory
    reach = 0;
    for(int i=0; i<nVertices; i++)
        delete[] matrix[i];
    for(int i=0; i<2; i++)
        delete[] smst[i];
    matrix =0;
    delete[] edges;
    edges = 0;
    delete[] krus;
    krus = 0;
    delete[] weight;
    weight = 0;
    delete[] make_set;
    make_set = 0;
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
        g.addEdge(u, v, w);
    }
    g.KruscalMST();
    g.SMST();
    inFile.close();
    return 0;
}
