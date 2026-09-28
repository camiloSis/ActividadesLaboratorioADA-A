#include <iostream>
#include <vector>
using namespace std;

const int INF = 1e9;

int main() {
    int n = 6; // A=0, B=1, C=2, D=3, E=4, F=5
    vector<vector<int>> dist(n, vector<int>(n, INF));

    for (int i = 0; i < n; i++) dist[i][i] = 0;

    auto agregarArista = [&](int u, int v, int peso) {
        dist[u][v] = peso;
        dist[v][u] = peso;
    };

    agregarArista(0, 1, 4);
    agregarArista(0, 2, 2);
    agregarArista(1, 2, 1);
    agregarArista(1, 3, 5);
    agregarArista(2, 3, 8);
    agregarArista(2, 4, 10);
    agregarArista(3, 4, 2);
    agregarArista(3, 5, 6);
    agregarArista(4, 5, 3);

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    string nombres[] = { "A", "B", "C", "D", "E", "F" };
    cout << "Matriz de distancias minimas entre todos los pares:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << dist[i][j] << "\t";
        cout << endl;
    }

    return 0;
}