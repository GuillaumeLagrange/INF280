#include <iostream>
#include <algorithm>

using namespace std;

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
    }

    return 0;
};
