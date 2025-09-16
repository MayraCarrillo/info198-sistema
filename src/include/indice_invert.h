#ifndef INDICE_H
#define INDICE_H

#include <vector>
#include <tuple>
#include <unordered_map>
#include <iostream>
using namespace std;

void indiceInvertido(string pathCarpeta, string nombreArch);
void leerLibro(const string& rutaArchivo, unordered_map<string, vector<tuple<string,int>>>& palabras);


#endif
