#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool esPalindromo(int numero) {
    string s = to_string(numero);
    int comparaciones = 0;
    int inicio = 0, fin = s.length() - 1;
    while (inicio < fin) {
        comparaciones++;
        if (s[inicio] != s[fin]) {
            cout << "  Comparaciones realizadas: " << comparaciones << endl;
            return false;
        }
        inicio++;
        fin--;
    }
    cout << "  Comparaciones realizadas: " << comparaciones << endl;
    return true;
}

int main() {
    vector<int> numeros = {121, 123, 1331, 12321, 12345};

    for (int num : numeros) {
        cout << "Numero: " << num << endl;
        bool result = esPalindromo(num);
        cout << "  Es palindromo: " << (result ? "Si" : "No") << endl;
        cout << "  Digitos: " << to_string(num).length() << endl;
        cout << "  Complejidad: O(d/2) = O(d) donde d=numero de digitos" << endl;
        cout << "----------------------------------------" << endl;
    }

    return 0;
}