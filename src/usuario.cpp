#include "../include/usuario.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>    
#include <limits> 
#include <regex>

using namespace std;

bool validarDNI(const string& dni) {
    return all_of(dni.begin(), dni.end(), ::isdigit);
}

bool validarEmail(const string& email) {
    const regex pattern(R"((\w+)(\.{1}\w+)*@(\w+)\.(\w+))");
    return regex_match(email, pattern);
}

void agregarUsuario(vector<Usuario>& usuarios) {
    try {
        Usuario usuario;
        cout << "Ingrese DNI: ";
        cin >> usuario.dni;
        if (!validarDNI(usuario.dni)) {
            throw invalid_argument("DNI no válido. Debe contener solo dígitos.");
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada

        cout << "Ingrese nombre: ";
        getline(cin, usuario.nombre);
        if (usuario.nombre.empty()) {
            throw invalid_argument("El nombre no puede estar vacío.");
        }

        cout << "Ingrese email: ";
        getline(cin, usuario.email);
        if (!validarEmail(usuario.email)) {
            throw invalid_argument("Email no válido.");
        }

        cout << "Ingrese telefono: ";
        getline(cin, usuario.telefono);
        if (!validarDNI(usuario.telefono)) {
            throw invalid_argument("Teléfono no válido. Debe contener solo dígitos.");
        }

        usuarios.push_back(usuario);
        cout << "Usuario agregado exitosamente." << endl;
    } catch (const exception& e) {
        cerr << "Error agregando el usuario: " << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void eliminarUsuario(vector<Usuario>& usuarios, const string& dni) {
    try {
        if (!validarDNI(dni)) {
            throw invalid_argument("DNI no válido. Debe contener solo dígitos.");
        }

        auto it = find_if(usuarios.begin(), usuarios.end(), [&dni](const Usuario& usuario) {
            return usuario.dni == dni;
        });
        if (it != usuarios.end()) {
            usuarios.erase(it);
            cout << "Usuario eliminado exitosamente." << endl;
        } else {
            cout << "Usuario no encontrado." << endl;
        }
    } catch (const exception& e) {
        cerr << "Error eliminando el usuario: " << e.what() << endl;
    }
}

void listarUsuarios(const vector<Usuario>& usuarios) {
    try {
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
    } catch (const exception& e) {
        cerr << "Error listando los usuarios: " << e.what() << endl;
    }
}

void guardarUsuariosEnFichero(const vector<Usuario>& usuarios) {
    try {
        ofstream archivo("../archive/usuario.txt");
        if (!archivo.is_open()) {
            throw runtime_error("No se pudo abrir el fichero para escritura.");
        }
        for (const auto& usuario : usuarios) {
            archivo << usuario.dni << "|" << usuario.nombre << "|" << usuario.email << "|" << usuario.telefono << endl;
        }
        archivo.close();
        cout << "Usuarios guardados exitosamente en el fichero." << endl;
    } catch (const exception& e) {
        cerr << "Error guardando los usuarios: " << e.what() << endl;
    }
}

void cargarUsuariosDesdeFichero(vector<Usuario>& usuarios) {
    try {
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
    } catch (const exception& e) {
        cerr << "Error cargando los usuarios: " << e.what() << endl;
    }
}