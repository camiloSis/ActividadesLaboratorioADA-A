// PROBLEMAS PROPUESTOS 
// e1. Problema numerico: Diseñar un algoritmo que calcule el Máximo Común Divisor (MCD)
// de dos números enteros mediante dos funciones, una que utilice el método de Euclides
// y otra con bucles, comparen el tiempo de ejecución entre ambos. Expliquen ¿Cuántas 
// divisiones como máximo realiza el algoritmo de Euclides para el MCD?.

#include <iostream>
#include <chrono> // mide tiempo de ejecución 
using namespace std; 

// 1. Metodo euclides 

int mcdEuclides(int a, int b) {
    if (b == 0) return a;
    return mcdEuclides(b, a % b);
}

// 2. Metodo bucles 

int mcdBucle(int a, int b) {
    int mcd = 1;
    for (int i = 1; i <= min(a, b); i++) {
        if (a % i == 0 && b % i == 0)
            mcd = i;
    }
    return mcd;
}
int main(){

    int a = 225, b = 75;

        // Para euclides
        auto inicioEu = chrono::high_resolution_clock::now();
        // llamamos al metodo probando el algoritmo Euclides
        int resultadoEu = mcdEuclides(a,b);
        auto finEu = chrono::high_resolution_clock::now();
        cout << " mcd Euclides: " << resultadoEu << endl;
        cout << "tiempo Euclides: " << chrono::duration_cast<chrono::nanoseconds>(finEu - inicioEu).count() << " ns (nanosegundos)" << endl;

        // Para bucle
        auto inicioBucle = chrono::high_resolution_clock::now();
        // llamamos al metodo probando el algoritmo Bucles
        int resultadoBucle = mcdBucle(a,b);
        auto finBucle = chrono::high_resolution_clock::now();
        cout << " mcd Bucle: " << resultadoBucle << endl;
        cout << "tiempo Bucle: " << chrono::duration_cast<chrono::nanoseconds>(finBucle - inicioBucle).count() << " ns (nanosegundos)" << endl;

        return 0; 
}