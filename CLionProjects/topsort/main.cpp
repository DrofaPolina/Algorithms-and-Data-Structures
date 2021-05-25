#include <iostream>
#include <vector>

using namespace std;

void dfs(int now, vector<vector<size_t>> &g, vector<int> &visited, vector<int> &topsort) {
    if (visited[now] == 1) {
        topsort.clear();
        return;
    }
    visited[now] = 1;
    for (int neig : g [now]) {
        if (visited[neig] != 2) {
            dfs(neig, g, visited, topsort);
            if (topsort.size() == 0) {
                return;
            }
        }
    }
    topsort.push_back(now);
    visited[now] = 2;
}

int main() {
    size_t from, to;
    int v, e;
    cin >> v >> e;
    vector<vector<size_t>> edges(v + 1);
    vector<int> visited(v + 1, 0);
    for (int i = 0; i < v + 1; ++i) {
        edges[i].resize(0);
    }
    for (int i = 0; i < e; ++i) {
        cin >> from >> to;
        edges[from].push_back(to);
    }
    vector<int> topsort = {0};
    for (int i = 1; i < v + 1; ++i) {
        if (visited[i] == 0) {
            dfs(i, edges, visited, topsort);
            if (topsort.size() == 0) {
                break;
            }
        }
    }
    if (topsort.size() > 0) {
        for (int i = topsort.size() - 1; i > 0; --i) {
            cout << topsort[i] << " ";
        }
    } else {
        cout << -1;
    }
    return 0;
}