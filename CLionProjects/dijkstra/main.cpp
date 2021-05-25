#include <iostream>
#include <vector>

using namespace std;

vector<vector<pair<int, int>>> edges;
vector<bool> visited;
vector<int> dist;
vector<int> pred;
size_t n;

void dijkstra() {
    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 1; j < n + 1; ++j)
            if (!visited[j] && (v == -1 || dist[j] < dist[v]))
                v = j;
        if (dist[v] == 100 * (n + 1)) {
            break;
        }
        visited[v] = true;

        for (size_t j = 0; j < edges[v].size(); ++j) {
            int to = edges[v][j].first;
            int len = edges[v][j].second;
            if (dist[v] + len < dist[to]) {
                dist[to] = dist[v] + len;
                pred[to] = v;
            }
        }
    }
}

int main() {
    int s, f, w;
    cin >> n >> s >> f;
    edges.resize(n + 1);
    visited.resize(n + 1);
    pred.resize(n + 1);
    dist.resize(n + 1, 100 * (n + 1));
    for (size_t i = 1; i < n + 1; ++i) {
        edges[i].clear();
        for (int j = 1; j < n + 1; ++j) {
            cin >> w;
            if (w != -1 && j != i) {
                edges[i].push_back({j, w});
            }
        }
    }
    dist[s] = 0;
    dijkstra();
    if (dist[f] != 100 * (n + 1)) {
        vector<int> answer;
        auto p = f;
        while (p != s) {
            p = pred[p];
            answer.push_back(p);
        }
        for (int i = answer.size() - 1; i >= 0; --i) {
            cout << answer[i] << " ";
        }
        cout << f;
    } else {
        cout << -1;
    }
    return 0;
}

