#include "../include/registro.h"
#include "../include/usuario.h"
#include "../include/prestamo.h"
#include "../include/database_manager.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

void pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void mostrarBanner() {
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

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Para las opciones de menu
void menuRegistro(vector<Libro>& libros, vector<Cancion>& canciones, vector<Pelicula>& peliculas);
void menuUsuario(vector<Usuario>& usuarios);
void menuPrestamo(vector<Prestamo>& prestamos);

vector<Libro> libros;
vector<Cancion> canciones;
vector<Pelicula> peliculas;
vector<Usuario> usuarios;
vector<Prestamo> prestamos;

void signalHandler(int signum) {
    cout << "\nInterrupcion recibida, guardando datos..." << endl;
    DatabaseManager::guardarDatos(libros, canciones, peliculas, usuarios, prestamos);
    cout << "Datos guardados exitosamente. Saliendo del programa." << endl;
    exit(signum);
}

int main() {
    signal(SIGINT, signalHandler);
    int opcion;
        
    // cargar datos al inicio del programa
    DatabaseManager::cargarDatos(libros, canciones, peliculas, usuarios, prestamos);
    
    limpiarPantalla();
    mostrarBanner();
    
    do {
        
        cout << "\n============================" << endl;
        cout << "   Gestion de Biblioteca    " << endl;
        cout << "============================\n" << endl;
        cout << "1. Operaciones de Registro" << endl;
        cout << "2. Operaciones de Usuario" << endl;
        cout << "3. Operaciones de Prestamo" << endl;
        cout << "4. Salir\n" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
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
                DatabaseManager::guardarDatos(libros, canciones, peliculas, usuarios, prestamos);
                break;
            default:
                cout << "Opcion no valida." << endl;
        }

        // guardar datos despuws de cada opcion
        if (opcion != 4) {
            DatabaseManager::guardarDatos(libros, canciones, peliculas, usuarios, prestamos);
        }
    } while (opcion != 4);

    return 0;
}

// operaciones de registro
void menuRegistro(vector<Libro>& libros, vector<Cancion>& canciones, vector<Pelicula>& peliculas) {
    int opcion;
    int codigoLibro;
    int codigoCancion;
    int codigoPelicula;

    do {
        cout << "\n============================" << endl;
        cout << "   Operaciones de Registro  " << endl;
        cout << "============================\n" << endl;
        cout << "1. Opciones de Libros" << endl;
        cout << "2. Opciones de Canciones" << endl;
        cout << "3. Opciones de Peliculas" << endl;
        cout << "4. Volver al Menu Principal\n" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "\n============================" << endl;
                cout << "   Operaciones de Libros    " << endl;
                cout << "============================\n" << endl;
                cout << "1. Agregar Libro" << endl;
                cout << "2. Eliminar Libro" << endl;
                cout << "3. Buscar Libro" << endl;
                cout << "4. Actualizar Libro" << endl;
                cout << "5. Listar Libros" << endl;
                cout << "6. Guardar Libros en Fichero" << endl;
                cout << "7. Cargar Libros desde Fichero" << endl;
                cout << "8. Volver a Registro\n" << endl;
                cout << "Seleccione una opcion: ";
                cin >> opcion;

                switch (opcion) {
                    case 1:
                        agregarLibro(libros);
                        break;
                    case 2:
                        cout << "\nIngrese codigo del libro a eliminar: ";
                        cin >> codigoLibro;
                        eliminarLibro(libros, codigoLibro);
                        break;
                    case 3:
                        cout << "Ingrese codigo del libro a buscar: ";
                        cin >> codigoLibro;
                        buscarLibro(libros, codigoLibro);
                        break;
                    case 4:
                        cout << "Ingrese codigo del libro a actualizar: ";
                        cin >> codigoLibro;
                        actualizarLibro(libros, codigoLibro);
                        break;
                    case 5:
                        listarLibros(libros);
                        break;
                    case 6:
                        guardarLibrosEnFichero(libros);
                        break;
                    case 7:
                        cargarLibrosDesdeFichero(libros);
                        break;
                    case 8:
                        cout << "\nVolviendo a Registro..." << endl;
                        break;
                    default:
                        cout << "Opcion no valida." << endl;
                }
                break;
            case 2:
                cout << "\n============================" << endl;
                cout << "  Operaciones de Canciones  " << endl;
                cout << "============================\n" << endl;
                cout << "1. Agregar Cancion" << endl;
                cout << "2. Eliminar Cancion" << endl;
                cout << "3. Buscar Cancion" << endl;
                cout << "4. Actualizar Cancion" << endl;
                cout << "5. Listar Canciones" << endl;
                cout << "6. Guardar Canciones en Fichero" << endl;
                cout << "7. Cargar Canciones desde Fichero" << endl;
                cout << "8. Volver a Registro\n" << endl;
                cout << "Seleccione una opcion: ";
                cin >> opcion;

                switch (opcion) {
                    case 1:
                        agregarCancion(canciones);
                        break;
                    case 2:
                        cout << "\nIngrese codigo de la cancion a eliminar: ";
                        cin >> codigoCancion;
                        eliminarCancion(canciones, codigoCancion);
                        break;
                    case 3:
                        cout << "Ingrese codigo de la cancion a buscar: ";
                        cin >> codigoCancion;
                        buscarCancion(canciones, codigoCancion);
                        break;
                    case 4:
                        cout << "Ingrese codigo de la canción a actualizar: ";
                        cin >> codigoCancion;
                        actualizarCancion(canciones, codigoCancion);
                        break;
                    case 5:
                        listarCanciones(canciones);
                        break;
                    case 6:
                        guardarCancionesEnFichero(canciones);
                        break;
                    case 7:
                        cargarCancionesDesdeFichero(canciones);
                        break;
                    case 8:
                        cout << "\nVolviendo a Registro..." << endl;
                        break;
                    default:
                        cout << "Opcion no valida." << endl;
                }
                break;
            case 3:
                cout << "\n============================" << endl;
                cout << "  Operaciones de Peliculas  " << endl;
                cout << "============================\n" << endl;
                cout << "1. Agregar Pelicula" << endl;
                cout << "2. Eliminar Pelicula" << endl;
                cout << "3. Buscar Pelicula" << endl;
                cout << "4. Actualizar Pelicula" << endl;
                cout << "5. Listar Peliculas" << endl;
                cout << "6. Guardar Peliculas en Fichero" << endl;
                cout << "7. Cargar Peliculas desde Fichero" << endl;
                cout << "8. Volver a Registro\n" << endl;
                cout << "Seleccione una opcion: ";
                cin >> opcion;

                switch (opcion) {
                    case 1:
                        agregarPelicula(peliculas);
                        break;
                    case 2:
                        cout << "\nIngrese codigo de la pelicula a eliminar: ";
                        cin >> codigoPelicula;
                        eliminarPelicula(peliculas, codigoPelicula);
                        break;
                    case 3:
                        cout << "Ingrese codigo de la pelicula a buscar: ";
                        cin >> codigoPelicula;
                        buscarPelicula(peliculas, codigoPelicula);
                        break;
                    case 4:
                        cout << "Ingrese codigo de la pelicula a actualizar: ";
                        cin >> codigoPelicula;
                        actualizarPelicula(peliculas, codigoPelicula);
                        break;
                    case 5:
                        listarPeliculas(peliculas);
                        break;
                    case 6:
                        guardarPeliculasEnFichero(peliculas);
                        break;
                    case 7:
                        cargarPeliculasDesdeFichero(peliculas);
                        break;
                    case 8:
                        cout << "\nVolviendo a Registro..." << endl;
                        break;
                    default:
                        cout << "Opcion no valida." << endl;
                }
                break;
            case 4:
                cout << "\nVolviendo al Menu Principal..." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
        }
    } while (opcion != 4);
}

// operaciones de usuario
void menuUsuario(vector<Usuario>& usuarios) {
    int opcion;
    string dniUsuario;

    do {
        cout << "\n============================" << endl;
        cout << "   Operaciones de Usuario   " << endl;
        cout << "============================\n" << endl;
        cout << "1. Agregar Usuario" << endl;
        cout << "2. Eliminar Usuario" << endl;
        cout << "3. Listar Usuarios" << endl;
        cout << "4. Volver al Menu Principal\n" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                agregarUsuario(usuarios);
                break;
            case 2:
                cout << "\nIngrese DNI del usuario a eliminar: ";
                cin >> dniUsuario;
                eliminarUsuario(usuarios, dniUsuario);
                break;
            case 3:
                listarUsuarios(usuarios);
                break;
            case 4:
                cout << "Volviendo al Menu Principal..." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
        }
    } while (opcion != 4);
}

// operaciones de prestamo
void menuPrestamo(vector<Prestamo>& prestamos) {
    int opcion;
    int codigoPrestamo;
    
    do {
        cout << "\n============================" << endl;
        cout << "   Operaciones de Prestamo  " << endl;
        cout << "============================\n" << endl;
        cout << "1. Establecer Prestamo" << endl;
        cout << "2. Establecer Devolucion" << endl;
        cout << "3. Listar Prestamos" << endl;
        cout << "4. Volver al Menu Principal\n" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                establecerPrestamo(prestamos);
                break;
            case 2:
                cout << "\nIngrese codigo del registro a devolver: ";
                cin >> codigoPrestamo;
                establecerDevolucion(prestamos, codigoPrestamo);
                break;
            case 3:
                listarPrestamos(prestamos);
                break;
            case 4:
                guardarPrestamosEnFichero(prestamos);
                break;
            case 5:
                cargarPrestamosDesdeFichero(prestamos);
                break;
            case 6:
                cout << "\nVolviendo al Menu Principal..." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
        }
    } while (opcion != 4);
}