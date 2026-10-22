#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>
using namespace std;

int main() {

    const int T = 6;                            
    int d[T + 1] = { 0, 3, 2, 4, 1, 5, 2 };     
    const int K = 10;                           
    const int c = 2;                            
    const int h = 1;                            
    const int IMAX = 8;                         
    const int XMAX = 8;                         
    const int INF = INT_MAX;

    vector<vector<int>> f(T + 2, vector<int>(IMAX + 1, INF));
    vector<vector<int>> prod(T + 2, vector<int>(IMAX + 1, -1));

    for (int i = 0; i <= IMAX; i++) f[T + 1][i] = 0;

    for (int t = T; t >= 1; t--) {
        for (int i = 0; i <= IMAX; i++) {                
            for (int x = 0; x <= XMAX; x++) {            
                int j = i + x - d[t];                    
                if (j < 0 || j > IMAX) continue;         
                if (f[t + 1][j] == INF) continue;        

                int costoMes = (x > 0 ? K : 0) + c * x + h * j;
                int total = costoMes + f[t + 1][j];      
                if (total < f[t][i]) {
                    f[t][i] = total;
                    prod[t][i] = x;                      
                }
            }
        }
    }

    int inventario = 0;
    cout << "Costo minimo total de los " << T << " meses: " << f[1][inventario] << "\n\n";

    cout << "Plan optimo de produccion\n";
    cout << "Mes | Demanda | Inv.inicial | Producir | Inv.final | Costo del mes\n";
    cout << "----+---------+-------------+----------+-----------+--------------\n";
    int suma = 0;
    for (int t = 1; t <= T; t++) {
        int x = prod[t][inventario];
        int j = inventario + x - d[t];
        int costoMes = (x > 0 ? K : 0) + c * x + h * j;
        suma += costoMes;
        cout << setw(3) << t << " | " << setw(7) << d[t] << " | " << setw(11) << inventario
             << " | " << setw(8) << x << " | " << setw(9) << j << " | " << setw(12) << costoMes << "\n";
        inventario = j;                                  
    }
    cout << "Suma de los costos mensuales (verificacion): " << suma << endl;
    return 0;
}

