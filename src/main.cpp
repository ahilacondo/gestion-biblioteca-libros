#include "../include/registro.h"
#include "../include/usuario.h"
#include "../include/prestamo.h"
#include <iostream>
#include <vector>

using namespace std;

// Para las opciones de menu
void menuRegistro(vector<Libro>& libros, vector<Cancion>& canciones, vector<Pelicula>& peliculas);
void menuUsuario(vector<Usuario>& usuarios);
void menuPrestamo(vector<Prestamo>& prestamos);

int main() {
    vector<Libro> libros;
    vector<Cancion> canciones;
    vector<Pelicula> peliculas;
    vector<Usuario> usuarios;
    vector<Prestamo> prestamos;
    int opcion;

    do {
        cout << "============================" << endl;
        cout << "   Gestion de Biblioteca" << endl;
        cout << "============================" << endl;
        cout << "1. Operaciones de Registro" << endl;
        cout << "2. Operaciones de Usuario" << endl;
        cout << "3. Operaciones de Prestamo" << endl;
        cout << "4. Salir" << endl;
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
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
        }
    } while (opcion != 4);

    return 0;
}

// operaciones de registro
void menuRegistro(vector<Libro>& libros, vector<Cancion>& canciones, vector<Pelicula>& peliculas) {
    int opcion;
    do {
        cout << "============================" << endl;
        cout << "   Operaciones de Registro" << endl;
        cout << "============================" << endl;
        cout << "1. Agregar Libro" << endl;
        cout << "2. Eliminar Libro" << endl;
        cout << "3. Buscar Libro" << endl;
        cout << "4. Actualizar Libro" << endl;
        cout << "5. Listar Libros" << endl;
        cout << "6. Guardar Libros en Fichero" << endl;
        cout << "7. Cargar Libros desde Fichero" << endl;
        cout << "8. Agregar Cancion" << endl;
        cout << "9. Eliminar Cancion" << endl;
        cout << "10. Listar Canciones" << endl;
        cout << "11. Agregar Pelicula" << endl;
        cout << "12. Eliminar Pelicula" << endl;
        cout << "13. Listar Peliculas" << endl;
        cout << "14. Volver al Menu Principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                agregarLibro(libros);
                break;
                // completar con las demas opciones
            case 14:
                cout << "Volviendo al Menu Principal..." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
        }
    } while (opcion != 14);
}

// operaciones de usuario
void menuUsuario(vector<Usuario>& usuarios) {
    int opcion;
    do {
        cout << "============================" << endl;
        cout << "   Operaciones de Usuario" << endl;
        cout << "============================" << endl;
        cout << "1. Agregar Usuario" << endl;
        cout << "2. Eliminar Usuario" << endl;
        cout << "3. Listar Usuarios" << endl;
        cout << "4. Volver al Menu Principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                agregarUsuario(usuarios);
                break;
                // completar con las demas opciones
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
    do {
        cout << "============================" << endl;
        cout << "   Operaciones de Prestamo" << endl;
        cout << "============================" << endl;
        cout << "1. Establecer Prestamo" << endl;
        cout << "2. Establecer Devolucion" << endl;
        cout << "3. Listar Prestamos" << endl;
        cout << "4. Volver al Menu Principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                establecerPrestamo(prestamos);
                break;
                // completar con las demas opciones
            case 4:
                cout << "Volviendo al Menu Principal..." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
        }
    } while (opcion != 4);
}