#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

size_t v;
vector <vector<size_t>> edges;
vector<int> height;
queue<int> q;
vector<bool> visited;
vector<int> pred;

void bfs(int a) {
    q.push(a);
    pred[a] = -1;
    visited[a] = true;

    while (q.size() > 0) {
        auto now = q.front();
        q.pop();
        for (auto neig : edges[now]) {
            if (!visited[neig]) {
                visited[neig] = true;
                q.push (neig);
                height[neig] = height[now] + 1;
                pred[neig] = now;
            }
        }
    }
}


int main() {
    int to, a, b;
    cin >> v;
    height.resize(v + 1, 0);
    edges.resize(v + 1);
    visited.resize(v + 1, false);
    pred.resize(v + 1, -1);
    for (size_t i = 1; i < v + 1; ++i) {
        edges[i].resize(v + 1, 0);
        for (size_t j = 1; j < v + 1; ++j) {
            cin >> to;
            if (to == 1) {
                edges[i].push_back(j);
            }
        }
    }
    cin >> a >> b;
    bfs(a);
    if (a != b && height[b] == 0) {
        cout << -1;
    } else {
        cout << height[b] << "\n";
    }
    return 0;
}