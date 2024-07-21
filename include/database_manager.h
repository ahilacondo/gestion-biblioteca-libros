#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "registro.h"
#include "usuario.h"
#include "prestamo.h"

class DatabaseManager {
public:
    DatabaseManager(const std::string& path = "../database/") : DATABASE_PATH(path) {}

    void cargarDatos(std::vector<Libro>& libros, std::vector<Cancion>& canciones, 
                     std::vector<Pelicula>& peliculas, std::vector<Usuario>& usuarios, 
                     std::vector<Prestamo>& prestamos);
    
    void guardarDatos(const std::vector<Libro>& libros, const std::vector<Cancion>& canciones, 
                      const std::vector<Pelicula>& peliculas, const std::vector<Usuario>& usuarios, 
                      const std::vector<Prestamo>& prestamos);

    // metodo para cargar tipos individuales
    void cargarLibros(std::vector<Libro>& libros) { cargarDesdeArchivo(DATABASE_PATH + "libro.txt", libros); }
    void cargarCanciones(std::vector<Cancion>& canciones) { cargarDesdeArchivo(DATABASE_PATH + "cancion.txt", canciones); }
    void cargarPeliculas(std::vector<Pelicula>& peliculas) { cargarDesdeArchivo(DATABASE_PATH + "pelicula.txt", peliculas); }
    void cargarUsuarios(std::vector<Usuario>& usuarios) { cargarDesdeArchivo(DATABASE_PATH + "usuario.txt", usuarios); }
    void cargarPrestamos(std::vector<Prestamo>& prestamos) { cargarDesdeArchivo(DATABASE_PATH + "prestamo.txt", prestamos); }

private:
    const std::string DATABASE_PATH;
    
    template<typename T>
    void cargarDesdeArchivo(const std::string& nombreArchivo, std::vector<T>& vector);
    
    template<typename T>
    void guardarEnArchivo(const std::string& nombreArchivo, const std::vector<T>& vector);
};

void DatabaseManager::cargarDatos(std::vector<Libro>& libros, std::vector<Cancion>& canciones, 
                                  std::vector<Pelicula>& peliculas, std::vector<Usuario>& usuarios, 
                                  std::vector<Prestamo>& prestamos) {
    cargarLibros(libros);
    cargarCanciones(canciones);
    cargarPeliculas(peliculas);
    cargarUsuarios(usuarios);
    cargarPrestamos(prestamos);
}

void DatabaseManager::guardarDatos(const std::vector<Libro>& libros, const std::vector<Cancion>& canciones, 
                                   const std::vector<Pelicula>& peliculas, const std::vector<Usuario>& usuarios, 
                                   const std::vector<Prestamo>& prestamos) {
    guardarEnArchivo(DATABASE_PATH + "libro.txt", libros);
    guardarEnArchivo(DATABASE_PATH + "cancion.txt", canciones);
    guardarEnArchivo(DATABASE_PATH + "pelicula.txt", peliculas);
    guardarEnArchivo(DATABASE_PATH + "usuario.txt", usuarios);
    guardarEnArchivo(DATABASE_PATH + "prestamo.txt", prestamos);
}

template<typename T>
void DatabaseManager::cargarDesdeArchivo(const std::string& nombreArchivo, std::vector<T>& vector) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + nombreArchivo);
    }

    vector.clear();
    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream iss(linea);
        T item;
        if (iss >> item) {
            vector.push_back(item);
        }
    }
    archivo.close();
}

template<typename T>
void DatabaseManager::guardarEnArchivo(const std::string& nombreArchivo, const std::vector<T>& vector) {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo para escritura: " + nombreArchivo);
    }

    for (const auto& item : vector) {
        archivo << item << std::endl;
    }
    archivo.close();
}

#endif