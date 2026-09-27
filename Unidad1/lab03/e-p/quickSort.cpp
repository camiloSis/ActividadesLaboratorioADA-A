#include <iostream>
using namespace std;
void merge(int arr[], int izq, int medio, int der)
{
    int n1 = medio - izq + 1;
    int n2 = der - medio;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[izq + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[medio + 1 + j];
    int i = 0, j = 0, k = izq;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}
void mergeSort(int arr[], int izq, int der)
{
    if (izq < der)
    {
        int medio = izq + (der - izq) / 2;
        mergeSort(arr, izq, medio);
        mergeSort(arr, medio + 1, der);
        merge(arr, izq, medio, der);
    }
}
int main()
{
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    mergeSort(arr, 0, n - 1);
    cout << "Arreglo ordenado: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    return 0;
}