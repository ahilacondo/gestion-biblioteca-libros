#include <string>
#include <vector>

using namespace std;

struct Usuario {
    string dni;
    string nombre;
    string email;
    string telefono;
};

void agregarUsuario(vector<Usuario>& usuarios);
void eliminarUsuario(vector<Usuario>& usuarios, const string& dni);
void listarUsuarios(const vector<Usuario>& usuarios);