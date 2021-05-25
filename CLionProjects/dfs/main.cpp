#include <iostream>
#include <vector>

using namespace std;

void dfs(size_t now, vector<vector<size_t>> &g , vector<bool> &visited) {
    visited[now] = true;
    for (size_t neig : g [now]) {
        if (!visited[neig]) {
            dfs(neig, g, visited);
        }
    }
}

int main() {
    size_t v, e, from, to;
    cin >> v >> e;
    vector<vector<size_t>> edges(v + 1);
    vector<bool> visited(v + 1, false);
    for (size_t i = 0; i < v + 1; ++i) {
        edges[i].resize(0);
    }
    for (size_t i = 0; i < e; ++i) {
        cin >> from >> to;
        edges[from].push_back(to);
        edges[to].push_back(from);
    }
    dfs(1, edges, visited);
    size_t cnt = 0;
    for (bool v : visited) {
        if (v) {
            ++cnt;
        }
    }
    cout << cnt << "\n";
    for (size_t i = 0; i < v + 1; ++i) {
        if (visited[i]) {
            cout << i << " ";
        }
    }
    return 0;
}