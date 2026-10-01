#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    int n = 6; // A=0, B=1, C=2, D=3, E=4, F=5
    vector<vector<pair<int, int>>> grafo(n);

    auto agregarArista = [&](int u, int v, int peso)
    {
        grafo[u].push_back({v, peso});
        grafo[v].push_back({u, peso});
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

    vector<bool> enArbol(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 0}); // {peso, vertice}: empezamos en A

    string nombres[] = {"A", "B", "C", "D", "E", "F"};
    int pesoTotal = 0;

    while (!pq.empty())
    {
        //auto [peso, u] = pq.top();
        pair<int, int> top = pq.top();
        int peso = top.first;
        int u = top.second;
        pq.pop();
        if (enArbol[u]) continue;
        enArbol[u] = true;
        pesoTotal += peso;
        if (peso > 0)
        {
            cout << "Se agrega " << nombres[u];
            cout << " al arbol (peso " << peso << ")" << endl;
        }

        //for (auto [v, p] : grafo[u])
        for ( size_t i = 0; i < grafo[u].size(); i++){
            int v = grafo[u][i].first; 
            int p = grafo[u][i].second;

            if (!enArbol[v])
                pq.push({p, v});
        }
    }
    
    cout << "Peso total del arbol de expansion minimo: " << pesoTotal << endl;
    return 0;
}