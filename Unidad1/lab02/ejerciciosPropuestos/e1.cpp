#include <iostream>
#include <chrono>
using namespace std;

void printArray(int arr[], int n, int paso) {
    cout << "Paso " << paso << ": ";

    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << endl;
}

void insertionSort(int arr[], int n) {
    int paso = 0;

    printArray(arr, n, paso++);

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;

        printArray(arr, n, paso++);
    }
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
    int arrInsertion[] = {12, 5, -5, 23, 44, 67, 9, 10, 34, 1, -2};
    int arrSelection[] = {12, 5, -5, 23, 44, 67, 9, 10, 34, 1, -2};
    int n = sizeof(arrInsertion) / sizeof(arrInsertion[0]);

    cout << "Insertion Sort:" << endl;

        auto inicioInsertion = chrono::high_resolution_clock::now();
        insertionSort(arrInsertion, n);
        auto finInsertion = chrono::high_resolution_clock::now();

        auto tiempoInsertion = chrono::duration_cast<chrono::microseconds>(finInsertion - inicioInsertion);

        cout << "Tiempo de ejecucion de InsertionSort: "
            << tiempoInsertion.count()
            << " microsegundos" << endl;

    cout << "\nSelection Sort:" << endl;

        auto inicioSelection = chrono::high_resolution_clock::now();
        selectionSort(arrSelection, n);
        auto finSelection = chrono::high_resolution_clock::now();

        auto tiempoSelection = chrono::duration_cast<chrono::microseconds>(finSelection - inicioSelection);

        cout << "Tiempo de ejecucion de SelectionSort: "
            << tiempoSelection.count()
            << " microsegundos" << endl;

    return 0;
}