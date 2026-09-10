#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

// Metodo propuesto
int mcdDescomposicion(int a, int b) {
    int mcd = 1;
    int divisor = 2;

    while (divisor <= a && divisor <= b) {
        // Si el primo divide a ambos, es factor comun
        while (a % divisor == 0 && b % divisor == 0) {
            mcd *= divisor;
            a /= divisor;
            b /= divisor;
        }
        divisor++;
    }
    return mcd;
}

// metodo euclides
int mcdEuclides(int a, int b) {
    if (b == 0) return a;
    return mcdEuclides(b, a % b);
}

int main() {
    int a = 252, b = 198;

    cout << "MCD de " << a << " y " << b << endl;

    // Medicion de metodo propuesto
    auto inicio1 = chrono::high_resolution_clock::now();
    int resultado1 = mcdDescomposicion(a, b);
    auto fin1 = chrono::high_resolution_clock::now();
    long long tiempo1 = chrono::duration_cast<chrono::nanoseconds>(fin1 - inicio1).count();

    cout << "Metodo descomposicion canonica simultanea:" << endl;
    cout << "  MCD = " << resultado1 << endl;
    cout << "  Tiempo = " << tiempo1 << " ns" << endl;

    // Medicion Euclides
    auto inicio2 = chrono::high_resolution_clock::now();
    int resultado2 = mcdEuclides(a, b);
    auto fin2 = chrono::high_resolution_clock::now();
    long long tiempo2 = chrono::duration_cast<chrono::nanoseconds>(fin2 - inicio2).count();

    cout << "Metodo Euclides:" << endl;
    cout << "  MCD = " << resultado2 << endl;
    cout << "  Tiempo = " << tiempo2 << " ns" << endl;

    return 0;
}