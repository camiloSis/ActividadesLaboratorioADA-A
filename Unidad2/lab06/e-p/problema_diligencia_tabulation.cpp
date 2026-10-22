#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    // Nodos: 0=A, 1=B, 2=C, 3=D, 4=E, 5=F, 6=G, 7=H
    int n = 8;
    vector<vector<pair<int, int>>> grafo(n); // (destino, costo)

    grafo[0] = { {1, 2}, {2, 4}, {3, 3} };  // A -> B, C, D
    grafo[1] = { {4, 7}, {5, 4}, {6, 6} };  // B -> E, F, G
    grafo[2] = { {4, 3}, {5, 2}, {6, 4} };  // C -> E, F, G
    grafo[3] = { {4, 4}, {5, 1}, {6, 5} };  // D -> E, F, G
    grafo[4] = { {7, 3} };                  // E -> H
    grafo[5] = { {7, 6} };                  // F -> H
    grafo[6] = { {7, 3} };                  // G -> H

    vector<int> f(n, INT_MAX);
    vector<int> siguiente(n, -1);
    f[7] = 0; // caso base: el destino H cuesta 0 llegar a sí mismo

    // T: orden topologico inverso: G, F, E, D, C, B, A
    for (int u = 6; u >= 0; u--) {
        for (size_t k = 0; k < grafo[u].size(); k++) {
            int v = grafo[u][k].first, costo = grafo[u][k].second;
            // R: relacion de recurrencia
            if (f[v] != INT_MAX && costo + f[v] < f[u]) {
                f[u] = costo + f[v];
                siguiente[u] = v;
            }
        }
    }

    string nombres[] = { "A", "B", "C", "D", "E", "F", "G", "H" };
    cout << "Costo minimo desde A hasta H: " << f[0] << endl;

    cout << "Ruta optima: ";
    int actual = 0; // O: la respuesta buscada es f[0], el origen
    while (actual != -1) {
        cout << nombres[actual];
        actual = siguiente[actual];
        if (actual != -1) cout << " -> ";
    }
    cout << endl;

    return 0;
}

