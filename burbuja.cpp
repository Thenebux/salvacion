#include <iostream>
#include <string>
#include <cctype>
#include <fstream>

using namespace std;


int main()
{    
    int arreglo[6] = {8, 2, 5, 1, 9, 3};

    for (int i = 0; i < 6; i++) {
        cout << arreglo[i] << ", ";
    }

    //ordenamiento
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (arreglo[j] > arreglo[i]) {
                int aux = arreglo[i];
                arreglo[i] = arreglo[j];
                arreglo[j] = aux;
            }
        }
    }

    cout << endl << "Ordenado" << endl;

    for (int i = 0; i < 6; i++) {
        cout << arreglo[i] << ", ";
    }

    return 0;
}