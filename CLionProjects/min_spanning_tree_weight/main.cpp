#include <iostream>
#include <vector>
#include <tuple>
#include <set>

using namespace std;

int main() {
    size_t n, m;
    cin >> n >> m;
    int a, b, w;
    const int INF = 5000000;
    vector<vector<pair<int, int>>> edges(n + 1);
    vector<bool> used(n + 1, false);
    vector<int> dist(n + 1, INF);
    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> w;
        edges[a].push_back({b, w});
        edges[b].push_back({a, w});
        if (a == 1) {
            dist[b] = min(dist[b], w);
        } else if (b == 1) {
            dist[a] = min(dist[a], w);
        }
    }

    set<pair<int, int>> unused;
    for (int i = 2; i <= n; ++i) {
        unused.insert({dist[i], i});
    }
    dist[1] = 0;
    int weight = 0;
    unused.insert({dist[1], 1});
    while (unused.size() > 0) {
        auto v = unused.begin()->second;
        unused.erase(unused.begin());
        weight += dist[v];
        for (size_t j = 0; j < edges[v].size(); ++j) {
            int to = edges[v][j].first;
            int len = edges[v][j].second;
            if (len < dist[to]) {
                auto it = unused.find({dist[to], to});
                if (it != unused.end()) {
                    unused.erase(it);
                    dist[to] = len;
                    unused.emplace(dist[to], to);
                }
            }
        }
    }
    cout << weight;
    return 0;
}

