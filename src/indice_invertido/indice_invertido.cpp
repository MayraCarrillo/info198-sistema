#include "../include/util.h"
#include "../include/indice_invert.h"
#include <iostream>
#include <string>
#include <filesystem>
#include <unistd.h>
using namespace std;
namespace fs = std::filesystem;


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

    return std::stoi(opcion);
}

void ingresarNombreArchivo(string &nombreArchivo ) {
    cout << endl;
    cout<<"------------------------------------------";
    cout << endl;
    cout << "---= NOMBRE DEL ARCHIVO A CREAR =---" << "PID: "<< getpid() << endl;
    while(true){
        cout<<"------------------------------------------"<<endl;
        cout << "Ingresar nombre (Debe ser .idx): ";
        cin >> nombreArchivo;
        cout << endl;
        if (nombreArchivo.length() < 41) {
            cout << "¿Confirma el nombre: " << nombreArchivo << "?" <<endl;
            cout << "1) Sí"<< endl;
            cout << "2) No, volver" << endl;
            int opcion2 = solicitarOpcion();
            if (opcion2 == 1) {
                if (fs::path(nombreArchivo).extension() != ".idx") {
                    cerr << "(ERROR) El archivo debe tener extensión .idx" << endl;
                }else{
                    cout << endl;
                    break;
                }
            }
            else if (opcion2 == 2){
                cout << "Volver a ingresar nombre (OBLIGATORIO)" << endl;
            }
            else{
                cout << "(ERROR) ¡Opción inválida! NOMBRE BORRADO" << endl;
            }

        }
        else {
            cout << "(ERROR) Nombre sobre los 40 caracteres. Intente nuevamente." << endl;
        }
    }
}

void ingresarPath (string &path){
    cout << endl;
    cout<<"------------------------------------------"<<endl;
    cout << "---= PATH DE LA CARPETA LIBROS =---" << "PID: " << getpid() << endl;
    while(true){
        cout<<"------------------------------------------"<<endl;
        cout<<"Ingrese path de la carpeta con los libros: ";
        cin >> path;
        cout << "¿Confirma el path: " << path << "?" <<endl;
        cout << "1) Sí"<< endl;
        cout << "2) No, volver" << endl;
        int opcion2 = solicitarOpcion();
        if (opcion2 == 1) {
                cout << endl;
                break;
        }
        else if (opcion2 == 2){
            cout << "Volver a ingresar path (OBLIGATORIO)" << endl;
        }
        else{
            cout << "(ERROR) ¡Opción inválida! Vuelva a ingresar el path" << endl;
        }
    }
}


int main(){
    string librosPath;
    string nombreArchivo;
    while (true) {
        cout << "PID: " << getpid() << endl;
        cout << endl;
        cout << "---= CREA INDICE INVERTIDO =---" << "PID: "<< getpid() << endl;
        cout << "0) Volver" << endl;
        cout << "1) Ingresar nombre del archivo a crear" << endl;
        cout << "2) Ingresar path de los libros" << endl;
        cout << "  --Path actual: " <<  librosPath << endl;
        cout << "3) Ejecutar creacipon de index" << endl;
    int opcion = solicitarOpcion();

    switch (opcion) {
        case 0:
            cout << endl;
            return 0;
        case 1:
            ingresarNombreArchivo(nombreArchivo);
            break;
        case 2:
            ingresarPath(librosPath);
            break;
        case 3:
            cout << "Creando índice invertido..." << endl;
            indiceInvertido(librosPath, nombreArchivo);
            esperarTecla();
        default:
            cout << "(ERROR) ¡Opción inválida!" << endl;
            break;
        }
    }
}
