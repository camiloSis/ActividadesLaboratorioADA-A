#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

int main() {

    const int n = 10;
    string nombres[n] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" };
    int etapa[n]      = {  1,   2,   2,   2,   3,   3,   3,   4,   4,   5  };

    vector<vector<pair<int, int>>> grafo(n);
    grafo[0] = { {1, 5}, {2, 3}, {3, 6} };   
    grafo[1] = { {4, 4}, {5, 7}, {6, 6} };   
    grafo[2] = { {4, 2}, {5, 5}, {6, 8} };   
    grafo[3] = { {4, 6}, {5, 3}, {6, 4} };   
    grafo[4] = { {7, 5}, {8, 7} };           
    grafo[5] = { {7, 3}, {8, 4} };           
    grafo[6] = { {7, 6}, {8, 2} };           
    grafo[7] = { {9, 4} };                   
    grafo[8] = { {9, 5} };                   

    const int ORIGEN = 0, DESTINO = 9;

    vector<int> f(n, INT_MAX);      
    vector<int> siguiente(n, -1);   
    f[DESTINO] = 0;                 

    for (int u = DESTINO - 1; u >= ORIGEN; u--) {
        for (size_t k = 0; k < grafo[u].size(); k++) {
            int v     = grafo[u][k].first;
            int costo = grafo[u][k].second;

            if (f[v] != INT_MAX && costo + f[v] < f[u]) {
                f[u] = costo + f[v];
                siguiente[u] = v;      
            }
        }
    }

    cout << "=== Tabla de la programacion dinamica (de J hacia A) ===\n";
    cout << "Etapa | Nodo | f(nodo) | Decision optima\n";
    for (int u = n - 1; u >= 0; u--) {
        cout << "  " << etapa[u] << "   |  " << nombres[u] << "   |   " << f[u] << "\t |  ";
        if (siguiente[u] == -1) cout << "-";
        else cout << nombres[u] << " -> " << nombres[siguiente[u]];
        cout << "\n";
    }

    cout << "\nCosto minimo desde A hasta J: " << f[ORIGEN] << "\n";

    cout << "Ruta optima: ";
    int actual = ORIGEN;
    while (actual != -1) {
        cout << nombres[actual];
        actual = siguiente[actual];
        if (actual != -1) cout << " -> ";
    }
    cout << endl;
    return 0;
}

