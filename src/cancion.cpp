#include "../include/registro.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

// Implementación de funciones para Cancion
void agregarCancion(vector<Cancion>& canciones) {
    Cancion cancion;
    cout << "Ingrese codigo de la cancion: ";
    cin >> cancion.codigo;
    cout << "Ingrese nombre de la cancion: ";
    cin.ignore();
    getline(cin, cancion.nombre);
    cout << "Ingrese cantante de la cancion: ";
    getline(cin, cancion.cantante);
    cout << "Ingrese compositor de la cancion: ";
    getline(cin, cancion.compositor);
    cout << "Ingrese genero de la cancion: ";
    getline(cin, cancion.genero);
    canciones.push_back(cancion);
    cout << "Cancion agregada exitosamente." << endl;
}

void eliminarCancion(vector<Cancion>& canciones, int codigo) {
    for (auto it = canciones.begin(); it != canciones.end(); ++it) {
        if (it->codigo == codigo) {
            canciones.erase(it);
            cout << "Cancion eliminada exitosamente." << endl;
            return;
        }
    }
    cout << "Cancion no encontrada." << endl;
}

void buscarCancion(const vector<Cancion>& canciones, int codigo) {
    for (const auto& cancion : canciones) {
        if (cancion.codigo == codigo) {
            cout << "Codigo: " << cancion.codigo << endl;
            cout << "Nombre: " << cancion.nombre << endl;
            cout << "Cantante: " << cancion.cantante << endl;
            cout << "Compositor: " << cancion.compositor << endl;
            cout << "Genero: " << cancion.genero << endl;
            return;
        }
    }
    cout << "Cancion no encontrada." << endl;
}

void actualizarCancion(vector<Cancion>& canciones, int codigo) {
    for (auto& cancion : canciones) {
        if (cancion.codigo == codigo) {
            cout << "Ingrese nuevo nombre de la cancion: ";
            cin.ignore();
            getline(cin, cancion.nombre);
            cout << "Ingrese nuevo cantante de la cancion: ";
            getline(cin, cancion.cantante);
            cout << "Ingrese nuevo compositor de la cancion: ";
            getline(cin, cancion.compositor);
            cout << "Ingrese nuevo genero de la cancion: ";
            getline(cin, cancion.genero);
            cout << "Cancion actualizada exitosamente." << endl;
            return;
        }
    }
    cout << "Cancion no encontrada." << endl;
}

void listarCanciones(const vector<Cancion>& canciones) {
    const int anchoCodigo = 10;
    const int anchoNombre = 30;
    const int anchoCantante = 25;
    const int anchoCompositor = 25;
    const int anchoGenero = 15;
    
    cout << left
         << setw(anchoCodigo) << "Codigo"
         << setw(anchoNombre) << "Nombre"
         << setw(anchoCantante) << "Cantante"
         << setw(anchoCompositor) << "Compositor"
         << setw(anchoGenero) << "Genero" << endl;
    cout << string(anchoCodigo + anchoNombre + anchoCantante + anchoCompositor + anchoGenero, '-') << endl;

    for (const auto& cancion : canciones) {
        cout << left
             << setw(anchoCodigo) << cancion.codigo
             << setw(anchoNombre) << (cancion.nombre.length() > anchoNombre - 3 ? cancion.nombre.substr(0, anchoNombre - 3) + "..." : cancion.nombre)
             << setw(anchoCantante) << (cancion.cantante.length() > anchoCantante - 3 ? cancion.cantante.substr(0, anchoCantante - 3) + "..." : cancion.cantante)
             << setw(anchoCompositor) << (cancion.compositor.length() > anchoCompositor - 3 ? cancion.compositor.substr(0, anchoCompositor - 3) + "..." : cancion.compositor)
             << setw(anchoGenero) << (cancion.genero.length() > anchoGenero - 3 ? cancion.genero.substr(0, anchoGenero - 3) + "..." : cancion.genero) << endl;
    }
}

void guardarCancionesEnFichero(const vector<Cancion>& canciones) {
    ofstream archivo("../archive/cancion.txt");
    if (!archivo.is_open()) {
        throw runtime_error("No se pudo abrir el fichero para escritura.");
    }
    for (const auto& cancion : canciones) {
        archivo << cancion.codigo << "|" << cancion.nombre << "|" << cancion.cantante << "|"
                << cancion.compositor << "|" << cancion.genero << endl;
    }
    archivo.close();
    cout << "Canciones guardadas exitosamente en el fichero." << endl;
}

void cargarCancionesDesdeFichero(vector<Cancion>& canciones) {
    ifstream archivo("../archive/cancion.txt");
    if (!archivo.is_open()) {
        throw runtime_error("No se pudo abrir el fichero para lectura. Se iniciara con una lista vacia.");
    }
    Cancion cancion;
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string token;
        getline(ss, token, '|');
        cancion.codigo = stoi(token);
        getline(ss, token, '|');
        cancion.nombre = token;
        getline(ss, token, '|');
        cancion.cantante = token;
        getline(ss, token, '|');
        cancion.compositor = token;
        getline(ss, token, '|');
        cancion.genero = token;
        canciones.push_back(cancion);
    }
    archivo.close();
    cout << "Canciones cargadas exitosamente desde el fichero." << endl;
}