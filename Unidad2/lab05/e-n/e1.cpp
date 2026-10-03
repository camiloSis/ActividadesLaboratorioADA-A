
#include <bits/stdc++.h>
using namespace std;

struct Arista {
    int u, v;
    long long w;
};

struct UnionFind {
    vector<int> padre;
    vector<int> rango;
    int componentes;

    UnionFind(int n) : padre(n), rango(n, 0), componentes(n) {
        iota(padre.begin(), padre.end(), 0);
    }

    int buscar(int x) {
        if (padre[x] != x)
            padre[x] = buscar(padre[x]);
        return padre[x];
    }

    bool unir(int a, int b) {
        a = buscar(a);
        b = buscar(b);
        if (a == b) return false;
        if (rango[a] < rango[b]) swap(a, b);
        padre[b] = a;
        if (rango[a] == rango[b]) rango[a]++;
        componentes--;
        return true;
    }
};

const char* EJEMPLO =
    "6\n"
    "Rectorado Biblioteca Laboratorio Cafeteria Gimnasio Auditorio\n"
    "9\n"
    "Rectorado Biblioteca 4\n"
    "Rectorado Cafeteria 8\n"
    "Biblioteca Laboratorio 8\n"
    "Biblioteca Cafeteria 11\n"
    "Laboratorio Gimnasio 7\n"
    "Cafeteria Gimnasio 1\n"
    "Cafeteria Auditorio 2\n"
    "Gimnasio Auditorio 6\n"
    "Laboratorio Auditorio 4\n";

int main() {

    cout << "Usar datos de ejemplo? (s/n): ";
    char op; cin >> op;
    istringstream ejemplo(EJEMPLO);
    istream& in = (op == 's' || op == 'S') ? static_cast<istream&>(ejemplo) : cin;
    if (op != 's' && op != 'S')
        cout << "Ingrese n, luego los n nombres, luego m y luego m lineas 'A B costo':\n";

    int n, m;
    in >> n;
    vector<string> nombre(n);
    unordered_map<string, int> id;
    for (int i = 0; i < n; i++) { in >> nombre[i]; id[nombre[i]] = i; }

    in >> m;
    vector<Arista> aristas;
    for (int i = 0; i < m; i++) {
        string a, b; long long c;
        in >> a >> b >> c;
        if (!id.count(a) || !id.count(b) || c < 0) {
            cout << "Tendido invalido ignorado: " << a << " " << b << " " << c << "\n";
            continue;
        }
        if (id[a] == id[b]) continue;
        aristas.push_back({id[a], id[b], c});
    }

    sort(aristas.begin(), aristas.end(),
         [](const Arista& x, const Arista& y) { return x.w < y.w; });

    UnionFind uf(n);
    vector<Arista> elegidas;
    long long costoTotal = 0;

    cout << "\n--- Recorrido de Kruskal (aristas por costo creciente) ---\n";
    for (const Arista& e : aristas) {
        if (uf.unir(e.u, e.v)) {
            elegidas.push_back(e);
            costoTotal += e.w;
            cout << "ACEPTADA  " << nombre[e.u] << " - " << nombre[e.v]
                 << " (costo " << e.w << ")\n";
            if ((int)elegidas.size() == n - 1) break;
        } else {
            cout << "rechazada " << nombre[e.u] << " - " << nombre[e.v]
                 << " (costo " << e.w << ") -> formaria un ciclo\n";
        }
    }

    cout << "\n=== RED DE CABLEADO DE MENOR COSTO ===\n";
    for (const Arista& e : elegidas)
        cout << nombre[e.u] << " <-> " << nombre[e.v] << "  costo " << e.w << "\n";
    cout << "Costo total: " << costoTotal << "\n";

    if (uf.componentes > 1)
        cout << "AVISO: los tendidos dados no conectan todos los edificios; "
             << "quedan " << uf.componentes << " grupos separados.\n";
    return 0;
}
