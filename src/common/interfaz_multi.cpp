#include "../include/util.h"
#include "../include/interfaz_multi.h"
#include <iostream>
#include <limits>
#include <string>
#include <sys/stat.h>
#include <cstdlib>
#include <unistd.h>

using namespace std;

bool archivoExiste(const string& path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

// Función para solicitar opción

int solicitarOpcion() {
    string opcion = "0";

    while (true) {
        cout << "Ingrese opción (debe ser número): ";
        cin >> opcion;

        if (esEntero(opcion)) {
            break;
        }

        cout << "(ERROR) Opción inválida. Intente nuevamente." << endl;
    }

    return stoi(opcion);
}

void menuMatrices(string pathMulti) {
    string pathA, pathB;
    int n = 0;
    string multiM = pathMulti; 

    while (true) {
        cout << endl;
        cout << "---= MULTIPLICACIÓN DE MATRICES =---" << " PID: " << getpid() << endl;
        cout << "1) Ingresar tamaño N de las matrices" << endl;
        cout << "2) Ingresar path de los archivos" << endl;
        cout << "   --Path A actual: " << pathA << endl;
        cout << "   --Path B actual: " << pathB << endl;
        cout << "3) Ejecutar multiplicación" << endl;
        cout << "0) Volver y cancelar multiplicacion" << endl;


        int opcion = solicitarOpcion();

        switch (opcion) {
            case 1:
                cout << "Ingrese N ";
                cin >> n;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;

            case 2:{
            
                cout << "Ingrese path del primer archivo: ";
                cin.ignore();
                getline(cin, pathA);
                if (!archivoExiste(pathA)) {
                    cout << "(ERROR) Archivo A no existe." << endl;
                    pathA.clear();
                    break;
                }

                cout << "Ingrese path del segundo archivo: ";
                getline(cin, pathB);
                if (!archivoExiste(pathB)) {
                    cout << "(ERROR) Archivo B no existe." << endl;
                    pathB.clear();
                    break;
                }

                cout << "Archivos confirmados." << endl;
                break;

            }
            case 3:{
            
                if (n == 0 ) {
                    cout << "(ERROR) Falta ingresar N de las matrices" << endl;
                    break;
                }else if(pathA.empty() || pathB.empty()){
                    cout << "(ERROR) Falta ingresar paths de los archivos." << endl;
                    break;
                }
                // Ejecutar el programa multiplicador
                string comando = multiM + " \"" + pathA + "\" \"" + pathB + "\" \"" + ";" + "\"";
                cout << "Ejecutando: " << comando << endl;
                cout << endl;
                system(comando.c_str());
                break;
            }
            case 0:{
                return;
            }

            default:
                cout << "(ERROR) Opción inválida!" << endl;
                break;
        }
    }
}
