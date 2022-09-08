#include "vector"
#include "iostream"
#include "list"
#include <unordered_set>
using namespace std;
#define infi 1000000000
 
class Node {
public:
    int vertexNumber;
    vector<pair<int, int> > children;
    Node(int vertexNumber)
    {
        this->vertexNumber = vertexNumber;
    }
 
    void add_child(int vNumber, int length)
    {
        pair<int, int> p;
        p.first = vNumber;
        p.second = length;
        children.push_back(p);
    }
};
vector<int> dijkstraDist(
    vector<Node*> g,
    int s, vector<int>& path)
{

    vector<int> dist(g.size());
    bool visited[g.size()];
    for (int i = 0; i < g.size(); i++) {
        visited[i] = false;
        path[i] = -1;
        dist[i] = infi;
    }
    dist[s] = 0;
    path[s] = -1;
    int current = s;
    unordered_set<int> sett;
    while (true) {
 
        visited[current] = true;
        for (int i = 0;
             i < g[current]->children.size();
             i++) {
            int v = g[current]->children[i].first;
            if (visited[v])
                continue;

            sett.insert(v);
            int alt
                = dist[current]
                  + g[current]->children[i].second;
 
            if (alt < dist[v]) {
                dist[v] = alt;
                path[v] = current;
            }
        }
        sett.erase(current);
        if (sett.empty())
            break;
 
        int minDist = infi;
        int index = 0;
        for (int a: sett) {
            if (dist[a] < minDist) {
                minDist = dist[a];
                index = a;
            }
        }
        current = index;
    }
    return dist;
}
 
int main()
{
    vector<Node*> v;
    int n = 5, s = 0, e = 9;
    char data[10]={'A','B','C','D','E'}; 
    for (int i = 0; i < n; i++) {
        Node* a = new Node(i);
        v.push_back(a);
    }
    //0:A , 1:B, 2:C, 3:D, 4:E
    //edges weighted 
    v[0]->add_child(1,10);
    v[0]->add_child(2, 3);
    v[1]->add_child(2, 1);
    v[1]->add_child(3, 2);
    v[2]->add_child(1, 4);
    v[2]->add_child(3, 8);
    v[2]->add_child(4, 2);
    v[3]->add_child(4,7);
    v[3]->add_child(3,9);

 
    vector<int> path(v.size());
    vector<int> dist
        = dijkstraDist(v, s, path);
     cout << "Distance of " << data[0]
             << " to "
             << data[3] << " is: "
             << dist[3] << endl;
    return 0;
}
