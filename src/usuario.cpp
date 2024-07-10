#include "../include/usuario.h"
#include <iostream>
#include <fstream>
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
    for (const auto& usuario : usuarios) {
        cout << "DNI: " << usuario.dni << endl;
        cout << "Nombre: " << usuario.nombre << endl;
        cout << "Email: " << usuario.email << endl;
        cout << "Telefono: " << usuario.telefono << endl;
        cout << "------------------------" << endl;
    }
}

void guardarUsuariosEnFichero(const vector<Usuario>& usuarios) {
    ofstream archivo("../data/usuarios.txt");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para guardar." << endl;
        return;
    }
    for (const auto& usuario : usuarios) {
        archivo << usuario.dni << "|" << usuario.nombre << "|" << usuario.email << "|" << usuario.telefono << endl;
    }
    archivo.close();
}

void cargarUsuariosDesdeFichero(vector<Usuario>& usuarios) {
    ifstream archivo("../data/usuarios.txt");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para cargar." << endl;
        return;
    }
    Usuario usuario;
    string linea;
    while (getline(archivo, linea)) {
        size_t pos = 0;
        string token;

        pos = linea.find("|");
        usuario.dni = linea.substr(0, pos);
        linea.erase(0, pos + 1);

        pos = linea.find("|");
        usuario.nombre = linea.substr(0, pos);
        linea.erase(0, pos + 1);

        pos = linea.find("|");
        usuario.email = linea.substr(0, pos);
        linea.erase(0, pos + 1);

        usuario.telefono = linea;

        usuarios.push_back(usuario);
    }
    archivo.close();
}
