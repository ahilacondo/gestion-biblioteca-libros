#include "../include/registro.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

// Implementación de funciones para Libro
void agregarLibro(vector<Libro> &libros)
{
    try
    {
        Libro libro;
        cout << "Ingrese codigo del libro: ";
        cin >> libro.codigo;
        cout << "Ingrese nombre del libro: ";
        cin.ignore();
        getline(cin, libro.nombre);
        cout << "Ingrese autor del libro: ";
        getline(cin, libro.autor);
        cout << "Ingrese año de publicacion: ";
        cin >> libro.anoPublicacion;
        cout << "Ingrese precio del libro: ";
        cin >> libro.precio;
        libros.push_back(libro);
        cout << "Libro agregado exitosamente." << endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error al agregar el libro: " << e.what() << endl;
    }
}

void eliminarLibro(vector<Libro> &libros, int codigo)
{
    try
    {
        for (auto it = libros.begin(); it != libros.end(); ++it)
        {
            if (it->codigo == codigo)
            {
                libros.erase(it);
                cout << "Libro eliminado exitosamente." << endl;
                return;
            }
        }
        cout << "Libro no encontrado." << endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error al eliminar el libro: " << e.what() << endl;
    }
}

void buscarLibro(const vector<Libro> &libros, int codigo)
{
    try
    {
        for (const auto &libro : libros)
        {
            if (libro.codigo == codigo)
            {
                cout << "Codigo: " << libro.codigo << endl;
                cout << "Nombre: " << libro.nombre << endl;
                cout << "Autor: " << libro.autor << endl;
                cout << "Año de publicacion: " << libro.anoPublicacion << endl;
                cout << "Precio: " << libro.precio << endl;
                return;
            }
        }
        cout << "Libro no encontrado." << endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error al buscar el libro" << e.what() << endl;
    }
}

void actualizarLibro(vector<Libro> &libros, int codigo)
{
    try
    {
        for (auto &libro : libros)
        {
            if (libro.codigo == codigo)
            {
                cout << "Ingrese nuevo nombre del libro: ";
                cin.ignore();
                getline(cin, libro.nombre);
                cout << "Ingrese nuevo autor del libro: ";
                getline(cin, libro.autor);
                cout << "Ingrese nuevo año de publicacion: ";
                cin >> libro.anoPublicacion;
                cout << "Ingrese nuevo precio del libro: ";
                cin >> libro.precio;
                cout << "Libro actualizado exitosamente." << endl;
                return;
            }
        }
        cout << "Libro no encontrado." << endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error al actualizar el libro: " << e.what() << endl;
    }
}

void listarLibros(const vector<Libro>& libros) {
    const int anchoCodigo = 10;
    const int anchoNombre = 30;
    const int anchoAutor = 25;
    const int anchoAno = 15;
    const int anchoPrecio = 15;
    
    cout << left
         << setw(anchoCodigo) << "Codigo"
         << setw(anchoNombre) << "Nombre"
         << setw(anchoAutor) << "Autor"
         << setw(anchoAno) << "Año"
         << setw(anchoPrecio) << "Precio" << endl;
    cout << string(anchoCodigo + anchoNombre + anchoAutor + anchoAno + anchoPrecio, '-') << endl;

    for (const auto& libro : libros) {
        cout << left
             << setw(anchoCodigo) << libro.codigo
             << setw(anchoNombre) << (libro.nombre.length() > anchoNombre - 3 ? libro.nombre.substr(0, anchoNombre - 3) + "..." : libro.nombre)
             << setw(anchoAutor) << (libro.autor.length() > anchoAutor - 3 ? libro.autor.substr(0, anchoAutor - 3) + "..." : libro.autor)
             << setw(anchoAno) << libro.anoPublicacion
             << setw(anchoPrecio) << fixed << setprecision(2) << libro.precio << endl;
    }
}

void guardarLibrosEnFichero(const vector<Libro>& libros) {
    ofstream archivo("../archive/libro.txt");
    if (!archivo.is_open()) {
        throw runtime_error("No se pudo abrir el fichero para escritura.");
    }
    for (const auto& libro : libros) {
        archivo << libro.codigo << "|" << libro.nombre << "|" << libro.autor << "|"
                << libro.anoPublicacion << "|" << fixed << setprecision(2) << libro.precio << endl;
    }
    archivo.close();
    cout << "Libros guardados exitosamente en el fichero." << endl;
}

void cargarLibrosDesdeFichero(vector<Libro>& libros) {
    ifstream archivo("../archive/libro.txt");
    if (!archivo.is_open()) {
        throw runtime_error("No se pudo abrir el fichero para lectura. Se iniciara con una lista vacia.");
    }
    Libro libro;
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string token;
        getline(ss, token, '|');
        libro.codigo = stoi(token);
        getline(ss, token, '|');
        libro.nombre = token;
        getline(ss, token, '|');
        libro.autor = token;
        getline(ss, token, '|');
        libro.anoPublicacion = stoi(token);
        getline(ss, token, '|');
        libro.precio = stof(token);
        libros.push_back(libro);
    }
    archivo.close();
    cout << "Libros cargados exitosamente desde el fichero." << endl;
}