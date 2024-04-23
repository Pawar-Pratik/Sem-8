#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

const int MAXN = 1e5;
vector<int> adj[MAXN + 5]; // adjacency list
bool visited[MAXN + 5];     // mark visited nodes

void bfs(int start_node) {
    queue<int> q;
    q.push(start_node);
    visited[start_node] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " "; // Print the visited node here

        // Parallel loop for visiting adjacent nodes
#pragma omp parallel for
        for (int i = 0; i < adj[node].size(); i++) {
            int next_node = adj[node][i];
#pragma omp critical
            {
                if (!visited[next_node]) {
                    visited[next_node] = true;
                    q.push(next_node);
                }
            }
        }
    }
}

int main() {
    cout << "Please enter nodes and edges: ";
    int n, m; // number of nodes and edges
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v; // edge between u and v
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int start_node; // start node of BFS
    cout << "Enter the start node for BFS: ";
    cin >> start_node;
    bfs(start_node);
    cout << endl; // Print a newline after BFS traversal
    return 0;
}
