#include <iostream>
#include <algorithm>
#include <limits>
#include <vector>
#include <queue>
#include <list>

using namespace std;

int n;
int m;
int s;
int d;
int u, v;
unsigned int p;
typedef pair<unsigned int, int> WeightNode;
priority_queue<WeightNode, vector<WeightNode>, std::greater<WeightNode> > Q;

vector<list <int> > disjkstra(int root, vector<int, unsigned int> Adj[n], int * dist);
void clearPath(int root, vector<list<int> > paths, vector<int, unsigned int> Adj[n]);

int main() {
    cout << "Hello World" << endl;
    int max = std::numeric_limits<int>::max();
    std::cout << max << std::endl;

    while(true) {
        cin >> n;
        cin >> m;

        if ((n == 0) && (m == 0))
            return 0;

        cin >> s;
        cin >> d;

        vector<int, unsigned int> Adj[n];
        int dist[n];

        /* Adding distances to the dist array */
        for (int i=0; i<m; i++) {
            cin >> u;
            cin >> v;
            cin >> p;

            Adj[u]push_back(make_pair(v, p));
        }

        auto path_list = dijkstra(s, Adj, dist);
        clearPath(d, path_list, Adj);
        disjkstra(s, Adj, dist);

        if(dist[d] == numeric_limits::max())
            cout << "-1" << endl;
        else
            cout << dist[d] << endl;


    }

    return 0;
};

/* Disjkstra's algorithm for shortest path research */
vector<list <int> > disjkstra(int root, vector<int, unsigned int> Adj[n], int * dist)
{
    vector<list <int> > paths(n, list<int>(0));
    for(int i=0; i<n; i++)
        dist[i] = numeric_limits<int>::max();
    dist[root] = 0;
    Q.push(make_pair(0, root));
    while(!Q.empty()) {
        int u = Q.top().second;
        Q.pop();
        for(auto tmp : Adj[u]) {
            int v = tmp.first;
            unsigned int weight = tmp.second;
            if(dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                Q.push(make_pair(dist[v], v));
                paths[v].push_back(u);
            }
        }
    }

    return paths;
}

/* Function to delete a path */
void clearPath(int root, vector<list<int> > paths, vector<int, unsigned int> Adj[n])
{
    for (auto tmp : paths[root]) {
        Adj[tmp].remove(root);
        clearPath(tmp, paths, Adj);
    }
}

