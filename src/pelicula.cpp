#include "../include/registro.h"
#include "../include/utils.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>    
#include <limits>  
using namespace std;

// Función para validar que una cadena contiene solo dígitos en la cabecera utils.h

// Implementación de funciones para Pelicula
void agregarPelicula(vector<Pelicula>& peliculas) {
    try {
        Pelicula pelicula;
        cout << "Ingrese codigo de la pelicula: ";
        if (!(cin >> pelicula.codigo) || !validarNumero(to_string(pelicula.codigo))) {
            throw invalid_argument("Codigo de la pelicula no válido. Debe ser un número.");
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada

        cout << "Ingrese nombre de la pelicula: ";
        getline(cin, pelicula.nombre);
        if (pelicula.nombre.empty()) {
            throw invalid_argument("El nombre de la pelicula no puede estar vacío.");
        }

        cout << "Ingrese director de la pelicula: ";
        getline(cin, pelicula.director);
        if (pelicula.director.empty()) {
            throw invalid_argument("El director de la pelicula no puede estar vacío.");
        }

        cout << "Ingrese año de estreno: ";
        if (!(cin >> pelicula.anoEstreno) || !validarNumero(to_string(pelicula.anoEstreno))) {
            throw invalid_argument("Año de estreno no válido. Debe ser un número.");
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada

        cout << "Ingrese genero de la pelicula: ";
        getline(cin, pelicula.genero);
        if (pelicula.genero.empty()) {
            throw invalid_argument("El genero de la pelicula no puede estar vacío.");
        }

        peliculas.push_back(pelicula);
        cout << "Pelicula agregada exitosamente." << endl;
    } catch (const exception& e) {
        cerr << "Error agregando la pelicula: " << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void eliminarPelicula(vector<Pelicula>& peliculas, int codigo) {
    try {
        for (auto it = peliculas.begin(); it != peliculas.end(); ++it) {
            if (it->codigo == codigo) {
                peliculas.erase(it);
                cout << "Pelicula eliminada exitosamente." << endl;
                return;
            }
        }
        cout << "Pelicula no encontrada." << endl;
    } catch (const exception& e) {
        cerr << "Error eliminando la pelicula: " << e.what() << endl;
    }
}

void buscarPelicula(const vector<Pelicula>& peliculas, int codigo) {
    try {
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
    } catch (const exception& e) {
        cerr << "Error buscando la pelicula: " << e.what() << endl;
    }
}

void actualizarPelicula(vector<Pelicula>& peliculas, int codigo) {
    try {
        for (auto& pelicula : peliculas) {
            if (pelicula.codigo == codigo) {
                cout << "Ingrese nuevo nombre de la pelicula: ";
                cin.ignore();
                getline(cin, pelicula.nombre);
                if (pelicula.nombre.empty()) {
                    throw invalid_argument("El nombre de la pelicula no puede estar vacío.");
                }

                cout << "Ingrese nuevo director de la pelicula: ";
                getline(cin, pelicula.director);
                if (pelicula.director.empty()) {
                    throw invalid_argument("El director de la pelicula no puede estar vacío.");
                }

                cout << "Ingrese nuevo año de estreno: ";
                if (!(cin >> pelicula.anoEstreno) || !validarNumero(to_string(pelicula.anoEstreno))) {
                    throw invalid_argument("Año de estreno no válido. Debe ser un número.");
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada

                cout << "Ingrese nuevo genero de la pelicula: ";
                getline(cin, pelicula.genero);
                if (pelicula.genero.empty()) {
                    throw invalid_argument("El genero de la pelicula no puede estar vacío.");
                }

                cout << "Pelicula actualizada exitosamente." << endl;
                return;
            }
        }
        cout << "Pelicula no encontrada." << endl;
    } catch (const exception& e) {
        cerr << "Error actualizando la pelicula: " << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void listarPeliculas(const vector<Pelicula>& peliculas) {
    try {
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
    } catch (const exception& e) {
        cerr << "Error listando las peliculas: " << e.what() << endl;
    }
}

void guardarPeliculasEnFichero(const vector<Pelicula>& peliculas) {
    try {
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
    } catch (const exception& e) {
        cerr << "Error guardando las peliculas: " << e.what() << endl;
    }
}

void cargarPeliculasDesdeFichero(vector<Pelicula>& peliculas) {
    try {
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
    } catch (const exception& e) {
        cerr << "Error cargando las peliculas: " << e.what() << endl;
    }
}