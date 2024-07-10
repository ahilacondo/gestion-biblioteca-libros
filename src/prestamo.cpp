#include "../include/prestamo.h"
#include <iostream>
#include <fstream>

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
    for (const auto& prestamo : prestamos) {
        cout << "Codigo del registro: " << prestamo.codigoRegistro << endl;
        cout << "DNI del usuario: " << prestamo.dniUsuario << endl;
        cout << "Fecha de prestamo: " << prestamo.fechaPrestamo << endl;
        cout << "Fecha de devolucion: " << prestamo.fechaDevolucion << endl;
        cout << "------------------------" << endl;
    }
}

void guardarPrestamosEnFichero(const vector<Prestamo>& prestamos) {
    ofstream archivo("../data/prestamos.txt");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para guardar." << endl;
        return;
    }
    for (const auto& prestamo : prestamos) {
        archivo << prestamo.codigoRegistro << "|" << prestamo.dniUsuario << "|" 
                << prestamo.fechaPrestamo << "|" << prestamo.fechaDevolucion << endl;
    }
    archivo.close();
}

void cargarPrestamosDesdeFichero(vector<Prestamo>& prestamos) {
    ifstream archivo("../data/prestamos.txt");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para cargar." << endl;
        return;
    }
    Prestamo prestamo;
    string linea;
    while (getline(archivo, linea)) {
        size_t pos = 0;
        string token;

        pos = linea.find("|");
        prestamo.codigoRegistro = stoi(linea.substr(0, pos));
        linea.erase(0, pos + 1);

        pos = linea.find("|");
        prestamo.dniUsuario = linea.substr(0, pos);
        linea.erase(0, pos + 1);

        pos = linea.find("|");
        prestamo.fechaPrestamo = linea.substr(0, pos);
        linea.erase(0, pos + 1);

        prestamo.fechaDevolucion = linea;

        prestamos.push_back(prestamo);
    }
    archivo.close();
}
