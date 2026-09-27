#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <algorithm>
using namespace std;

void mergesortHelper(vector<int>& arr, int izq, int der) {
    if (izq < der) {
        int mid = (izq + der) / 2;
        mergesortHelper(arr, izq, mid);
        mergesortHelper(arr, mid + 1, der);
        vector<int> left(arr.begin() + izq, arr.begin() + mid + 1);
        vector<int> right(arr.begin() + mid + 1, arr.begin() + der + 1);
        int i = 0, j = 0, k = izq;
        while (i < left.size() && j < right.size())
            arr[k++] = (left[i] <= right[j]) ? left[i++] : right[j++];
        while (i < left.size()) arr[k++] = left[i++];
        while (j < right.size()) arr[k++] = right[j++];
    }
}

void quicksortHelper(vector<int>& arr, int izq, int der) {
    if (izq < der) {
        int pivot = arr[der], i = izq - 1;
        for (int j = izq; j < der; j++)
            if (arr[j] <= pivot) swap(arr[++i], arr[j]);
        swap(arr[i + 1], arr[der]);
        int pi = i + 1;
        quicksortHelper(arr, izq, pi - 1);
        quicksortHelper(arr, pi + 1, der);
    }
}

void insertionSort(vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) arr[j + 1] = arr[j--];
        arr[j + 1] = key;
    }
}

void selectionSort(vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < arr.size(); j++)
            if (arr[j] < arr[minIdx]) minIdx = j;
        swap(arr[i], arr[minIdx]);
    }
}

int main() {
    int n = 10000;
    vector<int> base(n);
    for (int i = 0; i < n; i++) base[i] = rand() % 100000;

    auto medir = [&](string nombre, auto func) {
        vector<int> arr = base;
        auto inicio = chrono::high_resolution_clock::now();
        func(arr);
        auto fin = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> tiempo = fin - inicio;
        cout << nombre << ": " << tiempo.count() << " ms\n";
    };

    cout << "Comparacion con " << n << " elementos aleatorios:\n";
    cout << "----------------------------------------\n";
    medir("Mergesort    O(n log n)", [](vector<int>& a){ mergesortHelper(a, 0, a.size()-1); });
    medir("Quicksort    O(n log n)", [](vector<int>& a){ quicksortHelper(a, 0, a.size()-1); });
    medir("InsertionSort O(n^2)   ", [](vector<int>& a){ insertionSort(a); });
    medir("SelectionSort O(n^2)   ", [](vector<int>& a){ selectionSort(a); });

    return 0;
}