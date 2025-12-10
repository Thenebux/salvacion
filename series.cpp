#include <iostream>
#include <string>
#include <cctype>
#include <fstream>

using namespace std;

int main()
{    
    int n;
    do {
        cout << "Ingrese el valor de N: ";
        cin >> n;
        if (n < 0) cout << "N debe ser positivo";
    } while (n <= 0);
    
    float suma_total = 0;

    for (float i = 0; i < n; i++) {
        float adicion = i * 2;
        float numerador = 2 + adicion;
        float denominador = 3 + adicion;
        float termino;
        termino = (numerador / denominador);
        cout << endl << numerador << "/" << denominador << " = " << termino;
        suma_total += termino;
    }
    
    cout << "\n\nSumatoria = " << suma_total;

    return 0;
}