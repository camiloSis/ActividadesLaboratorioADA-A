#include <iostream> 
using namespace std; 
int main(){
    int numeros[6]={1,2,3,4,5};
        for ( int i = 0; i<6 ; i++){
            cout << numeros[i];
        }


    int suma = 0; 
        for (int i = 0 ; i < 6 ; i++){
            suma=suma+numeros[i];
        }

        cout << suma; 
        return 0;
}



