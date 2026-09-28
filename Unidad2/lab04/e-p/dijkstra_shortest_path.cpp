#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int main() {
    int n = 6; // A=0, B=1, C=2, D=3, E=4, F=5
    vector<vector<pair<int, int>>> grafo(n);

    auto agregarArista = [&](int u, int v, int peso) {
        grafo[u].push_back({v, peso});
        grafo[v].push_back({u, peso});
    };

    agregarArista(0, 1, 4); // A-B
    agregarArista(0, 2, 2); // A-C
    agregarArista(1, 2, 1); // B-C
    agregarArista(1, 3, 5); // B-D
    agregarArista(2, 3, 8); // C-D
    agregarArista(2, 4, 10); // C-E
    agregarArista(3, 4, 2); // D-E
    agregarArista(3, 5, 6); // D-F
    agregarArista(4, 5, 3); // E-F

    vector<int> dist(n, INT_MAX);
    dist[0] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 0});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto [v, peso] : grafo[u]) {
            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                pq.push({dist[v], v});
            }
        }
    }

    string nombres[] = { "A", "B", "C", "D", "E", "F" };
    for (int i = 0; i < n; i++)
        cout << "Distancia a " << nombres[i] << ": " << dist[i] << endl;

    return 0;
}