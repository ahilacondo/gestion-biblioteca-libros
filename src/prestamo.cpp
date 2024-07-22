#include "../include/prestamo.h"
#include "../include/utils.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <limits> 
#include <regex>

using namespace std;

// Función para validar fecha en formato DD/MM/AAAA
bool validarFecha(const string& fecha) {
    regex formatoFecha("\\d{2}/\\d{2}/\\d{4}");
    return regex_match(fecha, formatoFecha);
}

// Función para validar que una cadena contiene solo dígitos en cabecera utils.h

void establecerPrestamo(vector<Prestamo>& prestamos) {
    try {
        Prestamo prestamo;
        cout << "Ingrese codigo del registro: ";
        if (!(cin >> prestamo.codigoRegistro)) {
            throw invalid_argument("Codigo de registro no válido.");
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada

        cout << "Ingrese DNI del usuario: ";
        cin >> prestamo.dniUsuario;
        if (!validarNumero(prestamo.dniUsuario)) {
            throw invalid_argument("DNI no válido. Debe contener solo números.");
        }

        cout << "Ingrese fecha de prestamo (DD/MM/AAAA): ";
        cin >> prestamo.fechaPrestamo;
        if (!validarFecha(prestamo.fechaPrestamo)) {
            throw invalid_argument("Fecha de prestamo no válida. Debe estar en formato DD/MM/AAAA.");
        }

        cout << "Ingrese fecha de devolucion (DD/MM/AAAA): ";
        cin >> prestamo.fechaDevolucion;
        if (!validarFecha(prestamo.fechaDevolucion)) {
            throw invalid_argument("Fecha de devolucion no válida. Debe estar en formato DD/MM/AAAA.");
        }

        prestamos.push_back(prestamo);
        cout << "Prestamo registrado exitosamente." << endl;
    } catch (const exception& e) {
        cerr << "Error registrando el prestamo: " << e.what() << endl;
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
    }
}

void establecerDevolucion(vector<Prestamo>& prestamos, int codigoRegistro) {
    try {
        for (auto& prestamo : prestamos) {
            if (prestamo.codigoRegistro == codigoRegistro) {
                cout << "Ingrese nueva fecha de devolucion (DD/MM/AAAA): ";
                cin >> prestamo.fechaDevolucion;
                if (!validarFecha(prestamo.fechaDevolucion)) {
                    throw invalid_argument("Fecha de devolucion no válida. Debe estar en formato DD/MM/AAAA.");
                }
                cout << "Fecha de devolucion actualizada exitosamente." << endl;
                return;
            }
        }
        cout << "Prestamo no encontrado." << endl;
    } catch (const exception& e) {
        cerr << "Error registrando la devolucion: " << e.what() << endl;
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
    }
}

void listarPrestamos(const vector<Prestamo>& prestamos) {
    try {
        const int anchoCodigo = 15;
        const int anchoDNI = 15;
        const int anchoFechaPrestamo = 20;
        const int anchoFechaDevolucion = 20;
        
        cout << left
             << setw(anchoCodigo) << "Codigo"
             << setw(anchoDNI) << "DNI Usuario"
             << setw(anchoFechaPrestamo) << "Fecha Prestamo"
             << setw(anchoFechaDevolucion) << "Fecha Devolucion" << endl;
        cout << string(anchoCodigo + anchoDNI + anchoFechaPrestamo + anchoFechaDevolucion, '-') << endl;

        for (const auto& prestamo : prestamos) {
            cout << left
                 << setw(anchoCodigo) << prestamo.codigoRegistro
                 << setw(anchoDNI) << prestamo.dniUsuario
                 << setw(anchoFechaPrestamo) << prestamo.fechaPrestamo
                 << setw(anchoFechaDevolucion) << prestamo.fechaDevolucion << endl;
        }
    } catch (const exception& e) {
        cerr << "Error listando los prestamos: " << e.what() << endl;
    }
}

void guardarPrestamosEnFichero(const vector<Prestamo>& prestamos) {
    try {
        ofstream archivo("../archive/prestamo.txt");
        if (!archivo.is_open()) {
            throw runtime_error("No se pudo abrir el fichero para escritura.");
        }
        for (const auto& prestamo : prestamos) {
            archivo << prestamo.codigoRegistro << "|" << prestamo.dniUsuario << "|" 
                    << prestamo.fechaPrestamo << "|" << prestamo.fechaDevolucion << endl;
        }
        archivo.close();
        cout << "Prestamos guardados exitosamente en el fichero." << endl;
    } catch (const exception& e) {
        cerr << "Error guardando los prestamos: " << e.what() << endl;
    }
}

void cargarPrestamosDesdeFichero(vector<Prestamo>& prestamos) {
    try {
        ifstream archivo("../archive/prestamo.txt");
        if (!archivo.is_open()) {
            throw runtime_error("No se pudo abrir el fichero para lectura. Se iniciara con una lista vacia.");
        }
        Prestamo prestamo;
        string linea;
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string token;
            getline(ss, token, '|');
            prestamo.codigoRegistro = stoi(token);
            getline(ss, token, '|');
            prestamo.dniUsuario = token;
            getline(ss, token, '|');
            prestamo.fechaPrestamo = token;
            getline(ss, token, '|');
            prestamo.fechaDevolucion = token;
            prestamos.push_back(prestamo);
        }
        archivo.close();
        cout << "Prestamos cargados exitosamente desde el fichero." << endl;
    } catch (const exception& e) {
        cerr << "Error cargando los prestamos: " << e.what() << endl;
    }
}