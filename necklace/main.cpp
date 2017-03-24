#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <stack>

using namespace std;

bool eulerian_circuit_check(vector<int>* adj);
void eulerian_circuit_search(vector<int> adj[], vector<int> &circuit);

int main() {
    int cases;
    cin >> cases;

    for(int serial=1; serial<=cases; serial++) {
        int n;
        vector<int> adj[50];
        cin >> n;


        /* Constructing graph
         * Each node is a color
         * Each edge is a bead
         */
        int max_color = 0;
        for(int i=0; i<n; i++) {
            int clr1, clr2;
            cin >> clr1;
            cin >> clr2;
            clr1--;
            clr2--;
            adj[clr1].push_back(clr2);
            adj[clr2].push_back(clr1);
            if(clr1 > max_color)
                max_color = clr1;
            if(clr2 > max_color)
                max_color = clr2;
        }

        printf("Case #%d\n", serial);
        if (!eulerian_circuit_check(adj)) {
            puts("some beads may be lost");
        } else {
            vector<int> circuit;
            eulerian_circuit_search(adj, circuit);
            for(auto tmp : circuit)
                printf("%d\n", tmp);
        }
    }

    return 0;
};

/* Check wether an Eulerian circuit exists */
bool eulerian_circuit_check(vector<int>* adj)
{
    for(int i=0; i<50; i++) {
        if (adj[i].size()%2 != 0)
            return false;
    }
    return true;
}

/* Eulerian circuit research, from class slides Hierholzer's algorithm */
void eulerian_circuit_search(vector<int> * adj, vector<int> &circuit)
{
    int v = 0;
    stack<int> stck;
    stck.push(v);

    while(!stck.empty()) {
        if(!adj[v].empty()) {
            stck.push(v);
            int tmp = *adj[v].begin();
            adj[v].erase(remove(adj[v].begin(), adj[v].end(), tmp));
            adj[tmp].erase(remove(adj[tmp].begin(), adj[tmp].end(), v));
            v = tmp;
        } else {
            circuit.push_back(v);
            v = stck.top();
            stck.pop();
        }
    }
}
