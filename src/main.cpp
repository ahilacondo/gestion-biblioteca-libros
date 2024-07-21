#include "../include/registro.h"
#include "../include/usuario.h"
#include "../include/prestamo.h"
#include "../include/database_manager.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
#include <functional>
#include <windows.h>

using namespace std;

void pausar()
{
    cout << "\nPresione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void mostrarBanner()
{
    cout << R"(
    =================================================================================
    ||                                                                             ||
    ||   ######   ######    ######    ######  ######   #####  ###    ###  #####    ||
    ||   ##   ##  ##   ##  ##    ##  ##      ##   ##  ##   ## ####  #### ##   ##   ||
    ||   ######   ######   ##    ##  ## ###  ######   ####### ## #### ## #######   ||
    ||   ##       ##   ##  ##    ##  ##   ## ##   ##  ##   ## ##  ##  ## ##   ##   ||
    ||   ##       ##   ##   ######    #####  ##   ##  ##   ## ##      ## ##   ##   ||
    ||                                                                             ||
    ||                PROYECTO FINAL: PROGRAMACION DE SISTEMAS                     ||
    ||                   SISTEMA DE GESTION DE BIBLIOTECA                          ||
    ||                                                                             ||
    =================================================================================
    )" << endl;

    pausar();
}

void limpiarPantalla()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Declaración anticipada de funciones de menú
void menuRegistro(vector<Libro> &libros, vector<Cancion> &canciones, vector<Pelicula> &peliculas);
void menuUsuario(vector<Usuario> &usuarios);
void menuPrestamo(vector<Prestamo> &prestamos);

// Variables globales
vector<Libro> libros;
vector<Cancion> canciones;
vector<Pelicula> peliculas;
vector<Usuario> usuarios;
vector<Prestamo> prestamos;
DatabaseManager dbManager;

void signalHandler(int signum)
{
    cout << "\nInterrupcion recibida, guardando datos..." << endl;
    dbManager.guardarDatos(libros, canciones, peliculas, usuarios, prestamos);
    cout << "Datos guardados exitosamente. Saliendo del programa." << endl;
    exit(signum);
}

template <typename T>
void manejarSubmenu(const string &titulo, vector<T> &items,
                    const vector<pair<string, function<void(vector<T> &)>>> &opciones)
{
    int opcion;
    do
    {
        cout << "\n============================" << endl;
        cout << "   " << titulo << "   " << endl;
        cout << "============================\n"
             << endl;

        for (size_t i = 0; i < opciones.size(); ++i)
        {
            cout << i + 1 << ". " << opciones[i].first << endl;
        }
        cout << opciones.size() + 1 << ". Volver\n"
             << endl;

        bool valid_input = false;
        while (!valid_input)
        {
            try
            {
                cout << "Seleccione una opcion: ";
                if (!(cin >> opcion))
                {
                    throw invalid_argument("Entrada invalida. Debe ser un numero.");
                }
                if (opcion < 1 || opcion > static_cast<int>(opciones.size()) + 1)
                {
                    throw out_of_range("Opcion no valida.");
                }
                if (typeid(T) == typeid(Libro))
                {
                    ordenarLibros(libros);
                }
                valid_input = true;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        if (opcion > 0 && opcion <= static_cast<int>(opciones.size()))
        {
            opciones[opcion - 1].second(items);
        }
        else if (opcion != static_cast<int>(opciones.size()) + 1)
        {
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != static_cast<int>(opciones.size()) + 1);
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    signal(SIGINT, signalHandler);//errores o ctrl c
    int opcion;

    dbManager.cargarDatos(libros, canciones, peliculas, usuarios, prestamos);
    limpiarPantalla();
    mostrarBanner();

    do
    {
        cout << "\n============================" << endl;
        cout << "   Gestion de Biblioteca    " << endl;
        cout << "============================\n"
             << endl;
        cout << "1. Operaciones de Registro" << endl;
        cout << "2. Operaciones de Usuario" << endl;
        cout << "3. Operaciones de Prestamo" << endl;
        cout << "4. Salir\n"
             << endl;

        bool valid_input = false;
        while (!valid_input)
        {
            try
            {
                cout << "Seleccione una opcion: ";
                if (!(cin >> opcion))
                {
                    throw invalid_argument("Entrada invalida. Debe ser un numero.");
                }
                if (opcion < 1 || opcion > 4)
                {
                    throw out_of_range("Opcion no valida.");
                }
                valid_input = true;
            }
            catch (const exception &e)
            {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        switch (opcion)
        {
        case 1:
            menuRegistro(libros, canciones, peliculas);
            break;
        case 2:
            menuUsuario(usuarios);
            break;
        case 3:
            menuPrestamo(prestamos);
            break;
        case 4:
            cout << "\nGuardando datos y saliendo..." << endl;
            dbManager.guardarDatos(libros, canciones, peliculas, usuarios, prestamos);
            break;
        default:
            cout << "Opcion no valida." << endl;
        }

        if (opcion != 4)
        {
            dbManager.guardarDatos(libros, canciones, peliculas, usuarios, prestamos);
        }
    } while (opcion != 4);

    return 0;
}

void menuRegistro(vector<Libro> &libros, vector<Cancion> &canciones, vector<Pelicula> &peliculas)
{
    vector<pair<string, function<void(vector<Libro> &)>>> opcionesLibros = {
        {"Agregar Libro", agregarLibro},
        {"Eliminar Libro", [](vector<Libro> &l)
         { int codigo; cout << "Ingrese codigo: "; cin >> codigo; eliminarLibro(l, codigo); }},
        {"Buscar Libro", [](vector<Libro> &l)
         { int codigo; cout << "Ingrese codigo: "; cin >> codigo; buscarLibro(l, codigo); }},
        {"Actualizar Libro", [](vector<Libro> &l)
         { int codigo; cout << "Ingrese codigo: "; cin >> codigo; actualizarLibro(l, codigo); }},
        {"Listar Libros", listarLibros},
        {"Guardar Libros en Fichero", guardarLibrosEnFichero},
        {"Cargar Libros desde Fichero", cargarLibrosDesdeFichero}};

    vector<pair<string, function<void(vector<Cancion> &)>>> opcionesCanciones = {
        {"Agregar Cancion", agregarCancion},
        {"Eliminar Cancion", [](vector<Cancion> &c)
         { int codigo; cout << "Ingrese codigo: "; cin >> codigo; eliminarCancion(c, codigo); }},
        {"Buscar Cancion", [](vector<Cancion> &c)
         { int codigo; cout << "Ingrese codigo: "; cin >> codigo; buscarCancion(c, codigo); }},
        {"Actualizar Cancion", [](vector<Cancion> &c)
         { int codigo; cout << "Ingrese codigo: "; cin >> codigo; actualizarCancion(c, codigo); }},
        {"Listar Canciones", listarCanciones},
        {"Guardar Canciones en Fichero", guardarCancionesEnFichero},
        {"Cargar Canciones desde Fichero", cargarCancionesDesdeFichero}};

    vector<pair<string, function<void(vector<Pelicula> &)>>> opcionesPeliculas = {
        {"Agregar Pelicula", agregarPelicula},
        {"Eliminar Pelicula", [](vector<Pelicula> &p)
         { int codigo; cout << "Ingrese codigo: "; cin >> codigo; eliminarPelicula(p, codigo); }},
        {"Buscar Pelicula", [](vector<Pelicula> &p)
         { int codigo; cout << "Ingrese codigo: "; cin >> codigo; buscarPelicula(p, codigo); }},
        {"Actualizar Pelicula", [](vector<Pelicula> &p)
         { int codigo; cout << "Ingrese codigo: "; cin >> codigo; actualizarPelicula(p, codigo); }},
        {"Listar Peliculas", listarPeliculas},
        {"Guardar Peliculas en Fichero", guardarPeliculasEnFichero},
        {"Cargar Peliculas desde Fichero", cargarPeliculasDesdeFichero}};

    int opcion;
    do
    {
        cout << "\n============================" << endl;
        cout << "   Operaciones de Registro  " << endl;
        cout << "============================\n"
             << endl;
        cout << "1. Opciones de Libros" << endl;
        cout << "2. Opciones de Canciones" << endl;
        cout << "3. Opciones de Peliculas" << endl;
        cout << "4. Volver al Menu Principal\n"
             << endl;
        

        bool valid_input = false;
        while (!valid_input)
        {
            try
            {
                cout << "Seleccione una opcion: ";
                if (!(cin >> opcion))
                {
                    throw invalid_argument("Entrada invalida. Debe ser un numero.");
                }
                if (opcion < 1 || opcion > 4)
                {
                    throw out_of_range("Opcion no valida.");
                }
                valid_input = true;
            }
            catch (const exception &e)
            {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        switch (opcion)
        {
        case 1:
            manejarSubmenu("Operaciones de Libros", libros, opcionesLibros);
            break;
        case 2:
            manejarSubmenu("Operaciones de Canciones", canciones, opcionesCanciones);
            break;
        case 3:
            manejarSubmenu("Operaciones de Peliculas", peliculas, opcionesPeliculas);
            break;
        case 4:
            cout << "\nVolviendo al Menu Principal..." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 4);
}

void menuUsuario(vector<Usuario> &usuarios)
{
    vector<pair<string, function<void(vector<Usuario> &)>>> opcionesUsuario = {
        {"Agregar Usuario", agregarUsuario},
        {"Eliminar Usuario", [](vector<Usuario> &u)
         { string dni; cout << "Ingrese DNI: "; cin >> dni; eliminarUsuario(u, dni); }},
        {"Listar Usuarios", listarUsuarios}};

    manejarSubmenu("Operaciones de Usuario", usuarios, opcionesUsuario);
}

void menuPrestamo(vector<Prestamo> &prestamos)
{
    vector<pair<string, function<void(vector<Prestamo> &)>>> opcionesPrestamo = {
        {"Establecer Prestamo", establecerPrestamo},
        {"Establecer Devolucion", [](vector<Prestamo> &p)
         { int codigo; cout << "Ingrese codigo: "; cin >> codigo; establecerDevolucion(p, codigo); }},
        {"Listar Prestamos", listarPrestamos},
        {"Guardar Prestamos en Fichero", guardarPrestamosEnFichero},
        {"Cargar Prestamos desde Fichero", cargarPrestamosDesdeFichero}};

    manejarSubmenu("Operaciones de Prestamo", prestamos, opcionesPrestamo);
}