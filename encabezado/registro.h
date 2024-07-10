#include <string>
#include <vector>

using namespace std;

struct Libro {
    int codigo;
    string nombre;
    string autor;
    int anoPublicacion;
    float precio;
};

struct Cancion {
    int codigo;
    string nombre;
    string cantante;
    string compositor;
    string genero;
};

struct Pelicula {
    int codigo;
    string nombre;
    string director;
    int anoEstreno;
    string genero;
};

void guardarRegistros(const vector<Libro>& libros, const vector<Cancion>& canciones, const vector<Pelicula>& peliculas, const string& nombreArchivo);
void cargarRegistros(vector<Libro>& libros, vector<Cancion>& canciones, vector<Pelicula>& peliculas, const string& nombreArchivo);
void mostrarLibros(const vector<Libro>& libros);
void mostrarCanciones(const vector<Cancion>& canciones);
void mostrarPeliculas(const vector<Pelicula>& peliculas);
