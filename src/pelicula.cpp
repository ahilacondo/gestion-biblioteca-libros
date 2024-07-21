#include "../include/registro.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>

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
    const int anchoCodigo = 10;
    const int anchoNombre = 30;
    const int anchoDirector = 25;
    const int anchoAno = 15;
    const int anchoGenero = 15;
    
    cout << left
         << setw(anchoCodigo) << "Codigo"
         << setw(anchoNombre) << "Nombre"
         << setw(anchoDirector) << "Director"
         << setw(anchoAno) << "Año"
         << setw(anchoGenero) << "Genero" << endl;
    cout << string(anchoCodigo + anchoNombre + anchoDirector + anchoAno + anchoGenero, '-') << endl;

    for (const auto& pelicula : peliculas) {
        cout << left
             << setw(anchoCodigo) << pelicula.codigo
             << setw(anchoNombre) << (pelicula.nombre.length() > anchoNombre - 3 ? pelicula.nombre.substr(0, anchoNombre - 3) + "..." : pelicula.nombre)
             << setw(anchoDirector) << (pelicula.director.length() > anchoDirector - 3 ? pelicula.director.substr(0, anchoDirector - 3) + "..." : pelicula.director)
             << setw(anchoAno) << pelicula.anoEstreno
             << setw(anchoGenero) << (pelicula.genero.length() > anchoGenero - 3 ? pelicula.genero.substr(0, anchoGenero - 3) + "..." : pelicula.genero) << endl;
    }
}

void guardarPeliculasEnFichero(const vector<Pelicula>& peliculas) {
    ofstream archivo("../archive/pelicula.txt");
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
    ifstream archivo("../archive/pelicula.txt");
    if (!archivo.is_open()) {
        throw runtime_error("No se pudo abrir el fichero para lectura. Se iniciara con una lista vacia.");
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