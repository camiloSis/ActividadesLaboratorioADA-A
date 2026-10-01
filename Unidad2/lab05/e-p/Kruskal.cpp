#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Arista
{
    int u, v, peso;
};

vector<int> padre, rango;

int encontrar(int x)
{
    if (padre[x] != x)
        padre[x] = encontrar(padre[x]); // compresion de caminos
    return padre[x];
}

bool unir(int x, int y)

{
    int rx = encontrar(x), ry = encontrar(y);
    if (rx == ry)
        return false; // ya estan en la misma componente (formaria ciclo)
    if (rango[rx] < rango[ry])
        swap(rx, ry);
    padre[ry] = rx;
    if (rango[rx] == rango[ry])
        rango[rx]++;
    return true;
}

int main()

{
    int n = 6; // A=0, B=1, C=2, D=3, E=4, F=5

    vector<Arista> aristas = {
        {0, 1, 4}, {0, 2, 2}, {1, 2, 1}, {1, 3, 5}, {2, 3, 8}, {2, 4, 10}, {3, 4, 2}, {3, 5, 6}, {4, 5, 3}};
    sort(aristas.begin(), aristas.end(), [](Arista a, Arista b)
         { return a.peso < b.peso; });

    padre.resize(n);
    rango.assign(n, 0);

    for (int i = 0; i < n; i++)
        padre[i] = i;

    string nombres[] = {"A", "B", "C", "D", "E", "F"};
    int pesoTotal = 0;
    
    for (auto &a : aristas)
    {
        if (unir(a.u, a.v))
        {
            cout << nombres[a.u] << " - " << nombres[a.v];
            cout << " (peso " << a.peso << ")" << endl;
            pesoTotal += a.peso;
        }
    }

    cout << "Peso total del arbol de expansion minimo: " << pesoTotal << endl;
    return 0;
}