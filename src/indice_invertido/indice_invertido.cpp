#include "../include/util.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <tuple>
#include <filesystem>
#include <unordered_map>
#include <fstream>
#include <unistd.h>
using namespace std;
namespace fs = std::filesystem;


// Lee un libro y agrega sus palabras al mapa global
void leerLibro(const string& rutaArchivo, unordered_map<string, vector<tuple<string,int>>>& palabras) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir: " << rutaArchivo << endl;
        return;
    }
    string palabra;
    unordered_map<string,int> conteoLocal;
    while (archivo >> palabra) {
        string palabraLower ="";
        for (char c : palabra){
              if ( isalpha(c) ){
                  palabraLower += tolower (c);
              }
        }
        if (palabraLower != "")
            conteoLocal[palabraLower]++;
    }
    string nombreDoc = fs::path(rutaArchivo).filename().string();
    for (auto& [pal, cantidad] : conteoLocal) {
        palabras[pal].push_back(make_tuple(nombreDoc, cantidad));
    }
}


// Leer cada palabra, normalizar a minúsculas, eliminar caracteres no alfabéticos y escribir en el archivo
void indiceInvertido(string pathCarpeta, string nombreArch) {
    unordered_map<string, vector<tuple<string,int>>> palabras;
    try {
        for (const auto& entry : fs::directory_iterator(pathCarpeta)) {
            if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                leerLibro (entry.path().string(), palabras);
            }
        }
        ofstream MyFile(nombreArch);
        for (auto& [palabra, docs] : palabras) {
            MyFile << palabra << ";";
            for (size_t i = 0; i < docs.size(); ++i) {
                auto& [doc, num] = docs[i];
                MyFile << "(" << doc << ", " << num << ")";
                if (i != docs.size() - 1) {
                    MyFile << ";";
                }
            }
            MyFile <<"\n";
        }
        MyFile.close();
    } catch (const fs::filesystem_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
}


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
    cout << "---= NOMBRE DEL ARCHIVO A CREAR =---" << "PID: " << getpid() << endl;
    while(true){
        cout<<"------------------------------------------"<<endl;
        cout << "Ingresar nombre (Debe ser .idx): ";
        cin >> nombreArchivo;
        cout << endl;
        if (nombreArchivo.length() < 41) {
            cout << "¿Confirma el nombre: " << nombreArchivo << "?" <<endl;
            cout << "1) Sí"<< endl;
            cout << "2) No , volver" << endl;
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

int main(){
    string librosPath;
    string nombreArchivo;
    while (true) {
        cout << "PID: " << getpid() << endl;
        cout << endl;
        cout << "---= CREA INDICE INVERTIDO =---" << "PID: " << getpid() << endl;;
        cout << "1) Ingresar nombre del archivo a crear" << endl;
        cout << "2) Ingresar path de los libros" << endl;
        cout << "   --Path actual:" <<  librosPath << endl;
        cout << "3) Ejecutar creacipon de index" << endl;
    int opcion = solicitarOpcion();

    switch (opcion) {
        case 1:
            ingresarNombreArchivo(nombreArchivo);
            break;
        case 2:
            cout << endl;
            while(true){
                //Verificar si el PATH existe o no
                cout << "---= INGRESAR PATH A LA CARPETA LIBROS =---" << "PID: " << getpid() << endl;;
                cin >> librosPath;
                cout << "Confirma el path: " << librosPath << "?" <<endl;
                cout << "1) Sí"<< endl;
                cout << "2) No , volver" << endl;
                int opcion2 = solicitarOpcion();
                if (opcion2 == 1) {
                        cout << endl;
                        break;
                }
                else if (opcion2 == 2){
                    cout << "Volver a ingresar path (OBLIGATORIO)" << endl;
                }
                else{
                    cout << "(ERROR) ¡Opción inválida! PATH POR DEFAULT" << endl;
                }
        }
            cout << endl;
            break;
        case 3:
            cout << "Creando index..." << endl;
            indiceInvertido(librosPath, nombreArchivo);
            return 0;
        default:
            cout << "(ERROR) ¡Opción inválida!" << endl;
            break;
        }
    }
}
