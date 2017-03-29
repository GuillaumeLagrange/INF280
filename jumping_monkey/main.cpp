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
unordered_set<uint32_t> state_history; // Register already visited states
queue<pair<int, pair<uint32_t, vector<int>>>> bfs_queue; // Queue used for BFS

/* Generates the new state if node shot is shot at */
uint32_t new_state(int shot) {
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
    /* Empty queue and clear state_history */
    while(!bfs_queue.empty())
        bfs_queue.pop();
    state_history.clear();
    state_history.insert((1<<n) - 1);

    /* Fill queue with n first states */
    for(int i=0; i<n; i++)
        bfs_queue.push(make_pair(i, make_pair((1<<n) - 1, vector<int>(0))));

    /* Start of BFS */
    while(!bfs_queue.empty()) {
        auto tmp = bfs_queue.front();
        int i = tmp.first;
        curr_state = tmp.second.first;

        /* If current state is ok, we leave it at the front fo queue for main */
        if(curr_state == 0)
            return;

        bfs_queue.pop();
        int n_state = new_state(i);

        /* If new state has never been seen before */
        if(find(state_history.begin(), state_history.end(), n_state)
                == state_history.end()) {
            state_history.insert(n_state);
            /* Adding all potential shots to the queue */
            vector<int> curr_path = tmp.second.second;
            for(int j=0; j<n; j++)
                if(n_state & (1<<j) || n_state == 0) {
                    /* Copying old path */
                    vector<int> n_path = vector<int>(curr_path);
                    n_path.push_back(i);
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

        if(bfs_queue.empty()) {
            puts("Impossible");
        } else {
            auto tmp = bfs_queue.front();
            auto shots = tmp.second.second;
            printf("%d :", (int) shots.size());
            for(auto tree : shots)
                printf(" %d", tree);
            printf("\n");
        }
    }

    return 0;
};
