#ifndef PRESTAMO_H
#define PRESTAMO_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

struct Prestamo {
    int codigoRegistro;
    string dniUsuario;
    string fechaPrestamo;
    string fechaDevolucion;

    friend ostream& operator<<(ostream& os, const Prestamo& prestamo) {
        return os << prestamo.codigoRegistro << "|" << prestamo.dniUsuario << "|"
                  << prestamo.fechaPrestamo << "|" << prestamo.fechaDevolucion;
    }

    friend istream& operator>>(istream& is, Prestamo& prestamo) {
        string line;
        if (getline(is, line)) {
            istringstream iss(line);
            string codigo;
            getline(iss, codigo, '|');
            prestamo.codigoRegistro = stoi(codigo);
            getline(iss, prestamo.dniUsuario, '|');
            getline(iss, prestamo.fechaPrestamo, '|');
            getline(iss, prestamo.fechaDevolucion);
        }
        return is;
    }
};

void establecerPrestamo(vector<Prestamo>& prestamos);
void establecerDevolucion(vector<Prestamo>& prestamos, int codigoRegistro);
void listarPrestamos(const vector<Prestamo>& prestamos);
void guardarPrestamosEnFichero(const vector<Prestamo>& prestamos);
void cargarPrestamosDesdeFichero(vector<Prestamo>& prestamos);

#endif
