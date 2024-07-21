#include "../include/usuario.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

using namespace std;

void agregarUsuario(vector<Usuario>& usuarios) {
    Usuario usuario;
    cout << "Ingrese DNI: ";
    cin >> usuario.dni;
    cout << "Ingrese nombre: ";
    cin.ignore();
    getline(cin, usuario.nombre);
    cout << "Ingrese email: ";
    getline(cin, usuario.email);
    cout << "Ingrese telefono: ";
    getline(cin, usuario.telefono);
    usuarios.push_back(usuario);
}

void eliminarUsuario(vector<Usuario>& usuarios, const string& dni) {
    auto it = find_if(usuarios.begin(), usuarios.end(), [&dni](const Usuario& usuario) {
        return usuario.dni == dni;
    });
    if (it != usuarios.end()) {
        usuarios.erase(it);
    } else {
        cout << "Usuario no encontrado." << endl;
    }
}

void listarUsuarios(const vector<Usuario>& usuarios) {
    const int anchoDNI = 15;
    const int anchoNombre = 30;
    const int anchoEmail = 30;
    const int anchoTelefono = 15;
    
    cout << left
         << setw(anchoDNI) << "DNI"
         << setw(anchoNombre) << "Nombre"
         << setw(anchoEmail) << "Email"
         << setw(anchoTelefono) << "Telefono" << endl;
    cout << string(anchoDNI + anchoNombre + anchoEmail + anchoTelefono, '-') << endl;

    for (const auto& usuario : usuarios) {
        cout << left
             << setw(anchoDNI) << usuario.dni
             << setw(anchoNombre) << (usuario.nombre.length() > anchoNombre - 3 ? usuario.nombre.substr(0, anchoNombre - 3) + "..." : usuario.nombre)
             << setw(anchoEmail) << (usuario.email.length() > anchoEmail - 3 ? usuario.email.substr(0, anchoEmail - 3) + "..." : usuario.email)
             << setw(anchoTelefono) << usuario.telefono << endl;
    }
}

void guardarUsuariosEnFichero(const vector<Usuario>& usuarios) {
    ofstream archivo("../archive/usuario.txt");
    if (!archivo.is_open()) {
        throw runtime_error("No se pudo abrir el fichero para escritura.");
    }
    for (const auto& usuario : usuarios) {
        archivo << usuario.dni << "|" << usuario.nombre << "|" << usuario.email << "|" << usuario.telefono << endl;
    }
    archivo.close();
    cout << "Usuarios guardados exitosamente en el fichero." << endl;
}

void cargarUsuariosDesdeFichero(vector<Usuario>& usuarios) {
    ifstream archivo("../archive/usuario.txt");
    if (!archivo.is_open()) {
        throw runtime_error("No se pudo abrir el fichero para lectura. Se iniciara con una lista vacia.");
    }
    Usuario usuario;
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string token;
        getline(ss, token, '|');
        usuario.dni = token;
        getline(ss, token, '|');
        usuario.nombre = token;
        getline(ss, token, '|');
        usuario.email = token;
        getline(ss, token, '|');
        usuario.telefono = token;
        usuarios.push_back(usuario);
    }
    archivo.close();
    cout << "Usuarios cargados exitosamente desde el fichero." << endl;
}
