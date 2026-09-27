#include <iostream>
#include <chrono>
using namespace std;

void printArray(int arr[], int n, int paso) {
    cout << "Paso " << paso << ": ";

    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << endl;
}

void selectionSort(int arr[], int n) {
    int paso = 0;

    printArray(arr, n, paso++);

    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }

        swap(arr[i], arr[minIdx]);

        printArray(arr, n, paso++);
    }
}

int main() {
    int arr[] = {5, 2, 9, 1, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Selection Sort:" << endl;

    auto inicio = chrono::high_resolution_clock::now();

    selectionSort(arr, n);

    auto fin = chrono::high_resolution_clock::now();

    auto tiempo = chrono::duration_cast<chrono::microseconds>(fin - inicio);

    cout << "Tiempo de ejecucion: "
         << tiempo.count()
         << " microsegundos" << endl;

    return 0;
}