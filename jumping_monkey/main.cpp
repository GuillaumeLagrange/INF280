/* Guillaume Lagrange
 * Jumping Monkey https://icpcarchive.ecs.baylor.edu/index.php?option=onlinejudge&page=show_problem&problem=2960
 * Trying to use scanf for the first time
 */

#include <iostream>
#include <algorithm>
#include <cstdint>

#define NIL 0
#define INF numeric_limits<unsigned int >::max()
#define MAXN 21

using namespace std;

int n, m;
uint32_t adj[MAXN];
uint32_t curr_state; // Contains wether the monkey can be at each tree or not
vector<uint32_t> state_history; // Register already visited states

void new_state(int shot) {
    state_history.push_back(curr_state);
    curr_state &= ~(1<<shot);
    uint32_t new_state = 0;
    for(int i=0; i<n; i++) {
        if(curr_state & (1<<i))
            for(int j=0; j<n; j++)
                if(adj[i] & (1<<j))
                    new_state |= (1<<j);
    } // TODO : tester si on a déjà vu l'état ou non, intégrer ça à la BFS
}

int main() {
    while(true) {
        scanf("%d %d", &n, &m);

        if(n==0 && m==0)
            break;

        /* Registering adjencies */
        for(int i=0; i<m; i++) {
            int a,b;
            scanf("%d %d", &a, &b);
            adj[a] |= (1<<b);
            adj[b] |= (1<<a);
        }
    }

    return 0;
};
