#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

/* This problem is a direct implementation of Floyd Warshall algorithm
 * Most of it is directly inspired from the course slides
 */

int dist[50][50];
int p;
int r;
string name1;
string name2;
int current_index;
unordered_map<string, int> index_map;

int register_name(string name);
void floyd_warshall();

int main()
{
    int serial = 1;

    while (true) {

        cin >> p;
        cin >> r;

        if ((p == 0) || (r == 0))
            return 0;

        floyd_warshall();

        int max_dist = 0;

        for(int i=0; i<p; i++)
            for(int j=0; j<p; j++)
                if(dist[i][j] > max_dist)
                    max_dist = dist[i][j];

        cout << "Network " << serial ++ << ": ";
        if (max_dist == 50)
            cout << "DISCONNECTED" << endl << endl;
        else
            cout << max_dist << endl << endl;
    }


}

int register_name(string name)
{
    if(index_map.find(name) == index_map.end())
        index_map[name] = current_index++;

    return index_map[name];
}

void floyd_warshall()
{
    /* Restoring dist */
    for (int i=0; i<50; i++)
        for(int j=0; j<50; j++)
            dist[i][j] = 50;


    /* Set diag to 0 */
    for(int u = 0; u < p; u++) {
        dist[u][u] = 0;
    }

    /* Registering relationships */
    index_map.clear();
    current_index = 0;
    for(int i=0; i<r; i++) {
        cin >> name1;
        cin >> name2;

        int index1 = register_name(name1);
        int index2 = register_name(name2);

        dist[index1][index2] = 1;
        dist[index2][index1] = 1;
    }

    for(int k=0; k<p; k++)
        for(int i=0; i<p; i++)
            for(int j=0; j<p; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}
