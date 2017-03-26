#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <limits>

using namespace std;

int kruskal(vector<vector<int>> cities_graph);
vector<vector<int>> modify_graph(vector<vector <int>> cities_graph,
        vector<vector<int>> &subnetworks);

int main() {
    int cases;
    cin >> cases;

    for(int serial=0; serial<cases; serial++) {
        int n,q;
        cin >> n;
        cin >> q;

        /* Registering subnetworks */
        vector<vector <int>> subnetworks(q, vector<int>(0));
        vector<int> sub_costs(q);
        for(int i=0; i<q; i++) {
            int cities;
            cin >> cities;
            cin >> sub_costs[i];
            for(int j=0; j<cities; j++) {
                int city;
                cin >> city;
                subnetworks[i].push_back(city - 1); // Cities are from 1 to n
            }
        }

        /* Registering cities coordinates */
        vector<pair<int, int>> cities_coord(n);
        for(int i=0; i<n; i++) {
            int x,y;
            cin >> x;
            cin >> y;
            cities_coord[i] = make_pair(x, y);
        }

        /* Creating city graph */
        vector<vector <int>> cities_graph(n, vector<int>(n, 0));
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                if(i!=j) {
                    pair<int, int> coord1 = cities_coord[i];
                    pair<int, int> coord2 = cities_coord[j];
                    int dist = pow(coord1.first - coord2.first, 2) +
                               pow(coord1.second - coord2.second, 2);
                    cities_graph[i][j] = dist;
                    cities_graph[j][i] = dist;
                }

        /* Cycling through all subnetwork buying possibilities */
        uint8_t counter = 0;
        int min_cost = numeric_limits<int>::max();
        for(int i=0; i<256; i++) {
            vector<vector<int>> subnetworks_bought;
            int cost = 0;
            for(unsigned int j=0; j<8; j++) {
                if (j+1 <= subnetworks.size())
                    if (counter & (1<<j)) {
                        subnetworks_bought.push_back(subnetworks[j]);
                        cost += sub_costs[j];
                    }
            }
            counter ++;
            vector<vector<int>> modified_graph = modify_graph(cities_graph,
                    subnetworks_bought);
            cost += kruskal(modified_graph);
            if (cost < min_cost)
                min_cost = cost;
        }

        cout << min_cost << endl << endl;
    }

    return 0;
};

vector<vector<int>> modify_graph(vector<vector <int>> cities_graph,
        vector<vector<int>> &subnetworks) {
    for(auto subnetwork : subnetworks)
        for(auto city : subnetwork)
            for(auto other_city : subnetwork) {
                cities_graph[city][other_city] = 0;
    }
    return cities_graph;
}
