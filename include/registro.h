#include <string>
#include <vector>

using namespace std;

#include <string>
#include <vector>

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

void agregarLibro(vector<Libro>& libros);
void eliminarLibro(vector<Libro>& libros, int codigo);
void buscarLibro(const vector<Libro>& libros, int codigo);
void actualizarLibro(vector<Libro>& libros, int codigo);
void listarLibros(const vector<Libro>& libros);
void guardarLibrosEnFichero(const vector<Libro>& libros);
void cargarLibrosDesdeFichero(vector<Libro>& libros);

void agregarCancion(vector<Cancion>& canciones);
void eliminarCancion(vector<Cancion>& canciones, int codigo);
void buscarCancion(const vector<Cancion>& canciones, int codigo);
void actualizarCancion(vector<Cancion>& canciones, int codigo);
void listarCanciones(const vector<Cancion>& canciones);
void guardarCancionesEnFichero(const vector<Cancion>& canciones);
void cargarCancionesDesdeFichero(vector<Cancion>& canciones);

void agregarPelicula(vector<Pelicula>& peliculas);
void eliminarPelicula(vector<Pelicula>& peliculas, int codigo);
void buscarPelicula(const vector<Pelicula>& peliculas, int codigo);
void actualizarPelicula(vector<Pelicula>& peliculas, int codigo);
void listarPeliculas(const vector<Pelicula>& peliculas);
void guardarPeliculasEnFichero(const vector<Pelicula>& peliculas);
void cargarPeliculasDesdeFichero(vector<Pelicula>& peliculas);
