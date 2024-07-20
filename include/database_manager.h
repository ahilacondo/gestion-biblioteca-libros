#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "registro.h"
#include "usuario.h"
#include "prestamo.h"

using namespace std;

class DatabaseManager {
public:
    static void cargarDatos(vector<Libro>& libros, vector<Cancion>& canciones, 
                            vector<Pelicula>& peliculas, vector<Usuario>& usuarios, 
                            vector<Prestamo>& prestamos);
    
    static void guardarDatos(const vector<Libro>& libros, const vector<Cancion>& canciones, 
                             const vector<Pelicula>& peliculas, const vector<Usuario>& usuarios, 
                             const vector<Prestamo>& prestamos);

private:
    static const string DATABASE_PATH;
    
    template<typename T>
    static void cargarDesdeArchivo(const string& nombreArchivo, vector<T>& vector);
    
    template<typename T>
    static void guardarEnArchivo(const string& nombreArchivo, const vector<T>& vector);
};

const string DatabaseManager::DATABASE_PATH = "../database/";

void DatabaseManager::cargarDatos(vector<Libro>& libros, vector<Cancion>& canciones, 
                                  vector<Pelicula>& peliculas, vector<Usuario>& usuarios, 
                                  vector<Prestamo>& prestamos) {
    cargarDesdeArchivo(DATABASE_PATH + "libro.txt", libros);
    cargarDesdeArchivo(DATABASE_PATH + "cancion.txt", canciones);
    cargarDesdeArchivo(DATABASE_PATH + "peliculas.txt", peliculas);
    cargarDesdeArchivo(DATABASE_PATH + "usuario.txt", usuarios);
    cargarDesdeArchivo(DATABASE_PATH + "prestamo.txt", prestamos);
}

void DatabaseManager::guardarDatos(const vector<Libro>& libros, const vector<Cancion>& canciones, 
                                   const vector<Pelicula>& peliculas, const vector<Usuario>& usuarios, 
                                   const vector<Prestamo>& prestamos) {
    guardarEnArchivo(DATABASE_PATH + "libro.txt", libros);
    guardarEnArchivo(DATABASE_PATH + "cancion.txt", canciones);
    guardarEnArchivo(DATABASE_PATH + "peliculas.txt", peliculas);
    guardarEnArchivo(DATABASE_PATH + "usuario.txt", usuarios);
    guardarEnArchivo(DATABASE_PATH + "prestamo.txt", prestamos);
}

template<typename T>
void DatabaseManager::cargarDesdeArchivo(const string& nombreArchivo, vector<T>& vector) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    vector.clear();
    string linea;
    while (getline(archivo, linea)) {
        istringstream iss(linea);
        T item;
        if (iss >> item) {
            vector.push_back(item);
        }
    }
    archivo.close();
}

template<typename T>
void DatabaseManager::guardarEnArchivo(const string& nombreArchivo, const vector<T>& vector) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo para escritura: " << nombreArchivo << endl;
        return;
    }

    for (const auto& item : vector) {
        archivo << item << endl;
    }
    archivo.close();
}

#endif