#include<stdio.h>
#include<stdlib.h>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <cstring>
#define MAX_HEAP_SIZE 100000
#define MAXREAL 999999.0
#include<stack>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 0
#define BLACK 3
#define GREY 2
using namespace std;
class HeapItem
{
public:
    int data; //actual data that is stored
    float key; //key value of the data, heap is constructed based on key
};

//MinHeap class, minimum item stored at the root of heap tree
class MinHeap
{
public:
    HeapItem * A; //stores heap items, e.g., nodes
    int heapLength;
    int * map;

    MinHeap() //constructor
    {
        A = new HeapItem[MAX_HEAP_SIZE];
        map = new int[MAX_HEAP_SIZE];
        heapLength=0;
    }

    ~MinHeap() //destructor
    {
        if(map) delete [] map;
        if(A) delete [] A;
        map = 0; //set to NULL after deletion
        A = 0;//set to NULL after deletion
    }

    void initialize(int v[], int n)
    {
        heapLength = n;
        for(int i=0; i<n; i++) //nodes are stored from index 1 instead of 0 in the heap
        {
            A[i+1].data = v[i];
            A[i+1].key = MAXREAL;
            map[v[i]] = i+1; //data is stored at which heap node
        }
    }

    void insertItem(int data, float key)
    {
        if(data<0)
        {
            printf("Negative data can't be inserted\n");
            return;
        }
        heapLength++;
        if(heapLength==MAX_HEAP_SIZE)
        {
            heapLength--;
            return;
        }
        A[heapLength].data = data;
        A[heapLength].key = key;
        map[data] = heapLength;
        buHeapify(heapLength);
    }

    int removeMin()
    {
        //write your codes here
        HeapItem tt;
        if(Empty())
        {
            return NULL_VALUE;
        }
        tt = A[1];
        A[1]=A[heapLength];
        heapLength--;
        heapify(1);
        return tt.data;
    }

    void updateKey(int data, float key)
    {
        //Write your codes here.
        if(data<0)
            return;
        int j;
        bool m = true;
        for(j=1; j<=heapLength; j++)
        {
            if(A[j].data == data)
            {
                m = false;
                break;
            }
        }
        if(m)
        {
            //printf("Data Not Found\n");
            return;
        }
        float temp = getKey(data);
        if(temp==key)
            return;
        int i = map[data];
        A[i].key = key;
        if(temp>key)
        {
            buHeapify(i);
        }
        else if(temp<key)
        {
            heapify(i);
        }
        return;
    }

    float getKey(int data)
    {
        int i = map[data];
        return A[i].key;
    }

    void heapify(int i)
    {
        int l,r,smallest;
        while(1)
        {
            l=2*i;      //left child index
            r=2*i+1;    //right child index
            smallest=i;

            if(l>heapLength && r>heapLength)
                break; //nothing to do, we are at bottom
            else if(r>heapLength)
                smallest = l;
            else if(l>heapLength)
                smallest = r;
            else if( A[l].key < A[r].key )
                smallest = l;
            else
                smallest = r;

            if(A[i].key <= A[smallest].key)
                break;	//we are done heapifying
            else
            {
                //swap nodes with smallest child, adjust map array accordingly
                HeapItem t;
                t=A[i];
                A[i]=A[smallest];
                map[A[i].data]=i;
                A[smallest]=t;
                map[A[smallest].data]=smallest;
                i=smallest;
            }

        }
    }

    void buHeapify(int i)
    {
        if(heapLength ==0 || heapLength==1)
            return;
        int j;
        while(i>1)
        {
            if(i%2)
                j= (i-1)/2;
            else
                j=i/2;
            if(A[j].key>A[i].key)
            {
                HeapItem tem = A[i];
                A[i] = A[j];
                A[j] = tem;
                map[A[i].data]=i;
                map[A[j].data]=j;
                i=j;
            }
            else
                return;
        }
    }

    void printHeap()
    {
        printf("Heap length: %d\n", heapLength);
        for(int i=1; i<=heapLength; i++)
        {
            printf(" (%d,%.2f) -> ", A[i].data, A[i].key);
        }
        printf("\n");
    }

    bool Empty()
    {
        if(heapLength==0)
            return true;
        else
            return false;
    }
};



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


typedef struct edge
{
    int dest,weight;
} edge;

class ArrayList
{
    edge * list;
    int length ;
    int listMaxSize ;
    int listInitSize ;
public:
    ArrayList() ;
    ~ArrayList() ;
    int searchItem(edge item) ;
    int searchItem(int item) ;
    int searchItem(int item, int newvalue) ;
    void insertItem(int dest,int weight) ;
    void removeItem(edge item) ;
    void removeItem(int item) ;
    void removeItemAt(int position);
    edge getItem(int position) ;
    int getLength();
    bool empty();
} ;


ArrayList::ArrayList()
{
    listInitSize = 2 ;
    listMaxSize = listInitSize ;
    list = new edge[listMaxSize] ;
    length = 0 ;
}

void ArrayList::insertItem(int dest,int weight)
{
    edge * tempList ;
    edge temp ;
    temp.dest = dest ;
    temp.weight = weight ;
    if (length == listMaxSize)
    {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;
        tempList = new edge[listMaxSize] ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i].dest = list[i].dest;
            tempList[i].weight = list[i].weight ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    };

    list[length].dest = temp.dest ; //store new item
    list[length].weight = temp.weight ;
    length++ ;
}

int ArrayList::searchItem(edge item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i].dest == item.dest && list[i].weight == item.weight) return i;
    }
    return NULL_VALUE;
}

int ArrayList::searchItem(int item,int newvalue)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i].dest == item)
        {
            if(list[i].weight>newvalue)
            {
                list[i].weight = newvalue;
            }
            return i;
        }
    }
    return NULL_VALUE;
}

int ArrayList::searchItem(int item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i].dest == item)
        {
            return i;
        }
    }
    return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
    if ( position < 0 || position >= length ) return ; //nothing to remove
    list[position].dest = list[length-1].dest ;
    list[position].weight = list[length-1].weight;
    length-- ;
}


void ArrayList::removeItem(edge item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE ) return ; //nothing to remove
    removeItemAt(position) ;
}

void ArrayList::removeItem(int item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE ) return ; //nothing to remove
    removeItemAt(position) ;
}

edge ArrayList::getItem(int position)
{
    edge temp;
    temp.dest = NULL_VALUE;
    temp.weight = NULL_VALUE;
    if(position < 0 || position >= length) return temp ;
    return list[position] ;
}

int ArrayList::getLength()
{
    return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}


ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    ArrayList  * adjList ;

    int *color;
    int *dist;
    int *parent;
    int time;
    int *reach;
    int *out;
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v, int weight);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source); //will run bfs in the graph
    void dfs();
    void dfs(int i); //will run dfs in the graph
    void Dijkstra(int source);
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    adjList = 0 ;
    color = 0 ;
    dist = 0;
    parent = 0;
    directed = dir ;
    time =0; //set direction of the graph
    //define other variables to be initialized
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    if(adjList!=0) delete[] adjList ; //delete previous list
    adjList = new ArrayList[nVertices] ;
    color = new int[nVertices];
    dist = new int[nVertices];
    parent = new int[nVertices];
    reach = new int[nVertices];
    out = new int[nVertices];
}

void Graph::addEdge(int u, int v, int w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    if(adjList[u].searchItem(v,w)==NULL_VALUE)
    {
        this->nEdges++ ;
        adjList[u].insertItem(v,w) ;
    }
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || v<0 || u>=nVertices || v>=nVertices || nEdges ==0) return; //vertex out of range
    if(adjList[u].searchItem(v)!=NULL_VALUE)
        this->nEdges-- ;
    else
        return;
    adjList[u].removeItem(v) ;
}

bool Graph::isEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices || nEdges ==0) return false; //vertex out of range
    if(adjList[u].searchItem(v)!=NULL_VALUE)
        return true;
    return false;
}

int Graph::getDegree(int u)
{
    if(u<0 || u>=nVertices || nEdges ==0) return  NULL_VALUE;
    return adjList[u].getLength();

}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    if(u<0 || v<0 || u==v || u>=nVertices || v>=nVertices || nEdges ==0)
        return false;//vertex out of range
    for(int i=0; i<nVertices; i++)
    {
        if(adjList[u].searchItem(i)!=NULL_VALUE)
        {
            if(adjList[v].searchItem(i)!=NULL_VALUE)
                return true;
        }
    }
    return false;
}

void Graph::bfs(int source)
{
    if(source<0 ||source>=nVertices ) return ;
    //complete this function
    //initialize BFS variables
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;
    int i;
    color[source] = GREY;
    dist[source] = 0 ;
    q.enqueue(source) ;
    while( !q.empty() )
    {
        //complete this part
        int pop = q.dequeue();
        int m = adjList[pop].getLength();
        for(int j =0; j<m; j++)
        {
            i = adjList[pop].getItem(j).dest;
            if(color[i]==WHITE || dist[i]>dist[pop]+1)
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
    for(int j=0; j<adjList[u].getLength(); j++)
    {
        int m= adjList[u].getItem(j).dest;
        if(color[m]==WHITE)
        {
            parent[m]=u;
            dist[m]=dist[u]+1;
            dfs(m);
        }
    }
    color[u]=BLACK;
    time++;
    out[u]=time;
}
void Graph::dfs()
{
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
        reach[i]= -1;
        out[i] = -1;
    }
    dist[0]=0;
    time=0;
    for(int i=0; i<nVertices; i++)
    {
        if(color[i]==WHITE)
            dfs(i);
    }

}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return NULL_VALUE;
    bfs(u);
    return (dist[v]-dist[u]) ;
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i+1);
        for(int j=0; j<adjList[i].getLength(); j++)
        {
            printf(" %d->", adjList[i].getItem(j).dest+1);
            printf(" %d ", adjList[i].getItem(j).weight);
        }
        printf("\n");
    }
}

void Graph::Dijkstra(int source)
{
    MinHeap heap;
    int temp,init,path;
    for(int i=0; i<nVertices; i++)
    {
        heap.insertItem(i, INFINITY);
        parent[i]=-1;
        dist[i]=INFINITY;
    }
    parent[source]=-1;
    dist[source]=0;
    heap.updateKey(source,dist[source]);

    while(!heap.Empty())
    {
        temp = heap.removeMin();
        for(int i=0; i<adjList[temp].getLength(); i++)
        {
            init = adjList[temp].getItem(i).dest;
            path = adjList[temp].getItem(i).weight;
            if(dist[init]>dist[temp]+path)
            {
                dist[init]=dist[temp]+path;
                parent[init]=temp;
                heap.updateKey(init,dist[init]);
            }
        }
    }
    for(int i=0; i<nVertices; i++)
    {
        printf("%d ",i+1);
        printf("%d ",dist[i]);
        printf("%d\n",parent[i]+1);
    }
}

Graph::~Graph()
{
    //write your destructor here
    if(adjList) delete[] adjList; //deallocate memory
    adjList = 0;
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
        u--;
        v--;
        g.addEdge(u, v, w);
    }
    while(1)
    {
        printf("1.Dijkstra.\n");
        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u;
            printf("Enter Source:\n");
            scanf("%d",&u);
            u--;
            g.Dijkstra(u);
        }
        else
        {
            continue;
        }
    }
    /*while(1)
    {
        printf("1.Dijkstra.\n");
        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            u--;
            v--;
            g.addEdge(u, v, w);
        }
        else if(ch==2)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            u--;
            v--;
            g.removeEdge(u,v);
        }
        else if(ch==3)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            u--;
            v--;
            printf("%d\n",g.isEdge(u, v));
        }
        else if(ch==4)
        {
            int u, v;
            scanf("%d", &u);
            u--;
            v = g.getDegree(u);
            printf("%d\n",v);
        }
        else if(ch==5)
        {
            g.printGraph();
        }
        else if(ch==6)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            u--;
            v--;
            printf("%d\n",g.hasCommonAdjacent(u, v));
        }
        else if(ch==7)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            u--;
            v--;
            printf("%d\n",g.getDist(u, v));
        }
        else if(ch==8)
        {
            int u;
            scanf("%d", &u);
            u--;
            g.bfs(u);
        }
        else if(ch==9)
        {
            int u;
            printf("Enter Source:\n");
            scanf("%d",&u);
            u--;
            g.Dijkstra(u);
        }
        else
        {
            continue;
        }
    }*/

    return 0;
}
