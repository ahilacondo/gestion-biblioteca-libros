#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream> 

using namespace std;

struct Usuario {
    string dni;
    string nombre;
    string email;
    string telefono;

    friend ostream& operator<<(ostream& os, const Usuario& usuario) {
        return os << usuario.dni << "|" << usuario.nombre << "|" << usuario.email << "|" << usuario.telefono;
    }

    friend istream& operator>>(istream& is, Usuario& usuario) {
    string line;
    if (getline(is, line)) {
        istringstream iss(line);
        getline(iss, usuario.dni, '|');
        getline(iss, usuario.nombre, '|');
        getline(iss, usuario.email, '|');
        getline(iss, usuario.telefono);
    }
    return is;
}
};

void agregarUsuario(vector<Usuario>& usuarios);
void eliminarUsuario(vector<Usuario>& usuarios, const string& dni);
void listarUsuarios(const vector<Usuario>& usuarios);

#endif