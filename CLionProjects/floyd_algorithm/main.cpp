#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    size_t v;
    cin >> v;
    int x;
    vector<vector<int>> dist(v + 1);
    for (int i = 1; i < v + 1; ++i) {
        dist[i].resize(v + 1);
        for (int j = 1; j < v + 1; ++j) {
            cin >> x;
            dist[i][j] = x;
        }
    }

    for (size_t k = 1; k <= v; ++k) {
        for (size_t from = 1; from <= v; ++from) {
            for (size_t to = 1; to <= v; ++to) {
                dist[from][to] = min(dist[from][to], dist[from][k] + dist[k][to]);
            }
        }
    }
    for (size_t from = 1; from <= v; ++from) {
        for (size_t to = 1; to <= v; ++to) {
            cout << dist[from][to] << " ";
        }
        cout << "\n";
    }
    return 0;
}

