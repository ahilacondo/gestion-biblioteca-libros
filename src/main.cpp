#include "../include/registro.h"
#include "../include/usuario.h"
#include "../include/prestamo.h"
#include <iostream>
#include <vector>
// Caracteres UTF-8
#include <windows.h>

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    vector<Libro> libros;
    vector<Cancion> canciones;
    vector<Pelicula> peliculas;
    vector<Usuario> usuarios;
    vector<Prestamo> prestamos;
    int opcion;
    string dniUsuario;
    int codigoLibro;
    int codigoPrestamo;

    do {
        cout << "============================" << endl;
        cout << "   Gestión de Biblioteca" << endl;
        cout << "============================" << endl;
        cout << "1. Agregar Libro" << endl;
        cout << "2. Eliminar Libro" << endl;
        cout << "3. Buscar Libro" << endl;
        cout << "4. Actualizar Libro" << endl;
        cout << "5. Listar Libros" << endl;
        cout << "6. Guardar Libros en Fichero" << endl;
        cout << "7. Cargar Libros desde Fichero" << endl;
        cout << "8. Agregar Usuario" << endl;
        cout << "9. Eliminar Usuario" << endl;
        cout << "10. Listar Usuarios" << endl;
        cout << "11. Establecer Préstamo" << endl;
        cout << "12. Establecer Devolución" << endl;
        cout << "13. Listar Préstamos" << endl;
        cout << "14. Guardar Préstamos en Fichero" << endl;
        cout << "15. Cargar Préstamos desde Fichero" << endl;
        cout << "16. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                agregarLibro(libros);
                break;
            case 2:
                cout << "Ingrese código del libro a eliminar: ";
                cin >> codigoLibro;
                eliminarLibro(libros, codigoLibro);
                break;
            case 3:
                cout << "Ingrese código del libro a buscar: ";
                cin >> codigoLibro;
                buscarLibro(libros, codigoLibro);
                break;
            case 4:
                cout << "Ingrese código del libro a actualizar: ";
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
                agregarUsuario(usuarios);
                break;
            case 9:
                cout << "Ingrese DNI del usuario a eliminar: ";
                cin >> dniUsuario;
                eliminarUsuario(usuarios, dniUsuario);
                break;
            case 10:
                listarUsuarios(usuarios);
                break;
            case 11:
                establecerPrestamo(prestamos);
                break;
            case 12:
                cout << "Ingrese código del registro a devolver: ";
                cin >> codigoPrestamo;
                establecerDevolucion(prestamos, codigoPrestamo);
                break;
            case 13:
                listarPrestamos(prestamos);
                break;
            case 14:
                guardarPrestamosEnFichero(prestamos);
                break;
            case 15:
                cargarPrestamosDesdeFichero(prestamos);
                break;
            case 16:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción no válida." << endl;
        }
    } while (opcion != 16);

    return 0;
}
