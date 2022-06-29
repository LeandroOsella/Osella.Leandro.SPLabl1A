#include "LinkedList.h"

#ifndef MOVIE_H_INCLUDED
#define MOVIE_H_INCLUDED

typedef struct
{
    int id;
    char titulo[30];
    char genero[20];
    float rating;
}eMovies;

#endif // MOVIES_H_INCLUDED

eMovies* movie_new();
eMovies* movie_newParametros(char* idStr,char* tituloStr,char* generoStr, char* ratingStr);
void movie_delete(eMovies* this);
int mostrarMovie(eMovies* this);
int mostrarMovies(LinkedList* pListaPeliculas);

//***********************************SETTER Y GETTERS****************************************

int movie_setId(eMovies* this,int id);
int movie_getId(eMovies* this,int* id);

int movie_setTitulo(eMovies* this,char* titulo);
int movie_getTitulo(eMovies* this,char* titulo);

int movie_setGenero(eMovies* this ,char* genero);
int movie_getGenero(eMovies* this,char* genero);

int movie_setRating(eMovies* this, float rating);
int movie_getRating(eMovies* this, float* rating);

//************************************COMPARADORES********************************************

int movie_CmpId(void* a, void* b);
int movie_CmpTitulo(void* a, void* b);
int movie_CmpGenero(void* a, void* b);
int movie_CmpRating(void* a, void* b);
int movie_CmpGeneroYRating(void* a, void* b);

//************************************RANDOM********************************************

float randomRating();
void* asignarRating(void* pElement);

int randomGenero();
void* asignarGenero(void* pElement);

//************************************FILTERS********************************************

int filtrarPeliculaDrama(void* a);
int filtrarPeliculaComedia(void* a);
int filtrarPeliculaAccion(void* a);
int filtrarPeliculaTerror(void* a);
