
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int disc[MAXN], low[MAXN], timer;
bool visited[MAXN];
vector<pair<int,int>> bridges;

void dfs(int u, int parent) {
    visited[u] = true;
    disc[u] = low[u] = ++timer;

    for (int v : adj[u]) {
        if (v == parent) continue;

        if (!visited[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);

            if (low[v] > disc[u])
                bridges.push_back({u, v});
        } else {
            low[u] = min(low[u], disc[v]);
        }
    }
}

int main() {
    int V = 5;
    vector<pair<int,int>> edges = {
        {0,1},{1,2},{2,0},{1,3},{3,4}
    };

    for (auto e : edges) {
        adj[e.first].push_back(e.second);
        adj[e.second].push_back(e.first);
    }

    for (int i = 0; i < V; i++)
        if (!visited[i])
            dfs(i, -1);

    for (auto b : bridges)
        cout << b.first << " " << b.second << "\n";
}
