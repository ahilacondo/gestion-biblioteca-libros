#include "../include/registro.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Implementación de funciones para Pelicula
void agregarPelicula(vector<Pelicula>& peliculas) {
    Pelicula pelicula;
    cout << "Ingrese codigo de la pelicula: ";
    cin >> pelicula.codigo;
    cout << "Ingrese nombre de la pelicula: ";
    cin.ignore();
    getline(cin, pelicula.nombre);
    cout << "Ingrese director de la pelicula: ";
    getline(cin, pelicula.director);
    cout << "Ingrese año de estreno: ";
    cin >> pelicula.anoEstreno;
    cout << "Ingrese genero de la pelicula: ";
    cin.ignore();
    getline(cin, pelicula.genero);
    peliculas.push_back(pelicula);
    cout << "Pelicula agregada exitosamente." << endl;
}

void eliminarPelicula(vector<Pelicula>& peliculas, int codigo) {
    for (auto it = peliculas.begin(); it != peliculas.end(); ++it) {
        if (it->codigo == codigo) {
            peliculas.erase(it);
            cout << "Pelicula eliminada exitosamente." << endl;
            return;
        }
    }
    cout << "Pelicula no encontrada." << endl;
}

void buscarPelicula(const vector<Pelicula>& peliculas, int codigo) {
    for (const auto& pelicula : peliculas) {
        if (pelicula.codigo == codigo) {
            cout << "Codigo: " << pelicula.codigo << endl;
            cout << "Nombre: " << pelicula.nombre << endl;
            cout << "Director: " << pelicula.director << endl;
            cout << "Año de estreno: " << pelicula.anoEstreno << endl;
            cout << "Genero: " << pelicula.genero << endl;
            return;
        }
    }
    cout << "Pelicula no encontrada." << endl;
}

void actualizarPelicula(vector<Pelicula>& peliculas, int codigo) {
    for (auto& pelicula : peliculas) {
        if (pelicula.codigo == codigo) {
            cout << "Ingrese nuevo nombre de la pelicula: ";
            cin.ignore();
            getline(cin, pelicula.nombre);
            cout << "Ingrese nuevo director de la pelicula: ";
            getline(cin, pelicula.director);
            cout << "Ingrese nuevo año de estreno: ";
            cin >> pelicula.anoEstreno;
            cout << "Ingrese nuevo genero de la pelicula: ";
            cin.ignore();
            getline(cin, pelicula.genero);
            cout << "Pelicula actualizada exitosamente." << endl;
            return;
        }
    }
    cout << "Pelicula no encontrada." << endl;
}

void listarPeliculas(const vector<Pelicula>& peliculas) {
    for (const auto& pelicula : peliculas) {
        cout << "Codigo: " << pelicula.codigo << endl;
        cout << "Nombre: " << pelicula.nombre << endl;
        cout << "Director: " << pelicula.director << endl;
        cout << "Año de estreno: " << pelicula.anoEstreno << endl;
        cout << "Genero: " << pelicula.genero << endl;
        cout << "------------------------" << endl;
    }
}

void guardarPeliculasEnFichero(const vector<Pelicula>& peliculas) {
    ofstream archivo("peliculas.txt");
    if (!archivo.is_open()) {
        throw runtime_error("No se pudo abrir el fichero para escritura.");
    }
    for (const auto& pelicula : peliculas) {
        archivo << pelicula.codigo << "|" << pelicula.nombre << "|" << pelicula.director << "|"
                << pelicula.anoEstreno << "|" << pelicula.genero << endl;
    }
    archivo.close();
    cout << "Peliculas guardadas exitosamente en el fichero." << endl;
}

void cargarPeliculasDesdeFichero(vector<Pelicula>& peliculas) {
    ifstream archivo("peliculas.txt");
    if (!archivo.is_open()) {
        throw runtime_error("No se pudo abrir el fichero para lectura.");
    }
    Pelicula pelicula;
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string token;
        getline(ss, token, '|');
        pelicula.codigo = stoi(token);
        getline(ss, token, '|');
        pelicula.nombre = token;
        getline(ss, token, '|');
        pelicula.director = token;
        getline(ss, token, '|');
        pelicula.anoEstreno = stoi(token);
        getline(ss, token, '|');
        pelicula.genero = token;
        peliculas.push_back(pelicula);
    }
    archivo.close();
    cout << "Peliculas cargadas exitosamente desde el fichero." << endl;
}