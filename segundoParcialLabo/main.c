#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#include "LinkedList.h"
#include "input.h"
#include "menu.h"
#include "controller.h"
#include "movie.h"

int main()
{
    char salir = 'n';
    int opcion;
    int genero;
    int flagArchivo = 0;
    int flagRating = 0;
    int flagGenero = 0;
    int flagOrdenadas = 0;
    char path[20];

    LinkedList* listaPeliculas = ll_newLinkedList();
    LinkedList* listaPeliculasFiltradas = NULL;

    srand(time(NULL));

    do
    {
        opcion = menu();

        switch(opcion)
        {
        case 1:
            if(flagArchivo == 0)
            {
                printf("Ingrese nombre del archivo (movies.csv): ");
                fflush(stdin);
                gets(path);
                while(strcmp(path, "movies.csv")!=0)
                {
                    printf("Error. Ingrese nombre del archivo correctamente (movies.csv): ");
                    fflush(stdin);
                    gets(path);
                }
                if(controller_loadFromText(path, listaPeliculas))
                {
                    printf("\nArchivo cargado con exito\n\n");
                    flagArchivo = 1;
                }
                else
                {
                    printf("\nError al cargar el archivo\n\n");
                }
            }
            else
            {
                printf("\nYa se realizo la carga del archivo!!!!\n\n");
            }
            break;
        case 2:
            if(flagArchivo == 0)
            {
                printf("\nPara mostrar peliculas debe cargarlas primero!!\n\n");
            }
            else
            {
                mostrarMovies(listaPeliculas);
            }
            break;
        case 3:
            if(flagArchivo == 0)
            {
                printf("\nPara asignar rating debe cargar peliculas primero!!\n\n");
            }
            else
            {
                listaPeliculas = ll_map(listaPeliculas, asignarRating);
                mostrarMovies(listaPeliculas);
                printf("\nRating asignado con exito!!\n\n");
                flagRating = 1;
            }
            break;
        case 4:
            if(flagArchivo == 0)
            {
                printf("\nPara asignar genero debe cargar peliculas primero!!\n\n");
            }
            else
            {
                listaPeliculas = ll_map(listaPeliculas, asignarGenero);
                mostrarMovies(listaPeliculas);
                printf("\nGenero asignado con exito!!\n\n");
                flagGenero = 1;
            }
            break;
        case 5:
            if(flagArchivo == 0 || flagGenero == 0)
            {
                printf("\nPara filtrar por genero primero debe cargar peliculas y asignarle genero!!\n\n");
            }
            else
            {
                utn_getInt("Ingrese genero deseado (1-Drama / 2-Comedia / 3-accion / 4-Terror): ", "Error. reingrese.",1,4,100,&genero);
                switch(genero)
                {
                case 1:
                    listaPeliculasFiltradas = ll_filter(listaPeliculas, filtrarPeliculaDrama);
                    controller_saveAsText("moviesDrama.csv", listaPeliculasFiltradas);
                    break;
                case 2:
                    listaPeliculasFiltradas = ll_filter(listaPeliculas, filtrarPeliculaComedia);
                    controller_saveAsText("moviesComedia.csv", listaPeliculasFiltradas);
                    break;
                case 3:
                    listaPeliculasFiltradas = ll_filter(listaPeliculas, filtrarPeliculaAccion);
                    controller_saveAsText("moviesAccion.csv", listaPeliculasFiltradas);
                    break;
                case 4:
                    listaPeliculasFiltradas = ll_filter(listaPeliculas, filtrarPeliculaTerror);
                    controller_saveAsText("moviesTerror.csv", listaPeliculasFiltradas);
                    break;
                }
            }
            break;
        case 6:
            if(flagArchivo == 0 || flagGenero == 0 || flagRating == 0)
            {
                printf("\nError, para ordenar pelis es OBLIGATORIO cargarlas, asignarle rating y asignarle genero!!\n\n");
            }
            else
            {
                ll_sort(listaPeliculas, movie_CmpGeneroYRating, 0);
                mostrarMovies(listaPeliculas);
                printf("\nPeliculas ordenadas con exito!!\n\n");
                flagOrdenadas = 1;
            }
            break;
        case 7:
            if(flagOrdenadas==0)
            {
                printf("\nError. Para realizar un guardado primero debe ordenar las peliculas!!\n\n");
            }
            else
            {
                controller_saveAsText("moviesGeneroYRating.csv", listaPeliculas);
            }
            break;
        case 8:
            salir = 's';
            printf("\nAdios!!\n\n");
            break;
        }
        system("pause");
        system("cls");
    }
    while(salir != 's');

    ll_deleteLinkedList(listaPeliculas);
    ll_deleteLinkedList(listaPeliculasFiltradas);

    return 0;
}
