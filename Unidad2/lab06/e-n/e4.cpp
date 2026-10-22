#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

vector<vector<pair<int, int>>> grafo;   
vector<int> f;                          
vector<vector<int>> mejores;            
string nombres[] = { "A", "B", "C", "D", "E", "F", "G", "H" };
const int ORIGEN = 0, DESTINO = 7;
int totalCaminos = 0;

void enumerar(int u, vector<int>& camino) {
    camino.push_back(u);
    if (u == DESTINO) {
        totalCaminos++;
        cout << "  Camino " << totalCaminos << ": ";
        for (size_t i = 0; i < camino.size(); i++)
            cout << nombres[camino[i]] << (i + 1 < camino.size() ? " -> " : "");
        cout << "   (ganancia = " << f[ORIGEN] << ")\n";
    } else {
        for (size_t k = 0; k < mejores[u].size(); k++)
            enumerar(mejores[u][k], camino);
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

    const int NEG = INT_MIN;                 
    f.assign(n, NEG);
    mejores.assign(n, {});
    f[DESTINO] = 0;                          

    for (int u = DESTINO - 1; u >= 0; u--) {
        for (size_t k = 0; k < grafo[u].size(); k++) {
            int v = grafo[u][k].first, ganancia = grafo[u][k].second;
            if (f[v] == NEG) continue;       
            int candidato = ganancia + f[v];
            if (candidato > f[u]) {          
                f[u] = candidato;
                mejores[u].clear();
                mejores[u].push_back(v);
            } else if (candidato == f[u]) {  
                mejores[u].push_back(v);
            }
        }
    }

    cout << "Ganancia maxima desde A hasta H: " << f[ORIGEN] << "\n\n";
    cout << "Tabla (de H hacia A):\n";
    for (int u = n - 1; u >= 0; u--) {
        cout << "  f(" << nombres[u] << ") = " << f[u];
        if (u != DESTINO) {
            cout << "  via ";
            for (size_t k = 0; k < mejores[u].size(); k++)
                cout << nombres[mejores[u][k]] << (k + 1 < mejores[u].size() ? ", " : "");
        }
        cout << "\n";
    }

    cout << "\nCaminos de ganancia maxima:\n";
    vector<int> camino;
    enumerar(ORIGEN, camino);
    cout << "\nTotal: " << totalCaminos << " camino(s)\n";
    cout << "(Para comparar: el camino de costo MINIMO de la guia vale 10.)\n";
    return 0;
}

