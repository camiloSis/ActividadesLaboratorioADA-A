#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
using namespace std;
using reloj = chrono::steady_clock;

long long llamadas = 0;

long long fibIngenuo(int n) {
    llamadas++;
    if (n <= 1) return n;                        
    return fibIngenuo(n - 1) + fibIngenuo(n - 2);
}

long long fibMemo(int n, vector<long long>& memo) {
    llamadas++;
    if (n <= 1) return n;                        
    if (memo[n] != -1) return memo[n];           
    memo[n] = fibMemo(n - 1, memo) + fibMemo(n - 2, memo);  
    return memo[n];
}

long long fibTabulacion(int n) {
    if (n <= 1) return n;
    vector<long long> tabla(n + 1);
    tabla[0] = 0;                                
    tabla[1] = 1;                                
    for (int i = 2; i <= n; i++)
        tabla[i] = tabla[i - 1] + tabla[i - 2];  
    return tabla[n];
}

template <typename F>
double medirMicros(F f, int repeticiones) {
    auto t0 = reloj::now();
    for (int i = 0; i < repeticiones; i++) f();
    auto t1 = reloj::now();
    double total = chrono::duration<double, micro>(t1 - t0).count();
    return total / repeticiones;
}

int main() {
    int valores[3] = { 10, 20, 30 };

    volatile long long sumidero = 0;

    cout << fixed << setprecision(3);
    cout << "Comparacion de tiempos (promedio, en microsegundos)\n";
    cout << "----------------------------------------------------------------------\n";
    cout << " n | F(n)    | Ingenuo(us) [llamadas] | Memo(us) [llamadas] | Tabul.(us)\n";
    cout << "----------------------------------------------------------------------\n";

    for (int idx = 0; idx < 3; idx++) {
        int n = valores[idx];

        int repIng = (n <= 10) ? 100000 : (n <= 20) ? 1000 : 5;
        llamadas = 0;
        long long resIng = fibIngenuo(n);        
        long long llamIng = llamadas;
        double tIng = medirMicros([&]() { sumidero = fibIngenuo(n); }, repIng);

        llamadas = 0;
        { vector<long long> memo(n + 1, -1); fibMemo(n, memo); }
        long long llamMemo = llamadas;
        double tMemo = medirMicros([&]() {
            vector<long long> memo(n + 1, -1);
            sumidero = fibMemo(n, memo);
        }, 200000);

        double tTab = medirMicros([&]() { sumidero = fibTabulacion(n); }, 200000);

        vector<long long> m2(n + 1, -1);
        bool ok = (resIng == fibMemo(n, m2)) && (resIng == fibTabulacion(n));

        cout << setw(2) << n << " | " << setw(7) << resIng << " | "
             << setw(11) << tIng << " [" << setw(8) << llamIng << "] | "
             << setw(8) << tMemo << " [" << setw(3) << llamMemo << "] | "
             << setw(8) << tTab << (ok ? "   OK" : "   ERROR") << "\n";
    }
    cout << "----------------------------------------------------------------------\n";
    cout << "Nota: el ingenuo crece ~1.6x por cada +1 en n (O(2^n)); memo y tabulacion crecen lineal.\n";
    return 0;
}

