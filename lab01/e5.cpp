#include <iostream>
using namespace std;

int main() {
    int n = 100;

    // Método 1: bucle
    int pasosBucle = 0;
    long long sumaBucle = 0;
    for (int i = 1; i <= n; i++) {
        sumaBucle += i;
        pasosBucle++;
    }

    cout << "Suma de los primeros " << n << " numeros naturales" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Metodo bucle:" << endl;
    cout << "  Suma = " << sumaBucle << endl;
    cout << "  Pasos realizados = " << pasosBucle << endl;
    cout << "  Complejidad: O(n)" << endl;

    cout << "----------------------------------------" << endl;

    // Método 2: fórmula
    int pasosFormula = 1;
    long long sumaFormula = (long long)n * (n + 1) / 2;

    cout << "Metodo formula n(n+1)/2:" << endl;
    cout << "  Suma = " << sumaFormula << endl;
    cout << "  Pasos realizados = " << pasosFormula << endl;
    cout << "  Complejidad: O(1)" << endl;

    cout << "----------------------------------------" << endl;
    cout << "Conclusion: el bucle realiza " << pasosBucle << " pasos O(n)" << endl;
    cout << "La formula realiza siempre 1 paso O(1), sin importar el valor de n" << endl;

    return 0;
}