#include <iostream>
#include <string>
#include <cctype>
#include <fstream>

using namespace std;

struct producto {
    int id;
    string nombre;
    int stock;
    float precio;
};

int cproductos = 0;
producto productos[50];

void ingresar_producto();
int buscar_por_nombre(string nombre);
void actualizar_stock(string nombre);
void generar_reporte();
void guardar_datos();
void cargar_datos();

int main()
{    
    cargar_datos();
    char opcion;
    do {
        cout << "SISTEMA DE FARMACIA\n";
        cout << "[1] Ingresar nuevo producto\n";
        cout << "[2] Buscar producto por nombre\n";
        cout << "[3] Actualizar stock\n";
        cout << "[4] Generar reporte\n";
        cout << "Ingrese su opcion: ";
        cin >> opcion;
        switch (opcion) {
        case '1': {
            ingresar_producto();
            break;
        }
        case '2': {
            string nombre;
            cout << "Ingrese el nombre del producto a buscar: ";
            cin.ignore();
            getline(cin, nombre);
            int index = buscar_por_nombre(nombre);
            if (index < 0) { 
                cout << "Producto no encontrado.\n";
                break; 
            }
            cout << "Producto Encontrado\n";
            cout << "Id: " << productos[index].id << endl;
            cout << "Nombre: " << productos[index].nombre << endl;
            cout << "Precio: " << productos[index].precio << endl;
            cout << "Stock: " << productos[index].stock << endl;

            break;
        }
        case '3': {
            string nombre;
            cout << "Ingrese el nombre del producto a actualizar: ";
            cin.ignore();
            getline(cin, nombre);
            actualizar_stock(nombre);
            break;
        }
        case '4': {
            generar_reporte();
        }
        }
    } while (opcion != 0);
    return 0;
}

void ingresar_producto() {
    string nombre;
    int stock, id;
    float precio;
    cout << "Ingrese el nombre del producto a registrar: ";
    cin.ignore();
    getline(cin, nombre);
    cout << "Ingrese el stock inicial del producto: ";
    cin >> stock;
    cout << "Ingrese el precio del producto: ";
    cin >> precio;

    productos[cproductos].id = cproductos+1;
    productos[cproductos].nombre = nombre;
    productos[cproductos].stock = stock;
    productos[cproductos].precio = precio;
    cproductos++;
    cout << "Producto agregado";
    guardar_datos();
}

int buscar_por_nombre(string nombre) {
    for (int i = 0; i < cproductos; i++) {
        if (productos[i].nombre == nombre) return i;
    }
    return -1;
}

void actualizar_stock(string nombre) {
    for (int i = 0; i < cproductos; i++) {
        if (productos[i].nombre == nombre) {
            int nuevo_stock;
            cout << "Producto encontrado.\n";
            cout << "Ingrese el nuevo stock: ";
            cin >> nuevo_stock;
            productos[i].stock = nuevo_stock;
            cout << "\nStock actualizado a " << nuevo_stock;
            guardar_datos();
            return;
        }
    }
    cout << "\nProducto no encontrado";
}
void generar_reporte() {
    float valor_total = 0;
    for (int i = 0; i < cproductos; i++) {
        float precio = productos[i].precio;
        int stock = productos[i].stock;
        float valor_total_producto = precio * stock;
        cout << "Producto: " << productos[i].nombre << ", Total: " << valor_total_producto<<endl;
        valor_total = valor_total + valor_total_producto;
    }
    cout << "Valor total del inventario: " << valor_total << endl;
}

void guardar_datos() {
    ofstream datosFarmacia("farmacia.txt", ios::out);
    if (datosFarmacia.is_open()) {
        for (int i = 0; i < cproductos; i++) {
            datosFarmacia << productos[i].id << " " << productos[i].nombre << " " << productos[i].precio << " " << productos[i].stock << endl;
        }
        datosFarmacia.close();
    }
}

void cargar_datos() {
    ifstream datosIn("farmacia.txt");
    int c_entrada = 0;
    while (c_entrada < 50 && datosIn >> productos[c_entrada].id >> productos[c_entrada].nombre >> productos[c_entrada].precio >> productos[c_entrada].stock) {
        cout << "Producto " << productos[c_entrada].nombre << " cargado." << endl;
        c_entrada++;
    }
    cproductos = c_entrada;
    datosIn.close();
}