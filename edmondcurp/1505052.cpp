#define INFINITY 999999
#include<bits/stdc++.h>
using namespace std;
int nVertices, nEdges ;
int matrix[100][100] ; // capacity input
bool dist[100];     //for dfs
int parent[100];    //for bfs
int flow[100][100];    //residue graph

void setnVertices(int n)
{
    nVertices = n ;
    nEdges = 0 ;

    for(int i=0; i<nVertices; i++)
    {
        for(int j=0; j<nVertices; j++)
        {
            matrix[i][j] = 0;
            flow[i][j] = 0;
        }
    }
    for(int i=0; i<nVertices; i++)
    {
        dist[i]= false;
    }
}

void addEdge(int u, int v,int w)
{
    u--;
    v--;
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = w;
    flow[u][v] = w;
    nEdges++;
}

bool bfs(int source,int sink)
{
    bool visited[nVertices];
    memset(visited, 0, nVertices);
    queue <int> q;
    visited[source] = true;
    parent[source] = -1;
    q.push(source);
    while( !q.empty() )
    {
        int pop = q.front();
        q.pop();
        for(int i =0; i<nVertices; i++)
        {
            if(visited[i]==false && flow[pop][i] > 0)
            {
                parent[i]=pop;
                visited[i]=true;
                q.push(i);
            }
        }
    }
    return (visited[sink] == true);
    //returns if there is the path to the sink
}

void dfs(int s)
{
    dist[s] = true;
    for (int i = 0; i <nVertices; i++)
        if (flow[s][i] && !dist[i])
            dfs(i);
}

void printGraph()
{
    printf("\nFlow Network\n");
    for(int i=0; i<nVertices; i++)
    {
        for(int j=0; j<nVertices; j++)
        {
            if (matrix[i][j]>0 && (matrix[i][j]-flow[i][j])>=0 ){
            printf("%3d,%3d : %3d",i+1,j+1, matrix[i][j]-flow[i][j]);
            printf("\n");}
        }
    }
}

void fordFulkerson(int source,int sink)
{
    source--; // as the graph is ) indexed , so substracting one
    sink--;   // as stated above
    int max_flow = 0;
    while (bfs(source, sink))
    {
        int path_flow = INFINITY;
        for (int v=sink; v!=source; v=parent[v])
        {
            int u = parent[v];
            path_flow = min(path_flow, flow[u][v]);
        }
        for(int v=sink; v!=source; v=parent[v])
        {
            int u = parent[v];
            flow[u][v] -= path_flow;
            flow[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    dfs(source);
    cout<<"Maximum Flow - "<<max_flow<<endl;
    printGraph();
    cout<<"Min Cut Edges"<<endl;
    for (int i = 0; i <nVertices; i++){
        for (int j = 0; j < nVertices; j++)
        {
            if (dist[i] && !dist[j] && matrix[i][j])
                cout << i+1 << " - " << j+1 << endl;
        }
    }
}



//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n;
    int u,v,w;
    ifstream inFile;
    inFile.open("test.txt");
    if (!inFile)
    {
        cout << "Unable to open file";
        exit(1);
    }
    //reading from file
    inFile >> n;
    setnVertices(n);
    inFile >> n;
    for(int m=0; m<n; m++){
            inFile >> u;
            inFile >> v;
            inFile >> w;
            addEdge(u, v, w);
    }
    inFile >> u;
    inFile >> v;
    inFile.close();
    //calling the function
    fordFulkerson(u,v);
    return 0;
}
