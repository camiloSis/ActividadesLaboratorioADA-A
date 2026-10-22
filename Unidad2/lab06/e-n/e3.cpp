#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

vector<vector<pair<int, int>>> grafo;  
vector<int> f;                         
vector<vector<int>> optimos;           
string nombres[] = { "A", "B", "C", "D", "E", "F", "G", "H" };
const int ORIGEN = 0, DESTINO = 7;
int totalCaminos = 0;

void enumerarCaminos(int u, vector<int>& camino) {
    camino.push_back(u);
    if (u == DESTINO) {
        totalCaminos++;
        cout << "  Camino " << totalCaminos << ": ";
        for (size_t i = 0; i < camino.size(); i++) {
            cout << nombres[camino[i]];
            if (i + 1 < camino.size()) cout << " -> ";
        }
        cout << "   (costo = " << f[ORIGEN] << ")\n";
    } else {

        for (size_t k = 0; k < optimos[u].size(); k++)
            enumerarCaminos(optimos[u][k], camino);
    }
    camino.pop_back();   
}

int main() {
    int n = 8;   
    grafo.assign(n, {});
    grafo[0] = { {1, 2}, {2, 4}, {3, 3} };   
    grafo[1] = { {4, 7}, {5, 4}, {6, 6} };   
    grafo[2] = { {4, 3}, {5, 2}, {6, 4} };   
    grafo[3] = { {4, 4}, {5, 1}, {6, 5} };   
    grafo[4] = { {7, 3} };                   
    grafo[5] = { {7, 6} };                   
    grafo[6] = { {7, 3} };                   

    f.assign(n, INT_MAX);
    optimos.assign(n, {});
    f[DESTINO] = 0;                          

    for (int u = DESTINO - 1; u >= 0; u--) {
        for (size_t k = 0; k < grafo[u].size(); k++) {
            int v = grafo[u][k].first, costo = grafo[u][k].second;
            if (f[v] == INT_MAX) continue;
            int candidato = costo + f[v];

            if (candidato < f[u]) {

                f[u] = candidato;
                optimos[u].clear();
                optimos[u].push_back(v);
            } else if (candidato == f[u]) {

                optimos[u].push_back(v);
            }
        }
    }

    cout << "Costo minimo desde A hasta H: " << f[ORIGEN] << "\n\n";
    cout << "Sucesores optimos por nodo (empate si hay mas de uno):\n";
    for (int u = n - 2; u >= 0; u--) {
        cout << "  f(" << nombres[u] << ") = " << f[u] << "  via ";
        for (size_t k = 0; k < optimos[u].size(); k++)
            cout << nombres[optimos[u][k]] << (k + 1 < optimos[u].size() ? ", " : "");
        if (optimos[u].size() > 1) cout << "   <-- EMPATE";
        cout << "\n";
    }

    cout << "\nTodos los caminos optimos:\n";
    vector<int> camino;
    enumerarCaminos(ORIGEN, camino);
    cout << "\nTotal de caminos optimos: " << totalCaminos << endl;
    return 0;
}

