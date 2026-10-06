#include <bits/stdc++.h>
using namespace std;

struct Tramo {
    int u, v;
    double km;
    double costo;
};

struct UnionFind {
    vector<int> padre, rango;
    int componentes;
    UnionFind(int n) : padre(n), rango(n, 0), componentes(n) { iota(padre.begin(), padre.end(), 0); }
    int buscar(int x) { return padre[x] == x ? x : padre[x] = buscar(padre[x]); }
    bool unir(int a, int b) {
        a = buscar(a); b = buscar(b);
        if (a == b) return false;
        if (rango[a] < rango[b]) swap(a, b);
        padre[b] = a;
        if (rango[a] == rango[b]) rango[a]++;
        componentes--;
        return true;
    }
};

const char* EJEMPLO =
    "8\n"
    "Yura Cayma Uchumayo Characato Sabandia Socabaya Chiguata Polobaya\n"
    "14\n"
    "Yura Cayma 12 60\n"
    "Yura Uchumayo 18 75\n"
    "Cayma Uchumayo 15 50\n"
    "Cayma Socabaya 10 45\n"
    "Uchumayo Socabaya 9 55\n"
    "Socabaya Characato 8 40\n"
    "Socabaya Sabandia 7 40\n"
    "Characato Sabandia 5 35\n"
    "Characato Chiguata 14 70\n"
    "Sabandia Chiguata 17 80\n"
    "Sabandia Polobaya 20 85\n"
    "Chiguata Polobaya 16 90\n"
    "Uchumayo Polobaya 30 95\n"
    "Cayma Characato 13 50\n";

int main() {
    cout << "Usar red de ejemplo? (s/n): ";
    char op; cin >> op;
    istringstream ejemplo(EJEMPLO);
    istream& in = (op == 's' || op == 'S') ? static_cast<istream&>(ejemplo) : cin;
    if (op != 's' && op != 'S')
        cout << "Ingrese n, los nombres, m y luego m lineas 'A B km costo_por_km':\n";

    int n, m;
    in >> n;
    vector<string> nombre(n);
    unordered_map<string, int> id;
    for (int i = 0; i < n; i++) { in >> nombre[i]; id[nombre[i]] = i; }

    in >> m;
    vector<Tramo> tramos;
    double costoTodo = 0;
    for (int i = 0; i < m; i++) {
        string a, b; double km, cpk;
        in >> a >> b >> km >> cpk;
        if (!id.count(a) || !id.count(b) || km <= 0 || cpk < 0 || a == b) {
            cout << "Tramo invalido ignorado: " << a << " " << b << "\n";
            continue;
        }
        double costo = km * cpk;
        tramos.push_back({id[a], id[b], km, costo});
        costoTodo += costo;
    }

    sort(tramos.begin(), tramos.end(), [](const Tramo& x, const Tramo& y) {
        if (x.costo != y.costo) return x.costo < y.costo;
        if (min(x.u, x.v) != min(y.u, y.v)) return min(x.u, x.v) < min(y.u, y.v);
        return max(x.u, x.v) < max(y.u, y.v);
    });

    UnionFind uf(n);
    vector<Tramo> red;
    double costoMin = 0, kmTotal = 0;
    for (const Tramo& t : tramos) {
        if (uf.unir(t.u, t.v)) {
            red.push_back(t);
            costoMin += t.costo;
            kmTotal += t.km;
            if ((int)red.size() == n - 1) break;
        }
    }

    cout << fixed << setprecision(1);
    cout << "\n=== RED DE DISTRIBUCION DE COSTO MINIMO ===\n";
    for (const Tramo& t : red)
        cout << setw(11) << nombre[t.u] << " <-> " << left << setw(11) << nombre[t.v] << right
             << setw(6) << t.km << " km   costo " << setw(8) << t.costo << " (miles de S/)\n";

    cout << "\nTramos construidos : " << red.size() << " de " << tramos.size() << " posibles\n";
    cout << "Longitud total     : " << kmTotal << " km\n";
    cout << "COSTO MINIMO TOTAL : " << costoMin << " (miles de S/)\n";

    if (uf.componentes > 1) {
        cout << "\nAVISO: la red NO conecta todas las localidades; quedan " << uf.componentes
             << " zonas aisladas. Se necesitan tramos adicionales.\n";
    } else {
        cout << "Costo de construir TODOS los tramos: " << costoTodo << " (miles de S/)\n";
        cout << "Ahorro frente a construirlos todos : " << costoTodo - costoMin << " ("
             << 100.0 * (costoTodo - costoMin) / costoTodo << "%)\n";
    }
    return 0;
}
