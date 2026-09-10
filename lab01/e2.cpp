#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// busqueda simple en texto
int busquedaSimple(string texto, string palabra) {
    int count = 0;
    size_t pos = 0;
    while ((pos = texto.find(palabra, pos)) != string::npos) {
        count++;
        pos++;
    }
    return count;
}

// busqueda binaria en lista ordenada
bool busquedaBinaria(vector<string>& lista, string palabra) {
    int inicio = 0, fin = lista.size() - 1;
    while (inicio <= fin) {
        int medio = (inicio + fin) / 2;
        if (lista[medio] == palabra) return true;
        else if (lista[medio] < palabra) inicio = medio + 1;
        else fin = medio - 1;
    }
    return false;
}

int main() {
    string texto = "el gato come pescado y el gato duerme y el gato juega";
    string palabra = "gato";

    cout << "Texto: " << texto << endl;
    cout << "Palabra buscada: " << palabra << endl;
    cout << "----------------------------------------" << endl;

    int repeticiones = busquedaSimple(texto, palabra);
    cout << "Busqueda simple:" << endl;
    cout << "  La palabra aparece " << repeticiones << " veces" << endl;
    cout << "  Complejidad: O(n*m) donde n=longitud texto, m=longitud palabra" << endl;

    cout << "----------------------------------------" << endl;

    vector<string> lista = {"banana", "gato", "manzana", "perro", "uva"};
    sort(lista.begin(), lista.end());

    cout << "Busqueda binaria en lista ordenada:" << endl;
    bool encontrado = busquedaBinaria(lista, palabra);
    cout << "  Palabra '" << palabra << "': " << (encontrado ? "encontrada" : "no encontrada") << endl;
    cout << "  Complejidad: O(log n) donde n=tamanio de la lista" << endl;

    cout << "----------------------------------------" << endl;
    cout << "Conclusion:" << endl;
    cout << "  Busqueda en texto crece linealmente con la longitud del texto O(n)" << endl;
    cout << "  Busqueda en lista ordenada crece logaritmicamente O(log n)" << endl;

    return 0;
}