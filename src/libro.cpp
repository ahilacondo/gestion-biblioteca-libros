#include "../include/registro.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <limits>
#include <thread>

using namespace std;

int cod;
string nom;
string aut;
int anoPub;
float prec;

// Función para fusionar dos sub-vectores ordenados
void merge(vector<Libro> &libros, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Libro> L(n1);
    vector<Libro> R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = libros[left + i];
    for (int i = 0; i < n2; ++i)
        R[i] = libros[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i].codigo <= R[j].codigo)
        {
            libros[k] = L[i];
            ++i;
        }
        else
        {
            libros[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1)
    {
        libros[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2)
    {
        libros[k] = R[j];
        ++j;
        ++k;
    }
}

// Función recursiva para ordenar un vector de libros utilizando MergeSort
void mergeSort(vector<Libro> &libros, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        thread leftThread(mergeSort, ref(libros), left, mid);
        thread rightThread(mergeSort, ref(libros), mid + 1, right);

        leftThread.join();
        rightThread.join();

        merge(libros, left, mid, right);
    }
}

// Función para ordenar el vector de libros utilizando hilos y MergeSort
void ordenarLibros(vector<Libro> &libros)
{
    if (libros.empty())
    {
        cout << "No hay libros para ordenar." << endl;
        return;
    }

    try
    {
        mergeSort(libros, 0, libros.size() - 1);
        cout << "Libros ordenados exitosamente." << endl;
    }
    catch (const std::exception &e)
    {
        cerr << "Error al ordenar los libros: " << e.what() << endl;
    }
}
// Implementación de funciones para Libro
void agregarLibro(vector<Libro> &libros)
{
    try
    {
        Libro libro;
        // Codigo
        while (true)
        {
            cout << "Ingrese codigo del libro: ";
            if (cin >> cod)
            {
                bool existe = false;
                for (const auto &l : libros)
                {
                    if (l.codigo == cod)
                    {
                        existe = true;
                        break;
                    }
                }
                if (existe)
                {
                    cout << "Error: Ya existe un libro con el código '" << to_string(cod) << "'" << endl;
                    continue;
                } else if(cod < 1){
                    cout << "Error: El codigo no puede ser Negativo" << endl;
                    continue;
                }else 
                    break;
            }
            else
            {
                cout << "Error: El código del libro debe ser un número entero." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        // Nombre
        cout << "Ingrese nombre del libro: ";
        cin.ignore();
        // Autor
        getline(cin, nom);
        cout << "Ingrese autor del libro: ";
        getline(cin, aut);
        // Año de publicacion
        while (true)
        {
            cout << "Ingrese año de publicacion: ";
            if (cin >> anoPub)
            {
                break;
            }
            else
            {
                cout << "Error: año de publicación debe ser un número entero." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        // Precio
        while (true)
        {
            cout << "Ingrese precio del libro: ";
            if (cin >> prec)
            {
                if (prec < 0)
                {
                    cout << "Error: El precio del libro no puede ser un número negativo." << endl;
                }
                else
                {
                    break; // Precio válido y no negativo
                }
            }
            else
            {
                cout << "Error: El precio del libro debe ser un número decimal." << endl;
                cin.clear();                                         // Limpia el estado de error de cin
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el resto de la línea
            }
        }
        libro.codigo = cod;
        libro.nombre = nom;
        libro.autor = aut;
        libro.anoPublicacion = anoPub;
        libro.precio = prec;
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
                // Nombre
                cout << "Ingrese nombre del libro: ";
                cin.ignore();
                // Autor
                getline(cin, nom);
                cout << "Ingrese autor del libro: ";
                getline(cin, aut);
                // Año de publicacion
                while (true)
                {
                    cout << "Ingrese año de publicacion: ";
                    if (cin >> anoPub)
                    {
                        break;
                    }
                    else
                    {
                        cout << "Error: año de publicación debe ser un número entero." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                // Precio
                while (true)
                {
                    cout << "Ingrese precio del libro: ";
                    if (cin >> prec)
                    {
                        if (prec < 0)
                        {
                            cout << "Error: El precio del libro no puede ser un número negativo." << endl;
                        }
                        else
                        {
                            break; // Precio válido y no negativo
                        }
                    }
                    else
                    {
                        cout << "Error: El precio del libro debe ser un número decimal." << endl;
                        cin.clear();                                         // Limpia el estado de error de cin
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el resto de la línea
                    }
                }
                libro.nombre = nom;
                libro.autor = nom;
                libro.anoPublicacion = anoPub;
                libro.precio = prec;
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

    for (const auto &libro : libros)
    {
        cout << left
             << setw(anchoCodigo) << libro.codigo
             << setw(anchoNombre) << (libro.nombre.length() > anchoNombre - 3 ? libro.nombre.substr(0, anchoNombre - 3) + "..." : libro.nombre)
             << setw(anchoAutor) << (libro.autor.length() > anchoAutor - 3 ? libro.autor.substr(0, anchoAutor - 3) + "..." : libro.autor)
             << setw(anchoAno) << libro.anoPublicacion
             << setw(anchoPrecio) << fixed << setprecision(2) << libro.precio << endl;
    }
}

void guardarLibrosEnFichero(const vector<Libro> &libros)
{
    ofstream archivo("../archive/libro.txt", ios::out | ios::trunc);
    if (!archivo.is_open())
    {
        throw runtime_error("No se pudo abrir el fichero para escritura.");
    }
    for (const auto &libro : libros)
    {
        archivo << libro.codigo << "|" << libro.nombre << "|" << libro.autor << "|"
                << libro.anoPublicacion << "|" << fixed << setprecision(2) << libro.precio << endl;
    }
    archivo.close();
    cout << "Libros guardados exitosamente en el fichero." << endl;
}

void cargarLibrosDesdeFichero(vector<Libro> &libros)
{
    ifstream archivo("../archive/libro.txt");
    if (!archivo.is_open())
    {
        throw runtime_error("No se pudo abrir el fichero para lectura. Se iniciara con una lista vacia.");
    }
    Libro libro;
    string linea;
    libros.clear(); // Limpiar el vector antes de cargar
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