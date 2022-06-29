#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "movie.h"
#include "LinkedList.h"
#include "input.h"

eMovies* movie_new()
{
    eMovies* newMovie = (eMovies*) malloc(sizeof(eMovies));
    if(newMovie != NULL)
    {
        movie_setId(newMovie, 0);
        movie_setTitulo(newMovie, " ");
        movie_setGenero(newMovie, " ");
        movie_setRating(newMovie, 0);
    }
    return newMovie;
}

eMovies* movie_newParametros(char* idStr,char* tituloStr,char* generoStr, char* ratingStr)
{
    eMovies* newMovie = NULL;
    if(idStr != NULL && tituloStr!= NULL && generoStr != NULL && ratingStr!= NULL)
    {
        newMovie = movie_new();
        if(newMovie != NULL)
        {
            if(!(movie_setRating(newMovie, atoi(ratingStr)) &&
                    movie_setId(newMovie, atoi(idStr)) &&
                    movie_setTitulo(newMovie, tituloStr) &&
                    movie_setGenero(newMovie, generoStr)))
            {
                movie_delete(newMovie);
            }
        }
    }
    return newMovie;
}

void movie_delete(eMovies* this)
{
    free(this);
    this = NULL;
}

int movie_setId(eMovies* this,int id)
{
    int todoOk = 0;

    if(this != NULL)
    {
        this->id = id;
        todoOk = 1;
    }
    return todoOk;
}

int movie_getId(eMovies* this,int* id)
{
    int todoOk = 0;

    if(this != NULL && id != NULL)
    {
        *id = this->id;
        todoOk = 1;
    }
    return todoOk;
}

int movie_setTitulo(eMovies* this,char* titulo)
{
    int todoOk = 0;

    if(this != NULL && titulo != NULL)
    {
        strcpy(this->titulo, titulo);
        todoOk = 1;
    }
    return todoOk;
}

int movie_getTitulo(eMovies* this,char* titulo)
{
    int todoOk = 0;

    if(this != NULL && titulo != NULL)
    {
        strcpy(titulo, this->titulo);
        todoOk = 1;
    }
    return todoOk;
}

int movie_setGenero(eMovies* this,char* genero)
{
    int todoOk = 0;

    if(this != NULL && genero != NULL)
    {
        strcpy(this->genero, genero);
        todoOk = 1;
    }
    return todoOk;
}

int movie_getGenero(eMovies* this,char* genero)
{
    int todoOk = 0;

    if(this != NULL && genero != NULL)
    {
        strcpy(genero, this->genero);
        todoOk = 1;
    }
    return todoOk;
}

int movie_setRating(eMovies* this, float rating)
{
    int todoOk = 0;

    if(this != NULL)
    {
        this->rating = rating;
        todoOk = 1;
    }
    return todoOk;
}

int movie_getRating(eMovies* this,float* rating)
{
    int todoOk = 0;

    if(this != NULL && rating != NULL)
    {
        *rating = this->rating;
        todoOk = 1;
    }
    return todoOk;
}

int mostrarMovie(eMovies* this)
{
    int todoOk = 0;
    int id;
    char titulo[128];
    char genero[128];
    float rating;

    if(this != NULL
            && movie_getId(this, &id)
            && movie_getTitulo(this, titulo)
            && movie_getGenero(this, genero)
            && movie_getRating(this, &rating))
    {
        printf("  %2d    %-30s %-16s    %.1f\n", id, titulo, genero, rating);
        todoOk = 1;
    }
    return todoOk;
}

int mostrarMovies(LinkedList* pListaPeliculas)
{
    int todoOk = 0;
    int tam;
    eMovies* aux = NULL;

    if(pListaPeliculas!=NULL)
    {
        printf("  Id     Titulo \t\t\tGenero   \tRating\n");
        tam = ll_len(pListaPeliculas);
        for(int i = 0; i < tam ; i++)
        {
            aux = (eMovies*) ll_get(pListaPeliculas, i);
            if(aux != NULL)
            {
                mostrarMovie(aux);
                todoOk = 1;
            }
        }
    }

    return todoOk;
}

int movie_CmpId(void* a, void* b)
{
    int retorno = 0;
    eMovies* movie1;
    eMovies* movie2;

    if(a != NULL && b != NULL)
    {
        movie1 = (eMovies*) a;
        movie2 = (eMovies*) b;

        if(movie1->id > movie2->id)
        {
            retorno = 1;
        }
        else
        {
            if(movie1->id < movie2->id)
            {
                retorno = -1;
            }
        }
    }
    return retorno;
}

int movie_CmpTitulo(void* a, void* b)
{
    int retorno = 0;
    eMovies* movie1;
    eMovies* movie2;
    if(a != NULL && b != NULL)
    {
        movie1 = (eMovies*) a;
        movie2 = (eMovies*) b;

        retorno = strcmp(movie1->titulo, movie2->titulo);
    }
    return retorno;
}

int movie_CmpGenero(void* a, void* b)
{
    int retorno = 0;
    eMovies* movie1;
    eMovies* movie2;
    if(a != NULL && b != NULL)
    {
        movie1 = (eMovies*) a;
        movie2 = (eMovies*) b;

        retorno = strcmp(movie1->genero, movie2->genero);
    }
    return retorno;
}


int movie_CmpRating(void* a, void* b)
{
    int retorno = 0;
    eMovies* movie1;
    eMovies* movie2;

    if(a != NULL && b != NULL)
    {
        movie1 = (eMovies*) a;
        movie2 = (eMovies*) b;

        if(movie1->rating > movie2->rating)
        {
            retorno = 1;
        }
        else
        {
            if(movie1->rating < movie2->rating)
            {
                retorno = -1;
            }
        }
    }
    return retorno;
}

float randomRating()
{
    float valor;

    valor = (float) ((rand() % (100 - 10 +1)) + 10)/10; // (float) ((rand() % (max - min +1)) + min)/10;

    return valor;
}

void* asignarRating(void* pElement)
{
    eMovies* auxMovie;
    float valor;

    valor = randomRating();

    if(pElement!=NULL)
    {
        auxMovie = (eMovies*) pElement;
        movie_setRating(auxMovie, valor);
        pElement = auxMovie;
    }
    return pElement;
}

int randomGenero()
{
    int valor;

    //valor = (int) ((rand() % (40 - 10 +1)) + 10)/10;
    valor = (rand() % (3 - 0 +1)) + 1;

    return valor;
}

void* asignarGenero(void* pElement)
{
    eMovies* auxMovie;
    int valor;

    valor = randomGenero();

    if(pElement!=NULL)
    {
        auxMovie = (eMovies*) pElement;
        switch(valor)
        {
        case 1:
            movie_setGenero(auxMovie, "drama");
            pElement = auxMovie;
            break;
        case 2:
            movie_setGenero(auxMovie, "comedia");
            pElement = auxMovie;
            break;
        case 3:
            movie_setGenero(auxMovie, "accion");
            pElement = auxMovie;
            break;
        case 4:
            movie_setGenero(auxMovie, "terror");
            pElement = auxMovie;
            break;
        }
    }
    return pElement;
}

int filtrarPeliculaDrama(void* a)
{
    int rta = 0;

    eMovies* pMovie = NULL;

    if(a!=NULL)
    {
        pMovie = (eMovies*) a;
        if(strcmp(pMovie->genero, "drama")==0)
        {
            rta = 1;
        }
    }
    return rta;
}

int filtrarPeliculaComedia(void* a)
{
    int rta = 0;

    eMovies* pMovie = NULL;

    if(a!=NULL)
    {
        pMovie = (eMovies*) a;
        if(strcmp(pMovie->genero, "comedia")==0)
        {
            rta = 1;
        }
    }
    return rta;
}

int filtrarPeliculaAccion(void* a)
{
    int rta = 0;

    eMovies* pMovie = NULL;

    if(a!=NULL)
    {
        pMovie = (eMovies*) a;
        if(strcmp(pMovie->genero, "accion")==0)
        {
            rta = 1;
        }
    }
    return rta;
}

int filtrarPeliculaTerror(void* a)
{
    int rta = 0;

    eMovies* pMovie = NULL;

    if(a!=NULL)
    {
        pMovie = (eMovies*) a;
        if(strcmp(pMovie->genero, "terror")==0)
        {
            rta = 1;
        }
    }
    return rta;
}

int movie_CmpGeneroYRating(void* a, void* b)
{
    int retorno = 0;
    eMovies* movie1;
    eMovies* movie2;

    if(a!=NULL && b!=NULL)
    {
        movie1 = (eMovies*)a;
        movie2 = (eMovies*)b;

        if(movie_CmpGenero(movie1, movie2)<0)
        {
            retorno = 1;
        }
        else
        {
            if(movie_CmpGenero(movie1, movie2)>0)
            {
                retorno = -1;
            }
            else
            {
                if(movie_CmpGenero(movie1, movie2)==0)
                {
                    if(movie1->rating>movie2->rating)
                    {
                        retorno = 1;
                    }
                    else
                    {
                        if(movie1->rating<movie2->rating)
                        {
                            retorno = -1;
                        }
                    }
                }
            }
        }
    }
    return retorno;
}
