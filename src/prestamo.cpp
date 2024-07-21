#include "../include/prestamo.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

void establecerPrestamo(vector<Prestamo>& prestamos) {
    Prestamo prestamo;
    cout << "Ingrese codigo del registro: ";
    cin >> prestamo.codigoRegistro;
    cout << "Ingrese DNI del usuario: ";
    cin >> prestamo.dniUsuario;
    cout << "Ingrese fecha de prestamo (DD/MM/AAAA): ";
    cin >> prestamo.fechaPrestamo;
    cout << "Ingrese fecha de devolucion (DD/MM/AAAA): ";
    cin >> prestamo.fechaDevolucion;
    prestamos.push_back(prestamo);
    cout << "Prestamo registrado exitosamente." << endl;
}

void establecerDevolucion(vector<Prestamo>& prestamos, int codigoRegistro) {
    for (auto& prestamo : prestamos) {
        if (prestamo.codigoRegistro == codigoRegistro) {
            cout << "Ingrese nueva fecha de devolucion (DD/MM/AAAA): ";
            cin >> prestamo.fechaDevolucion;
            cout << "Fecha de devolucion actualizada exitosamente." << endl;
            return;
        }
    }
    cout << "Prestamo no encontrado." << endl;
}

void listarPrestamos(const vector<Prestamo>& prestamos) {
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
}

void guardarPrestamosEnFichero(const vector<Prestamo>& prestamos) {
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
}

void cargarPrestamosDesdeFichero(vector<Prestamo>& prestamos) {
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
}
