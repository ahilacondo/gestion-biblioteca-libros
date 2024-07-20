#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct Libro {
    int codigo;
    string nombre;
    string autor;
    int anoPublicacion;
    float precio;

    friend ostream& operator<<(ostream& os, const Libro& libro) {
        return os << libro.codigo << "|" << libro.nombre << "|" << libro.autor << "|"
                  << libro.anoPublicacion << "|" << libro.precio;
    }

    friend istream& operator>>(istream& is, Libro& libro) {
        char delimiter;
        return is >> libro.codigo >> delimiter
                  >> libro.nombre >> delimiter
                  >> libro.autor >> delimiter
                  >> libro.anoPublicacion >> delimiter
                  >> libro.precio;
    }
};

struct Cancion {
    int codigo;
    string nombre;
    string cantante;
    string compositor;
    string genero;

    friend ostream& operator<<(ostream& os, const Cancion& cancion) {
        return os << cancion.codigo << "|" << cancion.nombre << "|" << cancion.cantante << "|"
                  << cancion.compositor << "|" << cancion.genero;
    }

    friend istream& operator>>(istream& is, Cancion& cancion) {
        char delimiter;
        return is >> cancion.codigo >> delimiter
                  >> cancion.nombre >> delimiter
                  >> cancion.cantante >> delimiter
                  >> cancion.compositor >> delimiter
                  >> cancion.genero;
    }
};

struct Pelicula {
    int codigo;
    string nombre;
    string director;
    int anoEstreno;
    string genero;

    friend ostream& operator<<(ostream& os, const Pelicula& pelicula) {
        return os << pelicula.codigo << "|" << pelicula.nombre << "|" << pelicula.director << "|"
                  << pelicula.anoEstreno << "|" << pelicula.genero;
    }

    friend istream& operator>>(istream& is, Pelicula& pelicula) {
        char delimiter;
        return is >> pelicula.codigo >> delimiter
                  >> pelicula.nombre >> delimiter
                  >> pelicula.director >> delimiter
                  >> pelicula.anoEstreno >> delimiter
                  >> pelicula.genero;
    }
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

#endif
