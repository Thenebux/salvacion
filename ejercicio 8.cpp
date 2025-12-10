#include <iostream>
#include <string>
#include <cctype>
#include <fstream>

using namespace std;

struct Cliente {
    int id;
    string nombre;
    string telefono;
    string correo;
    string estado;
};

int c_clientes = 0;

const int MAX_CLIENTES = 100;

Cliente clientes[MAX_CLIENTES];

void registrar_cliente();
void consultar_cliente();
void modificar_datos();
void eliminar_cliente();
void listar_activos();
void guardar_datos();
void cargar_datos();

int main()
{    
    cargar_datos();
    char opcion = '0';
    while (opcion != '6') {
        cout << "\n\nMenu";
        cout << "\n[1] Registrar cliente";
        cout << "\n[2] Consultar cliente por ID";
        cout << "\n[3] Modificar datos de un cliente";
        cout << "\n[4] Eliminar cliente (logicamente)";
        cout << "\n[5] Listar activos";
        cout << "\n[6] Salir";
        cout << "\nIngrese su opcion: ";
        cin >> opcion;
        switch (opcion) {
        case '1': {
            registrar_cliente();
            break;
        }
        case '2': {
            consultar_cliente();
            break;
        }
        case '3': {
            modificar_datos();
            break;
        }
        case '4': {
            eliminar_cliente();
            break;
        }
        case '5': {
            listar_activos();
            break;
        }
        }
    }
    return 0;
}

void registrar_cliente() {
    string nombre, telefono, correo;
    cout << "\nIngrese el nombre del cliente: ";
    cin >> nombre;
    cout << "\nIngrese el telefono del cliente: ";
    cin >> telefono;
    cout << "\nIngrese el correo del cliente: ";
    cin >> correo;
    clientes[c_clientes].id = c_clientes+1;
    clientes[c_clientes].nombre = nombre;
    clientes[c_clientes].telefono = telefono;
    clientes[c_clientes].correo = correo;
    clientes[c_clientes].estado = "activo";
    cout << "\nCliente agregado exitosamente.";
    cout << "\nID: " << clientes[c_clientes].id;
    cout << "\nNombre: " << clientes[c_clientes].nombre;
    cout << "\nTelefono: " << clientes[c_clientes].telefono;
    cout << "\nCorreo: " << clientes[c_clientes].correo;
    c_clientes++;
    guardar_datos();
}
void consultar_cliente() {
    int id;
    cout << "\nIngrese el ID a consultar: ";
    cin >> id;
    for (int i = 0; i < c_clientes; i++) {
        if (clientes[i].id == id) {
            cout << "\nCliente encontrado.";
            cout << "\nID: " << clientes[i].id;
            cout << "\nNombre: " << clientes[i].nombre;
            cout << "\nTelefono: " << clientes[i].telefono;
            cout << "\nCorreo: " << clientes[i].correo;
            cout << "\nEstado: " << clientes[i].estado;
            
            return;            
        }
    }
    cout << "No se encontraron clientes con el ID solicitado";
}
void modificar_datos() {
    string nombre, telefono, correo;
    int id;
    cout << "\nIngrese el ID del cliente a modificar: ";
    cin >> id;
    for (int i = 0; i < c_clientes; i++) {
        if (clientes[i].id == id) {
            cout << "\nCliente encontrado.";
            cout << "\nID: " << clientes[i].id;
            cout << "\nNombre: " << clientes[i].nombre;
            cout << "\nTelefono: " << clientes[i].telefono;
            cout << "\nCorreo: " << clientes[i].correo;
            cout << "\nEstado: " << clientes[i].estado;

            cout << "\nIngrese el nuevo Nombre: ";
            cin >> nombre;
            cout << "\nIngrese el nuevo Telefono: ";
            cin >> telefono;
            cout << "\nIngrese el nuevo correo: ";
            cin >> correo;
            clientes[c_clientes].nombre = nombre;
            clientes[c_clientes].telefono = telefono;
            clientes[c_clientes].correo = correo;
            cout << "\nCliente modificado exitosamente.";
            cout << "\nID: " << id;
            cout << "\nNombre: " << nombre;
            cout << "\nTelefono: " << telefono;
            cout << "\nCorreo: " << correo;
            guardar_datos();
            return;
        }
    }
    cout << "No se encontraron clientes con el ID solicitado";
}

void eliminar_cliente() {
    int id;
    cout << "\nIngrese el ID a eliminar: ";
    cin >> id;
    for (int i = 0; i < c_clientes; i++) {
        if (clientes[i].id == id) {
            cout << "\nCliente encontrado.";
            cout << "\nID: " << clientes[i].id;
            cout << "\nNombre: " << clientes[i].nombre;
            cout << "\nTelefono: " << clientes[i].telefono;
            cout << "\nCorreo: " << clientes[i].correo;
            cout << "\nEstado: " << clientes[i].estado;

            char eleccion;
            cout << "\nDesea pasar este cliente a Inactivo? (S/N): ";
            cin >> eleccion;
            if (eleccion == 'S' || eleccion == 's') {
                clientes[i].estado = "inactivo";
                cout << "\nCliente desactivado exitosamente";
                guardar_datos();
            }
            else cout << "Volviendo al menu principal...";
            return;
        }
    }
    cout << "No se encontraron clientes con el ID solicitado";
}

void listar_activos() {
    for (int i = 0; i < c_clientes; i++) {
        if (clientes[i].estado == "activo") {
            cout << "\nCliente activo encontrado.";
            cout << "\n\tID: " << clientes[i].id;
            cout << "\n\tNombre: " << clientes[i].nombre;
            cout << "\n\tTelefono: " << clientes[i].telefono;
            cout << "\n\tCorreo: " << clientes[i].correo;
            cout << "\n\tEstado: " << clientes[i].estado;
        }
    }
}

void guardar_datos() {
    ofstream datosClientes("clientes.txt", ios::out);
    if (datosClientes.is_open()) {
        for (int i = 0; i < c_clientes; i++) {
            datosClientes << clientes[i].id << " " << clientes[i].nombre << " " << clientes[i].telefono << " " << clientes[i].correo << " " << clientes[i].estado << endl;
        }
        datosClientes.close();
    }
}

void cargar_datos() {
    ifstream datosIn("clientes.txt");
    int c_entradas = 0;
    while (datosIn >> clientes[c_entradas].id >> clientes[c_entradas].nombre >> clientes[c_entradas].telefono >> clientes[c_entradas].correo >> clientes[c_entradas].estado) {
        cout << "\nCliente cargado." << "\n\tID:" << clientes[c_entradas].id << "\n\tNombre: " << clientes[c_entradas].nombre;
        c_entradas++;
    }
    c_clientes = c_entradas+1;
    datosIn.close();
    cout << "\nCantidad de clientes cargados: " << c_clientes;
}