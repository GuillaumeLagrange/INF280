#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <numeric>
#include <stack>

using namespace std;

bool eulerian_circuit_check(vector<vector<int>> adj);
void eulerian_circuit_search(vector<vector<int>> adj, vector<int> &circuit, int frst);

int main() {
    int cases;
    cin >> cases;

    for(int serial=1; serial<=cases; serial++) {
        unsigned int n;
        vector<vector<int>> adj(50, vector<int>(50, 0));
        cin >> n;
        int frst = 0;


        /* Constructing graph
         * Each node is a color
         * Each edge is a bead
         */
        for(unsigned int i=0; i<n; i++) {
            int clr1, clr2;
            cin >> clr1;
            cin >> clr2;
            clr1--;
            clr2--;
            frst = clr1;
            adj[clr1][clr2] ++;
            if(clr1 != clr2)
                adj[clr2][clr1] ++;
        }

        printf("Case #%d\n", serial);
        if (!eulerian_circuit_check(adj)) {
            puts("some beads may be lost");
        } else {
            vector<int> circuit;
            eulerian_circuit_search(adj, circuit, frst);
            if(circuit.size() != n + 1)
                puts("some beads may be lost");
            else
                for(auto tmp=circuit.begin(); tmp<circuit.end() - 1; tmp++)
                    printf("%d %d\n", *tmp + 1, *(tmp + 1) + 1);
        }
        cout << endl;
    }

    return 0;
};

/* Check wether an Eulerian circuit exists */
bool eulerian_circuit_check(vector<vector<int>> adj)
{
    for(int i=0; i<50; i++) {
		if((accumulate(adj[i].begin(), adj[i].end(), 0) - adj[i][i])%2)
            return false;
    }
    return true;
}

/* Eulerian circuit research, from class slides Hierholzer's algorithm */
void eulerian_circuit_search(vector<vector<int>> adj, vector<int>& circuit, int frst)
{
    int v = frst;
    stack<int> stck;
    stck.push(v);

    while(!stck.empty()) {
        int tmp = -1;

        for(int i=0; i<50; i++)
            if(adj[v][i]){
                tmp = i;
                break;
            }

        if(tmp > -1) {
            stck.push(v);
            adj[v][tmp] --;
            if(tmp != v)
                adj[tmp][v] --;
            v = tmp;
        } else {
            circuit.push_back(v);
            v = stck.top();
            stck.pop();
        }
    }
}
