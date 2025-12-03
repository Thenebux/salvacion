#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// --- CÃ³digos de color ANSI ---
const string reset = "\033[0m";
const string rojo = "\033[31m";
const string verde = "\033[32m";
const string amarillo = "\033[33m";
const string azul = "\033[34m";
const string magenta = "\033[35m";
const string cyan = "\033[36m";
const string gris = "\033[90m";
const string blanco = "\033[37m";

const int FILAS = 6;
const int COLUMNAS = 7;

struct Celda {
    string curso;
    string docente;
    string aula;
    int creditos;
    string color;
};
string nombreDia(int d); 
string elegirHorario();
string elegirHorario2();
bool cargarHorario(const string &nombre, Celda h[FILAS][COLUMNAS]);
void guardarHorario(const string &nombre, Celda h[FILAS][COLUMNAS]);
int listarHorariosDesdeTXT(string nombres[], int max);
void eliminarHorario();
void crear_datos(Celda h[FILAS][COLUMNAS]);
void imprimir_datos(Celda h[FILAS][COLUMNAS]);
void registrarClase(Celda h[FILAS][COLUMNAS]);
void consultarClase(Celda h[FILAS][COLUMNAS]);
void modificarClase(Celda h[FILAS][COLUMNAS]);
void buscarPorDocente(Celda h[FILAS][COLUMNAS]);
void contarHoras(Celda h[FILAS][COLUMNAS]);

// prototipos reportes
void menuReportes(Celda h[FILAS][COLUMNAS]);
void reporte_filtrar_docente(Celda h[FILAS][COLUMNAS]);
void reporte_filtrar_curso(Celda h[FILAS][COLUMNAS]);
void reporte_filtrar_aula(Celda h[FILAS][COLUMNAS]);
void reporte_total_horas_y_dias(Celda h[FILAS][COLUMNAS]);
int carga_horaria_docente(Celda h[FILAS][COLUMNAS], const string &docente, bool mostrarDetalle);
void reporte_conflictos();
void reporte_busqueda_parcial(Celda h[FILAS][COLUMNAS]);
void guardarArchivo(Celda h[FILAS][COLUMNAS]);
void cargarArchivo(Celda h[FILAS][COLUMNAS]);
string leerTextoConComillas(ifstream &arch);
int horasUsadasCurso(Celda h[FILAS][COLUMNAS], const string &curso);
void reporte_creditos_barras_vertical(Celda h[FILAS][COLUMNAS]);

int main() {
	setlocale(LC_ALL, "es_ES.UTF-8");
	Celda horario[FILAS][COLUMNAS];
	crear_datos(horario);
	int opcion;

	do {
        cout << "\n========= CALENDARIO ACADEMICO =========\n";
        cout << "1. Registrar nueva clase\n";
        cout << "2. Listar horario completo\n";
        cout << "3. Consultar clases de un dia / curso / docente\n";
        cout << "4. Modificar una clase\n";
        cout << "5. Buscar clases por docente\n";
        cout << "6. Contar horas de curso o docente\n";
        cout << "7. Guardar(hacer una copia) o eliminar horario en archivo \n";
        cout << "8. Cargar horario desde archivo \n";
        cout << "9. Mostrar reporte de clases\n";
        cout << "10. Salir\n";
        cout << "========================================\n";
		while (true) {

			cout << "Ingrese una opcion: ";
			cin >> opcion;
			if (cin.fail()) {
				cout << "Error: Ingrese solo numeros\n";
				cin.clear();
				cin.ignore(1000, '\n');
			}
			else if (opcion >= 1 && opcion <= 10) {
				break;
			}
			else {
				cout << "Opcion invalida\n";
			}
		}


		switch (opcion) {
        case 1: registrarClase(horario); break;
        case 2: imprimir_datos(horario); break;
        case 3: consultarClase(horario); break;
        case 4: modificarClase(horario); break;
        case 5: buscarPorDocente(horario); break;
        case 6: contarHoras(horario); break;
        case 7: guardarArchivo(horario); break;
        case 8: cargarArchivo(horario); break;
        case 9: menuReportes(horario); break;
        case 10: cout << "Cerrando programa...\n"; break;
        }
    } while (opcion != 10);

	return 0;
}

string nombreDia(int d) {
    switch (d) {
        case 1: return "Lunes";
        case 2: return "Martes";
        case 3: return "Miercoles";
        case 4: return "Jueves";
        case 5: return "Viernes";
        case 6: return "Sabado";
        case 7: return "Domingo";
        default: return "Desconocido";
    }
}
int horasUsadasCurso(Celda h[FILAS][COLUMNAS], const string &curso) {
    int total = 0;
    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            if (h[i][j].curso == curso)
                total++;
    return total;
}


void crear_datos(Celda h[FILAS][COLUMNAS]) {
	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLUMNAS; j++) {
			h[i][j].curso = "Vacio";
			h[i][j].docente = "";
            h[i][j].aula = "";
            h[i][j].creditos = 0;
            h[i][j].color = gris;
		}
	}
}

void imprimir_datos(Celda h[FILAS][COLUMNAS]) {
	int hora =7 ;
	cout << "+--------------------------------------------------------------------------------------------------+\n";
	cout << "| Hora  | Lunes      | Martes     | Miercoles  | Jueves     | Viernes    | Sabado     | Domingo    |\n";
	for (int i = 0; i < FILAS; i++) {
		cout << "+--------------------------------------------------------------------------------------------------+\n";
		if (hora < 10) cout << "| 0" << hora << ":00\t";
		else cout << "| " << hora << ":00\t";

		cout << "|";
		for (int j = 0; j < COLUMNAS; j++) {
			cout << h[i][j].color << h[i][j].curso << reset;
			for (int k = 0; k < 12 - h[i][j].curso.size(); k++) {
				cout << " ";
			}
			cout << "|";
		}
		hora++;
		cout << endl;
	}
	cout << "+--------------------------------------------------------------------------------------------------+\n";
}
void registrarClase(Celda h[FILAS][COLUMNAS]) {
    string curso, docente, aula, color;
    int dia = 0, hora = 0, horasSeguidas = 0, creditos = 0, scolor = 0;

    string horario = elegirHorario();
	if (horario == "") return;

	if (!cargarHorario(horario, h)) {
    	cout << "Horario vacio. Se creara uno nuevo.\n";
    	crear_datos(h);
	}

	
	
	
	cout << "\n=== REGISTRO DE CLASE ===\n";
    while (true) {
        cout << "\nIngrese el curso a asignar (max. 12 caracteres): ";
        getline(cin, curso);
        if (curso.length() <= 12 && curso.size() > 0){
			break;
		} 
        cout << "Longitud invalida\n";
    }

    // Buscar si el curso ya existe y tomar sus datos si existe
    bool cursoExiste = false;
    for (int i = 0; i < FILAS && !cursoExiste; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (h[i][j].curso == curso) {
                cursoExiste = true;
                docente = h[i][j].docente;
                aula = h[i][j].aula;
                creditos = h[i][j].creditos;
                color = h[i][j].color;
                break;
            }
        }
    }

    if (cursoExiste) {
        cout << "\nEl curso ya existe en el horario.\n";
        cout << "Docente: " << docente << "\nAula: " << aula << "\nCreditos: " << creditos << "\n";
        cout << "Color ya asignado.\n";
        
    } else {
        // pedir datos completos si es nuevo curso
        cout << "Docente: ";
        getline(cin, docente);
        cout << "Aula: ";
        getline(cin, aula);

        while (true) {
            cout << "Creditos (1-7): ";
            cin >> creditos;
            if (cin.fail()) {
            	cout << "Error: Ingrese solo numeros.\n";
            	cin.clear();
            	cin.ignore(1000, '\n');
        	}
        	else if (creditos < 1 || creditos > 7) {
            	cout << "Rango invalido.\n";
        	}
        	else {
            	cin.ignore(1000, '\n');
            	break;
        	}
        }

        while (true) {
            cout << "\nColores disponibles:\n";
			cout << "[1] Rojo\n";
			cout << "[2] Verde\n";
			cout << "[3] Amarillo\n";
			cout << "[4] Azul\n";
			cout << "[5] Magenta\n";
			cout << "[6] Cyan\n";
			cout << "[7] Gris\n";
			cout << "[8] Blanco\n";
			cout << "\nIngrese el color del curso: ";
            cin >> scolor;
			if (cin.fail()) {
				cout << "Error: Ingrese solo numeros\n";
				cin.clear();
				cin.ignore(1000, '\n');
			}
			else if (scolor >= 1 && scolor <= 8) {
				switch (scolor) {
				case 1: color = rojo; break;
				case 2: color = verde; break;
				case 3: color = amarillo; break;
				case 4: color = azul; break;
				case 5: color = magenta; break;
				case 6: color = cyan; break;
				case 7: color = gris; break;
				case 8: color = blanco; break;
				}
				break;
			}
			else {
				cout << "Color invalido\n";
			}
        }
    }
    
	int horasActuales = horasUsadasCurso(h, curso);
    int horasRestantes = creditos - horasActuales;

    if (horasRestantes <= 0) {
        cout << "\nEste curso ya completo todas sus horas.\n";
        return;
    }

    cout << "El curso requiere " << creditos << " horas.\n";
    cout << "Horas ya registradas: " << horasActuales << "\n";
    cout << "Horas restantes: " << horasRestantes << "\n\n";
    
	
	
	// Pedir día y hora inicial para el primer bloque (siempre)
    while (true) {
        cout << "[1] Lunes\n";
		cout << "[2] Martes\n";
		cout << "[3] Miercoles\n";
		cout << "[4] Jueves\n";
		cout << "[5] Viernes\n";
		cout << "[6] Sabado\n";
		cout << "[7] Domingo\n";
        cout << "Ingrese el dia para el primer bloque: ";
        cin >> dia;
        if (cin.fail()) {
			cout << "Error: Ingrese solo numeros\n";
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else if (dia >= 1 && dia <= 7) {
			break;
		}
		else {
			cout << "Dia invalido\n";
		}
    }
    while (true) {
        cout << "\nHora inicial (7-12): ";
		cin >> hora;

		if (cin.fail()) {
			cout << "Error: Ingrese solo numeros\n";
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else if (hora >= 7 && hora <= 12) {
			break;
		}
		else {
			cout << "Hora invalida\n";
		}
    }

    // PRIMER BLOQUE: pedir cantidad de horas contiguas (para el bloque inicial)
    while (true) {
        cout << "Horas seguidas a registrar (1-" << horasRestantes << "): ";
        cin >> horasSeguidas;
        if (!cin.fail() && horasSeguidas >= 1 && horasSeguidas <= horasRestantes &&(hora - 7 + horasSeguidas <= FILAS)) {
			break;
        }
        else{
        	cout << "Cantidad invalida o sin espacio.\n";
            cin.clear(); 
			cin.ignore(1000,'\n');
        	
		}
		
    }

    // Verificar colisiones en el bloque inicial
    for (int i = 0; i < horasSeguidas; i++) {
        int f = (hora - 7) + i;
        int c = dia - 1;
        if (h[f][c].curso != "Vacio" && h[f][c].curso != curso) {
            cout << "\nYa existe otra clase en esa hora (" << h[f][c].curso << ").\n";
            cout << "   1) Si, reemplazar esa(s) hora(s)\n";
            cout << "   2) No, elegir otra hora/dia\n";
            cout << "   3) Cancelar registro\n";
            cout << "Opcion: ";
            int op; cin >> op;
            if (cin.fail()) { 
				cin.clear(); 
				cin.ignore(1000,'\n'); 
				cout << "Entrada invalida. Cancelado.\n"; 
				return; 
			}
            if (op == 2) {
                // permitir al usuario reingresar día/hora (simplifico pidiendo que vuelva a llamar la función)
                cout << "Elige otra hora/dia iniciando el registro de nuevo.\n";
                return;
            }
            if (op == 3) { cout << "Registro cancelado.\n"; return; }
            // si op == 1: continúa y reemplaza
            break;
        }
    }

    // Registrar primer bloque (reemplaza si hay algo distinto)
    for (int i = 0; i < horasSeguidas; i++) {
        int fila = (hora - 7) + i;
        int col = dia - 1;
        h[fila][col].curso = curso;
        h[fila][col].docente = docente;
        h[fila][col].aula = aula;
        h[fila][col].creditos = creditos;
        h[fila][col].color = color;
    }
    horasRestantes -= horasSeguidas;

    // BLOQUES ADICIONALES: mientras falten horas, solicitar nuevos bloques (día/hora/bloque)
    while (horasRestantes > 0) {
        cout << "\nFaltan " << horasRestantes << " horas por asignar.\n";
        int nuevoDia = 0, nuevaHora = 0, nuevoBloque = 0;

        while (true) {
            cout << "Elija otro dia a registrar (1-7) o 0 para cancelar: \n";
            cout << "[1] Lunes\n";
			cout << "[2] Martes\n";
			cout << "[3] Miercoles\n";
			cout << "[4] Jueves\n";
			cout << "[5] Viernes\n";
			cout << "[6] Sabado\n";
			cout << "[7] Domingo\n";
            cin >> nuevoDia;
            if (cin.fail()) { 
				cin.clear(); 
				cin.ignore(1000,'\n'); 
				cout << "Valor inválido.\n"; 
				continue; 
			}
            if (nuevoDia == 0) { 
				cout << "Registro parcial guardado.\n"; 
				imprimir_datos(h); 
				return; 
			}
            if (nuevoDia >= 1 && nuevoDia <= 7){
            	break;
			} 
            cout << "Valor inválido.\n";
        }

        while (true) {
            cout << "Nueva hora inicial (7-12): ";
            cin >> nuevaHora;
            
			if (!cin.fail() && nuevaHora >= 7 && nuevaHora <= 12) { 
				break;
			}
            else{
            	cout << "Inválido.\n"; 
				cin.clear(); 
				cin.ignore(1000,'\n'); 
			}

        }

        while (true) {
            cout << "Horas seguidas (1-" << horasRestantes << "): ";
            cin >> nuevoBloque;
            if (!cin.fail() && nuevoBloque >= 1 && nuevoBloque <= horasRestantes && (nuevaHora - 7 + nuevoBloque <= FILAS)) {
                break;
                
            }
            else{
            	cout << "Cantidad invalida.\n";
            	cin.clear(); 
				cin.ignore(1000,'\n');
			}

			
        }

        // Verificar colisiones para el bloque nuevo
        bool conflicto = false;
        for (int i = 0; i < nuevoBloque; i++) {
            int f = (nuevaHora - 7) + i;
            int c = nuevoDia - 1;
            if (h[f][c].curso != "Vacio" && h[f][c].curso != curso) {
                cout << "Conflicto: ya existe clase (" << h[f][c].curso << ") en ese bloque.\n";
                conflicto = true;
                break;
            }
        }
        if (conflicto) {
            cout << "Elige otro bloque.\n";
            
        }

        // Registrar bloque nuevo
        for (int i = 0; i < nuevoBloque; i++) {
            int f = (nuevaHora - 7) + i;
            int c = nuevoDia - 1;
            h[f][c].curso = curso;
            h[f][c].docente = docente;
            h[f][c].aula = aula;
            h[f][c].creditos = creditos;
            h[f][c].color = color;
        }
        horasRestantes -= nuevoBloque;
    }

    cout << "\nClases registradas correctamente.\n";
    guardarHorario(horario, h);

	imprimir_datos(h);
    
}
    


void consultarClase(Celda h[FILAS][COLUMNAS]) {
	int modo;

    cout << "\n=== CONSULTAR ===\n";
    cout << "1. Consultar por dia\n";
    cout << "2. Consultar por docente\n";
    cout << "3. Consultar por curso\n";

    while (true) {
        cout << "Opcion: ";
        cin >> modo;

        if (cin.fail()) {
            cout << "Error: Ingrese solo numeros.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if (modo < 1 || modo > 3) {
            cout << "Opcion invalida.\n";
        }
        else {
            cin.ignore(1000, '\n');
            break;
        }
    }

  
    if (modo == 1) {
        int dia;
        cout << "Dia (1-7): \n";
        cout << "[1] Lunes\n";
		cout << "[2] Martes\n";
		cout << "[3] Miercoles\n";
		cout << "[4] Jueves\n";
		cout << "[5] Viernes\n";
		cout << "[6] Sabado\n";
		cout << "[7] Domingo\n";
		cout<<"Elige un dia:\n ";

        while (true) {
            cin >> dia;

            if (cin.fail()) {
                cout << "Error: Ingrese solo numeros.\n";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            else if (dia < 1 || dia > 7) {
                cout << "Rango invalido.\n";
            }
            else {
                break;
            }
        }

        int hora = 7;
        for (int i = 0; i < FILAS; i++) {
            Celda c = h[i][dia - 1];

            cout << hora++ << ":00  :  "
                 << c.color << c.curso << reset
                 << " | Docente: " << c.docente
                 << " | Aula: " << c.aula
                 << " | Creditos: " << c.creditos
                 << endl;
        }
    }

  
    else if (modo == 2) {
        string nom;
        cout << "Docente: ";
        getline(cin, nom);
        

        bool encontrado = false;
        int hora = 7;

        for (int i = 0; i < FILAS; i++)
            for (int j = 0; j < COLUMNAS; j++)
                if (h[i][j].docente == nom) {
                    cout << "Dia " << nombreDia(j+1)
                         << " Hora " << (i + 7)
                         << ":00  " << h[i][j].curso << endl;
                    encontrado = true;
                }

        if (!encontrado) cout << "No se encontraron clases.\n";
    }

  
    else {
        string nom;
        cout << "Curso: ";
        getline(cin, nom);
        

        bool encontrado = false;

        for (int i = 0; i < FILAS; i++)
            for (int j = 0; j < COLUMNAS; j++)
                if (h[i][j].curso == nom) {
                    cout << "Dia " << nombreDia(j+1)
                         << " Hora " << (i + 7)
                         << ":00  Docente: " << h[i][j].docente << endl;
                    encontrado = true;
                }

        if (!encontrado) cout << "No se encontraron clases.\n";
    }
}

void modificarClase(Celda h[FILAS][COLUMNAS]) {
    cout << "\n=== MODIFICAR CLASE ===\n";
    string horario = elegirHorario2();
    if (horario == "") return;

    if (!cargarHorario(horario, h)) {
        cout << "Horario vacio. Se creara uno nuevo.\n";
        crear_datos(h);
    }

    int dia, hora;
	imprimir_datos(h);
    // PEDIR DIA
    while (true) {
        cout << "Dia (1-7):\n";
        cout << "[1] Lunes\n";
		cout << "[2] Martes\n";
		cout << "[3] Miercoles\n";
		cout << "[4] Jueves\n";
		cout << "[5] Viernes\n";
		cout << "[6] Sabado\n";
		cout << "[7] Domingo\n";
		cout<<"Elige un dia:\n ";
        cin >> dia;
        if (!cin.fail() && dia >= 1 && dia <= 7) break;
        cin.clear(); cin.ignore(1000,'\n');
        cout << "Valor invalido.\n";
    }

    // PEDIR HORA
    while (true) {
        cout << "Hora de ese dia que deseas modificar( es parara modificar todo esa clase) (7-12): ";
        cin >> hora;
        if (!cin.fail() && hora >= 7 && hora <= 12) break;
        cin.clear(); cin.ignore(1000,'\n');
        cout << "Valor invalido.\n";
    }
    cin.ignore();

    Celda &c = h[hora - 7][dia - 1];

    // NO SE PUEDE MODIFICAR UNA CELDA VACIA
    if (c.curso == "Vacio") {
        cout << "\nNo hay clase en este horario. No se puede modificar.\n";
        return;
    }

    string cursoOriginal = c.curso;

    cout << "\nModificar curso: " << cursoOriginal << "\n";
    cout << "1. Cambiar docente (a todas las horas del curso)\n";
    cout << "2. Cambiar aula (a todas las horas del curso)\n";
    cout << "3. Cambiar color (a todas las horas del curso)\n";
    cout << "4. Cambiar datos completos del curso\n";
    cout << "5. Cambiar creditos del curso\n";
    cout << "6. Eliminar TODAS las horas del curso\n";
    cout << "Presiona cualquier otro numero si deseas cancelar\n";
    cout << "Opcion: ";

    int op;
    cin >> op;
    cin.ignore();

    if (op == 1) {
        string nuevoDoc;
        cout << "Nuevo docente: ";
        getline(cin, nuevoDoc);

        // Actualizar todas las horas del curso
        for (int i = 0; i < FILAS; i++)
            for (int j = 0; j < COLUMNAS; j++)
                if (h[i][j].curso == cursoOriginal)
                    h[i][j].docente = nuevoDoc;

        cout << "Docente actualizado correctamente.\n";
    }

    else if (op == 2) {
        string nuevaAula;
        cout << "Nueva aula: ";
        getline(cin, nuevaAula);

        for (int i = 0; i < FILAS; i++)
            for (int j = 0; j < COLUMNAS; j++)
                if (h[i][j].curso == cursoOriginal)
                    h[i][j].aula = nuevaAula;

        cout << "Aula actualizada correctamente.\n";
    }

    else if (op == 3) {
        int scolor;
        string nuevoColor;

        cout << "Elige color (1-8):\n ";
		cout << "[1] Rojo\n";
		cout << "[2] Verde\n";
		cout << "[3] Amarillo\n";
		cout << "[4] Azul\n";
		cout << "[5] Magenta\n";
		cout << "[6] Cyan\n";
		cout << "[7] Gris\n";
		cout << "[8] Blanco\n";
        cin >> scolor;

        switch (scolor) {
            case 1: nuevoColor = rojo; break;
            case 2: nuevoColor = verde; break;
            case 3: nuevoColor = amarillo; break;
            case 4: nuevoColor = azul; break;
            case 5: nuevoColor = magenta; break;
            case 6: nuevoColor = cyan; break;
            case 7: nuevoColor = gris; break;
            case 8: nuevoColor = blanco; break;
            default: cout << "Color invalido.\n"; return;
        }

        for (int i = 0; i < FILAS; i++)
            for (int j = 0; j < COLUMNAS; j++)
                if (h[i][j].curso == cursoOriginal)
                    h[i][j].color = nuevoColor;

        cout << "Color actualizado.\n";
    }

    else if (op == 4) {
        cout << "\n=== NUEVOS DATOS COMPLETOS ===\n";

        string nuevoCurso, nuevoDoc, nuevaAula;
        int nuevosCreditos, scolor;
        string nuevoColor;

        cout << "Nuevo nombre del curso: ";
        getline(cin, nuevoCurso);

        cout << "Nuevo docente: ";
        getline(cin, nuevoDoc);

        cout << "Nueva aula: ";
        getline(cin, nuevaAula);

        while (true) {
            cout << "Creditos (1-7): ";
            cin >> nuevosCreditos;
            if (!cin.fail() && nuevosCreditos >= 1 && nuevosCreditos <= 7) break;
            cin.clear(); cin.ignore(1000,'\n');
        }
		cout << "\nColores disponibles:\n";
		cout << "[1] Rojo\n";
		cout << "[2] Verde\n";
		cout << "[3] Amarillo\n";
		cout << "[4] Azul\n";
		cout << "[5] Magenta\n";
		cout << "[6] Cyan\n";
		cout << "[7] Gris\n";
		cout << "[8] Blanco\n";
        cout << "Color (1-8): ";
        cin >> scolor;

        switch (scolor) {
            case 1: nuevoColor = rojo; break;
            case 2: nuevoColor = verde; break;
            case 3: nuevoColor = amarillo; break;
            case 4: nuevoColor = azul; break;
            case 5: nuevoColor = magenta; break;
            case 6: nuevoColor = cyan; break;
            case 7: nuevoColor = gris; break;
            case 8: nuevoColor = blanco; break;
            default: cout << "Color invalido.\n"; return;
        }

        int horasActuales = horasUsadasCurso(h, cursoOriginal);

        if (horasActuales > nuevosCreditos) {
            cout << "\nERROR: Este curso ya tiene " << horasActuales 
                 << " horas asignadas.\nNo puedes bajar los creditos a " 
                 << nuevosCreditos << ".\n";
            return;
        }

        // Aplicar cambios a todas las celdas del curso
        for (int i = 0; i < FILAS; i++) {
            for (int j = 0; j < COLUMNAS; j++) {
                if (h[i][j].curso == cursoOriginal) {
                    h[i][j].curso = nuevoCurso;
                    h[i][j].docente = nuevoDoc;
                    h[i][j].aula = nuevaAula;
                    h[i][j].creditos = nuevosCreditos;
                    h[i][j].color = nuevoColor;
                }
            }
        }

        cout << "Datos del curso actualizados.\n";
    }
    else if (op == 5) {
        int nuevosCreditos;
        while (true) {
            cout << "Nuevos creditos (1-7): ";
            cin >> nuevosCreditos;
            if (!cin.fail() && nuevosCreditos >= 1 && nuevosCreditos <= 7) break;
            cin.clear(); cin.ignore(1000,'\n');
        }

        int horasActuales = horasUsadasCurso(h, cursoOriginal);

        if (horasActuales > nuevosCreditos) {
            cout << "\nERROR: el curso ya usa " << horasActuales
                 << " horas. No puedes bajar los créditos.\n";
            return;
        }

        for (int i = 0; i < FILAS; i++)
            for (int j = 0; j < COLUMNAS; j++)
                if (h[i][j].curso == cursoOriginal)
                    h[i][j].creditos = nuevosCreditos;

        cout << "Créditos actualizados correctamente.\n";
    }

    else if (op == 6) {
        cout << "\nEstas seguro de eliminar TODAS las horas del curso "
             << cursoOriginal << " (s/n): ";
        char cfm;
        cin >> cfm;

        if (cfm != 's' && cfm != 'S') {
            cout << "Cancelado.\n";
            return;
        }

        for (int i = 0; i < FILAS; i++)
            for (int j = 0; j < COLUMNAS; j++)
                if (h[i][j].curso == cursoOriginal) {
                    h[i][j].curso = "Vacio";
                    h[i][j].docente = "";
                    h[i][j].aula = "";
                    h[i][j].creditos = 0;
                    h[i][j].color = gris;
                }

        cout << "Curso eliminado correctamente.\n";
    }
    else {
        cout << "Opcion invalida.\n";
        return;
    }

    guardarHorario(horario, h);
    imprimir_datos(h);
}



void buscarPorDocente(Celda h[FILAS][COLUMNAS]) {
    string doc;
    cin.ignore();
    cout << "Ingrese nombre del docente: ";
    getline(cin, doc);

    bool encontrado = false;

    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            if (h[i][j].docente == doc) {
                cout << "Dia " << nombreDia(j+1)
                     << " | Hora " << (i+7) << ":00"
                     << " | Curso: " << h[i][j].curso
                     << endl;
                encontrado = true;
            }

    if (!encontrado)
        cout << "No se encontraron clases para ese docente.\n";
}


void contarHoras(Celda h[FILAS][COLUMNAS]) {
    int modo;
    cout << "1) Por curso\n";
	cout<<"2) Por docente\n";

    while (true) {
        cout << "Opcion: ";
        cin >> modo;

        if (cin.fail()) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "Error.\n";
        }
        else if (modo < 1 || modo > 2) {
            cout << "Invalido.\n";
        }
        else break;
    }

    cin.ignore();

    string buscado;
    if (modo == 1) {
        cout << "Curso: ";
        getline(cin, buscado);
    } else {
        cout << "Docente: ";
        getline(cin, buscado);
    }

    int contador = 0;

    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            if ((modo == 1 && h[i][j].curso == buscado) ||(modo == 2 && h[i][j].docente == buscado)){
				contador++;
			}
            
                

    cout << "Total de horas: " << contador << endl;
}

///////////////
void menuReportes(Celda h[FILAS][COLUMNAS]) {
    int op;
    do {
        cout << "\n========= REPORTES =========\n";
        cout << "1. Filtrar por docente\n";
        cout << "2. Filtrar por curso\n";
        cout << "3. Filtrar por aula\n";
        cout << "4. Total de horas dictadas y dias disponibles\n";
        cout << "5. Carga horaria semanal de un docente\n";
        cout << "6. Verificar conflictos de horario (docente/aula)\n";
        cout << "7. Buscar curso por coincidencia parcial\n";
        cout << "8. Grafico de barra segun creditos academico \n";
        cout << "9. Volver al menu principal\n";

        while (true) {
            cout << "Opcion: ";
            cin >> op;
            if (cin.fail()) {
                cout << "Error: ingrese solo numeros.\n";
                cin.clear(); cin.ignore(1000, '\n');
            } else if (op < 1 || op > 9) {
                cout << "Opcion invalida.\n";
            } else {
                cin.ignore(1000, '\n');
                break;
            }
        }

        switch (op) {
            case 1: reporte_filtrar_docente(h); break;
            case 2: reporte_filtrar_curso(h); break;
            case 3: reporte_filtrar_aula(h); break;
            case 4: reporte_total_horas_y_dias(h); break;
            case 5: {
                string doc;
                cout << "Docente: ";
                getline(cin, doc);
                int horas = carga_horaria_docente(h, doc, true);
                cout << "Total horas semana para " << doc << ": " << horas << "\n";
                break;
            }
            case 6: reporte_conflictos(); break;
            case 7: reporte_busqueda_parcial(h); break;
            case 8: reporte_creditos_barras_vertical(h); break;
			case 9: cout << "Volviendo...\n"; break;
        }
    } while (op != 9);
}

void reporte_filtrar_docente(Celda h[FILAS][COLUMNAS]) {
    string doc;
    cout << "Ingrese docente a filtrar: ";
    getline(cin, doc);

    bool nohay = false;
    for (int j = 0; j < COLUMNAS; j++)
        for (int i = 0; i < FILAS; i++)
            if (h[i][j].docente == doc && h[i][j].curso != "Vacio") {
                cout << "Dia " << nombreDia(j+1) << " Hora " << (i+7) << ":00 -> " << h[i][j].curso
                     << " | Aula: " << h[i][j].aula << " | Cred: " << h[i][j].creditos << "\n";
                nohay = true;
            }
    if (!nohay) cout << "No se encontraron clases para ese docente.\n";
}

void reporte_filtrar_curso(Celda h[FILAS][COLUMNAS]) {
    string curso;
    cout << "Ingrese curso a filtrar: ";
    getline(cin, curso);

    bool nohay = false;
    for (int j = 0; j < COLUMNAS; j++)
        for (int i = 0; i < FILAS; i++)
            if (h[i][j].curso == curso && h[i][j].curso != "Vacio") {
                cout << "Dia " << nombreDia(j+1) << " Hora " << (i+7) << ":00 -> Docente: " << h[i][j].docente
                     << " | Aula: " << h[i][j].aula << " | Cred: " << h[i][j].creditos << "\n";
                nohay = true;
            }
    if (!nohay) cout << "No se encontraron clases para ese curso.\n";
}

void reporte_filtrar_aula(Celda h[FILAS][COLUMNAS]) {
    string aula;
    cout << "Ingrese aula a filtrar: ";
    getline(cin, aula);

    bool nohay = false;
    for (int j = 0; j < COLUMNAS; j++)
        for (int i = 0; i < FILAS; i++)
            if (h[i][j].aula == aula && h[i][j].curso != "Vacio") {
                cout << "Dia " << nombreDia(j+1) << " Hora " << (i+7) << ":00 -> Curso: " << h[i][j].curso
                     << " | Docente: " << h[i][j].docente << " | Cred: " << h[i][j].creditos << "\n";
                nohay = true;
            }
    if (!nohay) cout << "No se encontraron clases para esa aula.\n";
}

void reporte_total_horas_y_dias(Celda h[FILAS][COLUMNAS]) {
    cout << "Mostrar total por: \n";
    cout << "(1) Curso:\n ";
    cout << "(2) Docente: \n";
    int modo;
    while (true) {
        cin >> modo;
        if (cin.fail()) {
            cout << "Error ingrese solo numeros.\n";
            cin.clear(); cin.ignore(1000, '\n');
        } else if (modo < 1 || modo > 2) {
            cout << "Opcion invalida.\n";
        } else {
            cin.ignore(1000, '\n');
            break;
        }
    }

    string busc;
    if (modo == 1)
    	cout << "Curso: ";
	else
    	cout << "Docente: ";

    getline(cin, busc);

    int total = 0;
    bool diasConClase[COLUMNAS] = {0};
    for (int j = 0; j < COLUMNAS; j++)
        for (int i = 0; i < FILAS; i++)
            if ((modo == 1 && h[i][j].curso == busc) || (modo == 2 && h[i][j].docente == busc)) {
                total++;
                diasConClase[j] = true;
            }

    cout << "Total de horas encontradas: " << total << "\n";
    cout << "Dias disponibles (sin clases para este filtro): ";
    bool nohay = false;
    for (int j = 0; j < COLUMNAS; j++) {
        if (!diasConClase[j]) {
            nohay = true;
            // mapear numero a nombre
            switch (j+1) {
                case 1: cout << "Lunes "; break;
                case 2: cout << "Martes "; break;
                case 3: cout << "Miercoles "; break;
                case 4: cout << "Jueves "; break;
                case 5: cout << "Viernes "; break;
                case 6: cout << "Sabado "; break;
                case 7: cout << "Domingo "; break;
            }
        }
    }
    if (!nohay) cout << "Ninguno";
    cout << "\n";
}

int carga_horaria_docente(Celda h[FILAS][COLUMNAS], const string &docente, bool mostrarDetalle) {
    int total = 0;
    for (int j = 0; j < COLUMNAS; j++)
        for (int i = 0; i < FILAS; i++)
            if (h[i][j].docente == docente && h[i][j].curso != "Vacio") {
                total++;
                if (mostrarDetalle) {
                    cout << "Dia " << nombreDia(j+1) << " Hora " << (i+7) << ":00 -> " << h[i][j].curso
                         << " | Aula: " << h[i][j].aula << " | Cred: " << h[i][j].creditos << "\n";
                }
            }
    return total;
}

void reporte_conflictos() {
    cout << "\n=== CONFLICTOS ENTRE HORARIOS ===\n\n";

    const int MAXH = 50;
    string horariosNombres[MAXH];
    int total = listarHorariosDesdeTXT(horariosNombres, MAXH);

    if (total == 0) {
        cout << "No hay horarios registrados.\n";
        return;
    }

    // cargar horarios a memoria
    Celda todos[MAXH][FILAS][COLUMNAS];

    for (int i = 0; i < total; i++) {
        if (!cargarHorario(horariosNombres[i], todos[i])) {
            cout << rojo << "Error cargando: " << horariosNombres[i] << reset << "\n";
        }
    }

    bool hay = false;

    for (int A = 0; A < total; A++) {
        for (int B = A + 1; B < total; B++) {

            // recorrer filas/columnas (hora/día)
            for (int f = 0; f < FILAS; f++) {
                for (int c = 0; c < COLUMNAS; c++) {

                    Celda &x = todos[A][f][c];
                    Celda &y = todos[B][f][c];

                    if (x.curso == "Vacio" || y.curso == "Vacio")
                        continue;
					if(x.docente != "" && x.docente == y.docente &&x.aula != "" && x.aula == y.aula && x.curso != "" && x.curso == y.curso){
						continue;
					}
                    // Conflicto docente
                    if (x.docente != "" && x.docente == y.docente) {
                        hay = true;
                        cout << rojo << "Conflicto DOCENTE: " << x.docente << reset << "\n";
                        cout << "  Dia " << nombreDia(c+1)
                             << " Hora " << (f+7) << ":00\n";
                        cout << "    - " << horariosNombres[A] << ": " << x.curso << "\n";
                        cout << "    - " << horariosNombres[B] << ": " << y.curso << "\n\n";
                    }

                    // Conflicto aula
                    if (x.aula != "" && x.aula == y.aula) {
                        hay = true;
                        cout << amarillo << "Conflicto AULA: " << x.aula << reset << "\n";
                        cout << "  Dia " << nombreDia(c+1)
                             << " Hora " << (f+7) << ":00\n";
                        cout << "    - " << horariosNombres[A] << ": " << x.curso << "\n";
                        cout << "    - " << horariosNombres[B] << ": " << y.curso << "\n\n";
                    }
                }
            }
        }
    }

    if (!hay)
        cout << verde << "No se encontraron conflictos entre horarios.\n" << reset;
}


void reporte_busqueda_parcial(Celda h[FILAS][COLUMNAS]) {
    string parcial;
    cout << "Ingrese texto parcial del curso: ";
    getline(cin, parcial);

    // Convertimos lo buscado a minúsculas
    string buscado = parcial;
    for (int i = 0; i < buscado.length(); i++) {
    	buscado[i] = tolower(buscado[i]);
	}


    bool encontrado = false;

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {

            if (h[i][j].curso != "Vacio") {

                // Copiamos y convertimos curso a minúsculas
                string cursoTemp = h[i][j].curso;
                for (int k = 0; k < cursoTemp.length(); k++){
                	cursoTemp[k] = tolower(cursoTemp[k]);
				}
                    

                // Busqueda parcial
                if (cursoTemp.find(buscado) != string::npos) {
                    cout << "Dia " << nombreDia(j+1)
                         << " Hora " << (i + 7) << ":00 -> "
                         << h[i][j].curso
                         << " | Docente: " << h[i][j].docente
                         << " | Aula: " << h[i][j].aula << endl;

                    encontrado = true;
                }
            }
        }
    }

    if (!encontrado)
        cout << "No se encontraron coincidencias.\n";
}




void guardarArchivo(Celda h[FILAS][COLUMNAS]) {

    int op;
    cout << "\n=== OPCIONES DE GUARDADO ===\n";
    cout << "1) Guardar horario actual\n";
    cout << "2) Eliminar un horario\n";
    cout << "0) Cancelar\n";

    while (true) {
        cout << "Opcion: ";
        cin >> op;
        if (!cin.fail() && op >= 0 && op <= 2) break;

        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Opcion invalida.\n";
    }

    cin.ignore();

    if (op == 0) {
        cout << "Cancelado.\n";
        return;
    }

    // --- ELIMINAR HORARIO ---
    if (op == 2) {
        eliminarHorario();
        return;
    }

    // --- GUARDAR HORARIO ---
    string nombre;
    cout << "Nombre del horario a guardar: ";
    getline(cin, nombre);

    // Verificar si ya existe en horarios.txt
    bool existe = false;
    {
        ifstream lista("horarios.txt");
        string linea;
        while (getline(lista, linea))
            if (linea == nombre)
                existe = true;
    }

    if (!existe) {
        ofstream lista("horarios.txt", ios::app);
        lista << nombre << "\n";
    }

    guardarHorario(nombre, h);
}



string leerTextoConComillas(ifstream &arch) {
    string texto;
    char c;

    // 1. Avanzar hasta encontrar una comilla
    while (arch.get(c)) {
        if (c == '"'){
        	break;
		} 
    }

    // 2. Leer hasta la próxima comilla
    getline(arch, texto, '"');

    return texto;
}


void cargarArchivo(Celda h[FILAS][COLUMNAS]) {
    string horario = elegirHorario();
    if (horario == "") return;

    if (!cargarHorario(horario, h)) {
        cout << "No existe ese horario.\n";
        return;
    }

    cout << "Horario '" << horario << "' cargado correctamente.\n";
}

    
    
void reporte_creditos_barras_vertical(Celda h[FILAS][COLUMNAS]) {
    cout << "\n=== GRAFICO VERTICAL DE CREDITOS POR CURSO ===\n\n";

    struct CursoInfo {
        string nombre;
        int creditos;
        string color;
    };

    CursoInfo lista[100];
    int count = 0;

    // EXTRAER CURSOS ÚNICOS
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {

            if (h[i][j].curso == "Vacio") continue;

            bool existe = false;
            for (int k = 0; k < count; k++)
                if (lista[k].nombre == h[i][j].curso)
                    existe = true;

            if (!existe) {
                lista[count].nombre = h[i][j].curso;
                lista[count].creditos = h[i][j].creditos;
                lista[count].color = h[i][j].color;
                count++;
            }
        }
    }

    if (count == 0) {
        cout << "No hay cursos registrados.\n";
        return;
    }

    // BUSCAR MÁXIMO
    int maxCred = 0;
    for (int i = 0; i < count; i++)
        if (lista[i].creditos > maxCred)
            maxCred = lista[i].creditos;

    cout << "CREDITOS MAXIMOS: " << maxCred << "\n\n";

    // ANCHO FIJO DE COLUMNA
    const int COL_WIDTH = 12;

    // DIBUJAR GRAFICO DESDE ARRIBA
    for (int nivel = maxCred; nivel >= 1; nivel--) {

        for (int i = 0; i < count; i++) {

            if (lista[i].creditos >= nivel)
                cout << lista[i].color << string(COL_WIDTH, '#') << reset;
            else
                cout << string(COL_WIDTH, ' ');
        }
        cout << "\n";
    }

    // LINEA
    cout << string(COL_WIDTH * count, '-') << "\n";

    // NOMBRES CENTRADOS
    for (int i = 0; i < count; i++) {
        string nom = lista[i].nombre;
        int pad = (COL_WIDTH - nom.size()) / 2;
        if (pad < 0) pad = 0;

        cout << string(pad, ' ') << nom << string(pad, ' ');
    }

    cout << "\n\n";
}

string elegirHorario() {
    ifstream lista("horarios.txt");
    string horarios[100];
    int count = 0;

    cout << "\n=== SELECCIONAR HORARIO ===\n";

    if (!lista) {
        cout << "(No hay horarios aun)\n";
    } else {
        string linea;
        while (getline(lista, linea)) {
            if (linea != "") {
                cout << count + 1 << ") " << linea << "\n";
                horarios[count++] = linea;
            }
        }
    }

    cout << count + 1 << ") Crear nuevo horario\n";
    cout << "0) Cancelar\n";

    int op;
    while (true) {
        cout << "Opcion: ";
        cin >> op;

        if (!cin.fail() && op >= 0 && op <= count + 1)
            break;

        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Opcion invalida\n";
    }

    cin.ignore();

    if (op == 0)
        return "";

    if (op == count + 1) {
        string nombre;
        cout << "Nombre del nuevo horario: ";
        getline(cin, nombre);

        ofstream add("horarios.txt", ios::app);
        add << nombre << "\n";

        return nombre;
    }

    return horarios[op - 1];
}

string elegirHorario2() {
    ifstream lista("horarios.txt");
    string horarios[100];
    int count = 0;

    cout << "\n=== SELECCIONAR HORARIO ===\n";

    if (!lista) {
        cout << "(No hay horarios aun)\n";
    } else {
        string linea;
        while (getline(lista, linea)) {
            if (linea != "") {
                cout << count + 1 << ") " << linea << "\n";
                horarios[count++] = linea;
            }
        }
    }

    cout << "0) Cancelar\n";

    int op;
    while (true) {
        cout << "Opcion: ";
        cin >> op;

        if (!cin.fail() && op >= 0 && op <= count)
            break;

        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Opcion invalida\n";
    }

    cin.ignore();

    if (op == 0)
        return "";

    return horarios[op - 1];
}

bool cargarHorario(const string &nombre, Celda h[FILAS][COLUMNAS]) {
    string archivo = nombre + ".txt";
    ifstream arch(archivo);

    if (!arch)
        return false;

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {

            h[i][j].curso   = leerTextoConComillas(arch);
            h[i][j].docente = leerTextoConComillas(arch);
            h[i][j].aula    = leerTextoConComillas(arch);

            arch >> h[i][j].creditos;
            arch >> h[i][j].color;
        }
    }

    return true;
}

void guardarHorario(const string &nombre, Celda h[FILAS][COLUMNAS]) {
    string archivo = nombre + ".txt";
    ofstream archOut(archivo);

    if (!archOut) {
        cout << "No se pudo guardar el archivo.\n";
        return;
    }

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            archOut << "\"" << h[i][j].curso   << "\" "
                    << "\"" << h[i][j].docente << "\" "
                    << "\"" << h[i][j].aula    << "\" "
                    << h[i][j].creditos << " "
                    << h[i][j].color;

            if (j < COLUMNAS - 1)
                archOut << " ";
        }
        archOut << "\n";
    }

    cout << "\nHorario guardado como: " << archivo << "\n";
}

void eliminarHorario() {
    ifstream listaIn("horarios.txt");

    if (!listaIn) {
        cout << "No hay horarios registrados.\n";
        return;
    }

    string horarios[100];
    int count = 0;
    string linea;

    while (getline(listaIn, linea)) {
        if (linea != "") {
            horarios[count++] = linea;
        }
    }
    listaIn.close();

    if (count == 0) {
        cout << "No hay horarios registrados.\n";
        return;
    }

    cout << "\n=== ELIMINAR HORARIO ===\n";

    for (int i = 0; i < count; i++)
        cout << i + 1 << ") " << horarios[i] << "\n";

    cout << "0) Cancelar\n";

    int op;
    while (true) {
        cout << "Seleccione: ";
        cin >> op;

        if (!cin.fail() && op >= 0 && op <= count)
            break;

        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Opcion invalida.\n";
    }

    if (op == 0) {
        cout << "Cancelado.\n";
        return;
    }

    string eliminar = horarios[op - 1];

    // eliminar archivo
    string archivo = eliminar + ".txt";
    remove(archivo.c_str());

    // reescribir lista sin el eliminado
    ofstream listaOut("horarios.txt");
    for (int i = 0; i < count; i++) {
        if (horarios[i] != eliminar)
            listaOut << horarios[i] << "\n";
    }
    listaOut.close();

    cout << "Horario '" << eliminar << "' eliminado correctamente.\n";
}


int listarHorariosDesdeTXT(string nombres[], int max) {
    ifstream arch("horarios.txt");
    if (!arch) return 0;

    int count = 0;
    string linea;

    while (getline(arch, linea) && count < max) {
        if (linea != "")
            nombres[count++] = linea;
    }

    return count;
}




