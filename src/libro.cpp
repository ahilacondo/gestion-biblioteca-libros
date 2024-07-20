#include "../include/registro.h"
#include <iostream>
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

void listarLibros(const vector<Libro> &libros)
{
    try
    {
        for (const auto &libro : libros)
        {
            cout << "Codigo: " << libro.codigo << endl;
            cout << "Nombre: " << libro.nombre << endl;
            cout << "Autor: " << libro.autor << endl;
            cout << "Año de publicacion: " << libro.anoPublicacion << endl;
            cout << "Precio: " << libro.precio << endl;
            cout << "------------------------" << endl;
        }
    }
    catch (const exception &e)
    {
        cerr << "Error al listar los libros: " << e.what() << endl;
    }
}

void guardarLibrosEnFichero(const vector<Libro> &libros)
{
    try
    {
        ofstream archivo("libros.txt");
        if (!archivo.is_open())
        {
            throw runtime_error("No se pudo abrir el fichero para escritura.");
        }
        for (const auto &libro : libros)
        {
            archivo << libro.codigo << "|" << libro.nombre << "|" << libro.autor << "|"
                    << libro.anoPublicacion << "|" << libro.precio << endl;
        }
        archivo.close();
        cout << "Libros guardados exitosamente en el fichero." << endl;
    }
    catch (const exception &e)
    {
        cerr << "Error al guardar los libros en el fichero: " << e.what() << endl;
    }
}

void cargarLibrosDesdeFichero(vector<Libro> &libros)
{
    try
    {
        ifstream archivo("libros.txt");
        if (!archivo.is_open())
        {
            throw runtime_error("No se pudo abrir el fichero para lectura.");
        }
        Libro libro;
        string linea;
        while (getline(archivo, linea))
        {
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
    catch (const exception &e)
    {
        cerr << "Error al cargar los libros desde el fichero: " << e.what() << endl;
    }
}