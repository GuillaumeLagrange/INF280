/* Guillaume Lagrange
 * Jumping Monkey https://icpcarchive.ecs.baylor.edu/index.php?option=onlinejudge&page=show_problem&problem=2960
 * Trying to use scanf for the first time
 */

#include <iostream>
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <queue>
#include <utility>
#include <unordered_set>

#define MAXN 21

using namespace std;

int n, m;
uint32_t adj[MAXN];
uint32_t curr_state; // Contains wether the monkey can be at each tree or not
vector<int> success_path;

/* Generates the new state if node shot is shot at */
inline uint32_t new_state(int shot) {
    curr_state &= ~(1<<shot);
    uint32_t n_state = 0;

    for(int i=0; i<n; i++) {
        if(curr_state & (1<<i))
            n_state |= adj[i];
    }
    return n_state;
}

void bfs()
{
    unordered_set<uint32_t> state_history; // Register already visited states
    queue<pair<int, pair<uint32_t, vector<int>>>> bfs_queue; // Queue used for BFS

    success_path.clear();

    /* Fill queue with n first states */
    for(int i=0; i<n; i++)
        bfs_queue.push(make_pair(i, make_pair((1<<n) - 1, vector<int>(0))));

    /* Start of BFS */
    while(!bfs_queue.empty()) {
        auto tmp = bfs_queue.front();
        bfs_queue.pop();
        int i = tmp.first;
        curr_state = tmp.second.first;
        int n_state = new_state(i);

        /* Handling if we got the monkey */
        if(n_state == 0) {
            success_path = tmp.second.second;
            success_path.push_back(i);
            break;
        }

        /* If new state has never been seen before */
        if(find(state_history.begin(), state_history.end(), n_state)
                == state_history.end()) {
            state_history.insert(n_state);
            /* Adding all potential shots to the queue */
            vector<int> n_path = tmp.second.second;
            n_path.push_back(i);
            for(int j=0; j<n; j++)
                if(n_state & (1<<j)) {
                    /* Copying old path */
                    bfs_queue.push(make_pair(j, make_pair(n_state, n_path)));
                }
        }
        /* If state has been seen before, don't do anything */
    }
}

int main() {
    while(true) {
        if(scanf("%d %d", &n, &m) != 2)
            return -1;

        if(n==0 && m==0)
            break;

        /* Clearing adj */
        memset(adj, 0, sizeof(adj));
        /* Registering adjencies */
        for(int i=0; i<m; i++) {
            int a,b;
            if (scanf("%d %d", &a, &b) != 2)
                return -1;
            adj[a] |= (1<<b);
            adj[b] |= (1<<a);
        }

        /* If graph contains a cycle, impossible */
        if(m != n-1) {
            puts("Impossible");
            continue;
        }

        bfs();

        if(success_path.empty()) {
            puts("Impossible");
        } else {
            printf("%d:", (int) success_path.size());
            for(auto tree : success_path)
                printf(" %d", tree);
            printf("\n");
        }
    }

    return 0;
};
