#include <string>
#include <vector>

using namespace std;

struct Prestamo {
    int codigoRegistro;
    string dniUsuario;
    string fechaPrestamo;
    string fechaDevolucion;
};

void establecerPrestamo(vector<Prestamo>& prestamos);
void establecerDevolucion(vector<Prestamo>& prestamos, int codigoRegistro);
void listarPrestamos(const vector<Prestamo>& prestamos);
