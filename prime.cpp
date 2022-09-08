#include "vector"
#include "iostream"
#include "list"
using namespace std;
typedef pair<int, int> iPair;
  
struct Graph
{
    int V, E;
    vector< pair<int, iPair> > edges;
  
    Graph(int V, int E)
    {
        this->V = V;
        this->E = E;
    }
  
    void addEdge(int u, int v, int w)
    {
        pair<int, int> tmp (u, v);
        edges.push_back(pair<int, iPair> (w,tmp));
    }
  
    int kruskalMST();
};
  
struct DisjointSets
{
    int *parent, *rnk;
    int n;
  
    DisjointSets(int n)
    {
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];
        for (int i = 0; i <= n; i++)
        {
            rnk[i] = 0;
            parent[i] = i;
        }
    }
    int find(int u)
    {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }
  
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
  
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else 
            parent[x] = y;
  
        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};
 char data[10]={'A','B','C','D','E','F'}; 
  
int Graph::kruskalMST()
{
    int mst_wt = 0; 
  
    sort(edges.begin(), edges.end());
  
    DisjointSets ds(V);
    vector< pair<int, iPair> >::iterator it;
    for (it=edges.begin(); it!=edges.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;
        int set_u = ds.find(u);
        int set_v = ds.find(v);
        if (set_u != set_v)
        {
            cout << data[u] << " - " << data[v]<<"-"<<it->first << endl;
            mst_wt += it->first;
            ds.merge(set_u, set_v);
        }
    }
    return mst_wt;
}
int main()
{
    int V = 10, E = 6;
    Graph g(V, E);
    //0:A , 1:B, 2:C, 3:D, 4:E, 5:F
    g.addEdge(0, 1, 16);
    g.addEdge(0, 4, 19);
    g.addEdge(0, 5, 21);
    g.addEdge(1, 2, 6);
    g.addEdge(1, 3, 5);
    g.addEdge(1, 5, 11);
    g.addEdge(2, 3, 10);
    g.addEdge(3, 4, 18);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 33);
    int mst_wt = g.kruskalMST();
  
  
    return 0;
}
