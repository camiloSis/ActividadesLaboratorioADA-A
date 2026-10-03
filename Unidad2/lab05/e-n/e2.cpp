
#include <bits/stdc++.h>
using namespace std;

struct Arista { int u, v; long long w; };

bool menor(const Arista& a, const Arista& b) {
    if (a.w != b.w) return a.w < b.w;
    if (a.u != b.u) return a.u < b.u;
    return a.v < b.v;
}

struct UnionFind {
    vector<int> padre, rango;
    UnionFind(int n) : padre(n), rango(n, 0) { iota(padre.begin(), padre.end(), 0); }
    int buscar(int x) { return padre[x] == x ? x : padre[x] = buscar(padre[x]); }
    bool unir(int a, int b) {
        a = buscar(a); b = buscar(b);
        if (a == b) return false;
        if (rango[a] < rango[b]) swap(a, b);
        padre[b] = a;
        if (rango[a] == rango[b]) rango[a]++;
        return true;
    }
};

vector<Arista> kruskal(int n, vector<Arista> aristas) {
    sort(aristas.begin(), aristas.end(), menor);
    UnionFind uf(n);
    vector<Arista> res;
    for (const Arista& e : aristas)
        if (uf.unir(e.u, e.v)) res.push_back(e);
    return res;
}

struct Candidato {
    Arista e;
    int destino;
};

struct MayorPrioridad {
    bool operator()(const Candidato& a, const Candidato& b) const { return menor(b.e, a.e); }
};

vector<Arista> prim(int n, const vector<vector<Candidato>>& ady) {
    vector<bool> visitado(n, false);
    vector<Arista> res;
    priority_queue<Candidato, vector<Candidato>, MayorPrioridad> pq;

    for (int inicio = 0; inicio < n; inicio++) {
        if (visitado[inicio]) continue;
        visitado[inicio] = true;
        for (const Candidato& c : ady[inicio]) pq.push(c);

        while (!pq.empty()) {
            Candidato c = pq.top(); pq.pop();
            if (visitado[c.destino]) continue;
            visitado[c.destino] = true;
            res.push_back(c.e);
            for (const Candidato& sig : ady[c.destino])
                if (!visitado[sig.destino]) pq.push(sig);
        }
    }
    return res;
}

long long pesoTotal(const vector<Arista>& v) {
    long long s = 0;
    for (const Arista& e : v) s += e.w;
    return s;
}

void imprimir(const string& titulo, const vector<Arista>& v) {
    cout << titulo << "\n";
    for (const Arista& e : v) cout << "  " << e.u << " - " << e.v << "  (peso " << e.w << ")\n";
    cout << "  Peso total: " << pesoTotal(v) << "\n";
}

const char* EJEMPLO =
    "7 11\n"
    "0 1 7\n0 3 5\n1 2 8\n1 3 9\n1 4 7\n2 4 5\n3 4 15\n3 5 6\n4 5 8\n4 6 9\n5 6 11\n";

int main() {
    cout << "Usar grafo de ejemplo? (s/n): ";
    char op; cin >> op;
    istringstream ejemplo(EJEMPLO);
    istream& in = (op == 's' || op == 'S') ? static_cast<istream&>(ejemplo) : cin;
    if (op != 's' && op != 'S') cout << "Ingrese 'n m' y luego m lineas 'u v w' (vertices 0..n-1):\n";

    int n, m;
    in >> n >> m;
    vector<Arista> aristas;
    vector<vector<Candidato>> ady(n);
    for (int i = 0; i < m; i++) {
        int u, v; long long w;
        in >> u >> v >> w;
        if (u == v || u < 0 || v < 0 || u >= n || v >= n) continue;
        if (u > v) swap(u, v);
        Arista e{u, v, w};
        aristas.push_back(e);
        ady[u].push_back({e, v});
        ady[v].push_back({e, u});
    }

    vector<Arista> aK = kruskal(n, aristas);
    vector<Arista> aP = prim(n, ady);

    imprimir("=== KRUSKAL ===", aK);
    imprimir("=== PRIM (cola de prioridad) ===", aP);

    vector<Arista> ordK = aK, ordP = aP;
    sort(ordK.begin(), ordK.end(), menor);
    sort(ordP.begin(), ordP.end(), menor);
    bool mismasAristas = ordK.size() == ordP.size() &&
        equal(ordK.begin(), ordK.end(), ordP.begin(),
              [](const Arista& a, const Arista& b) { return a.u == b.u && a.v == b.v && a.w == b.w; });

    cout << "\n=== COMPARACION ===\n";
    cout << "Peso Kruskal = " << pesoTotal(aK) << " | Peso Prim = " << pesoTotal(aP)
         << (pesoTotal(aK) == pesoTotal(aP) ? "  -> IGUALES\n" : "  -> DIFERENTES (error)\n");
    cout << "Aristas: " << (mismasAristas ? "ambos arboles tienen EXACTAMENTE las mismas aristas\n"
                                          : "los conjuntos de aristas difieren\n");
    cout << "Orden de seleccion: Kruskal es global (por peso), Prim crece desde un vertice;\n"
         << "el orden de aparicion difiere pero el arbol final es el mismo.\n";
    return 0;
}
