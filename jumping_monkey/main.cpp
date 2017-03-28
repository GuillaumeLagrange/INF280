/* Guillaume Lagrange
 * Jumping Monkey https://icpcarchive.ecs.baylor.edu/index.php?option=onlinejudge&page=show_problem&problem=2960
 * Trying to use scanf for the first time
 */

#include <iostream>
#include <algorithm>
#include <cstdint>
#include <queue>
#include <utility>

#define MAXN 21

using namespace std;

int n, m;
uint32_t adj[MAXN];
uint32_t curr_state; // Contains wether the monkey can be at each tree or not
vector<uint32_t> state_history; // Register already visited states
queue<pair<int, pair<uint32_t, vector<int>>>> bfs_queue; // Queue used for BFS

/* Generates the new state if node shot is shot at */
uint32_t new_state(int shot) {
    state_history.push_back(curr_state);
    curr_state &= ~(1<<shot);
    uint32_t new_state = 0;
    for(int i=0; i<n; i++) {
        if(curr_state & (1<<i))
            for(int j=0; j<n; j++)
                if(adj[i] & (1<<j))
                    new_state |= (1<<j);
    } // TODO : tester si on a déjà vu l'état ou non, intégrer ça à la BFS
    return new_state;
}

void bfs()
{
    /* Empty queue */
    while(!bfs_queue.empty())
        bfs_queue.pop();

    /* Fill queue with n first states */
    for(int i=0; i<n; i++)
        bfs_queue.push(make_pair(i, make_pair(0, vector<int>())));

    /* Start of BFS */
    while(!bfs_queue.empty()) {
        auto tmp = bfs_queue.front();
        bfs_queue.pop();
        int i = tmp.first;
        curr_state = tmp.second.first;

        if(curr_state == 0)
            break;

        int n_state = new_state(i);

        /* If new state has never been seen before */
        if(find(state_history.begin(), state_history.end(), n_state)
                == state_history.end()) {
            state_history.push_back(n_state);
            /* Adding all potential shots to the queue */
            vector<int> curr_path = tmp.second.second;
            for(int j=0; j<n; j++)
                if(n_state & (1<<j)) {
                    /* Copying old path */
                    vector<int> n_path = vector<int>(curr_path);
                    bfs_queue.push(make_pair(j, make_pair(n_state, n_path)));
                }
        }
        /* If state has been seen before, don't do anything */
    }
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

        /* If graph contains a cycle, impossible */
        if(m != n-1) {
            puts("Impossible");
            continue;
        }

        bfs();


    }

    return 0;
};
