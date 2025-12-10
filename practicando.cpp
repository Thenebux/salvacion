#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool validar_float(string cadena);
//int leer_entero(string mensaje);

int main()
{
    //sesion 9, cctype profe, si vale ok :)
    
    string cadena;
    getline(cin, cadena);

    if (validar_float(cadena)) {
        cout << "Si";
    }
    else cout << "No";


}

bool validar_float(string cadena) {
    if (cadena.length() == 0 || cadena[0] == '.') return false;
    int puntos = 0;
    for (int i = 0; i < cadena.length(); i++) {
        if (cadena[i] == '.') {
            puntos++;
            if (puntos > 1) return false;
        if (!isdigit(cadena[i])) {
            return false;
        }
    }
    return true;
}

//int leer_numero(string mensaje) {
//    char entrada[20];
//    cin >> entrada;
//    
//}
