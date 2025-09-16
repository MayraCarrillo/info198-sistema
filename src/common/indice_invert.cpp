#include <cstring>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <unistd.h>
namespace fs = std::filesystem;
using namespace std;


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
    cout<<"PID: " << getpid() << endl;
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
        cout<<"Archivo "<<nombreArch<<" creado exitosamente."<<endl;

    } catch (const fs::filesystem_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
}
