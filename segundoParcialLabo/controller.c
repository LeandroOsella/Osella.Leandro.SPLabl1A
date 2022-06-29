#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "controller.h"
#include "movie.h"
#include "parser.h"

int controller_loadFromText(char* path, LinkedList* pListaPeliculas)
{
	int todoOk = 0;
	FILE* f;
	if(path != NULL && pListaPeliculas != NULL)
	{
		f = fopen(path, "r");
		if(f == NULL)
		{
			printf("No se pudo abrir el archivo\n");
		}
		else
		{
			if(parser_movieFromText(f, pListaPeliculas))
			{
				printf("Se realizo la carga del archivo\n");
				todoOk = 1;
			}
			else
			{
				printf("No se realizo la carga del archivo\n");
			}
		}
		fclose(f);
	}
    return todoOk;
}

int controller_saveAsText(char* path , LinkedList* pListaPeliculas)
{
	int todoOk = 0;
	int tam = 0;
	int id = 0;
	char titulo[128];
	char genero[128];
	float rating = 0;

	eMovies* aux = NULL;
	FILE* f = NULL;

	if(path != NULL && pListaPeliculas != NULL)
	{
		f = fopen(path, "w");
		if(f == NULL)
		{
			printf("No se pudo abrir el archivo\n");
		}
		else
		{
			tam = ll_len(pListaPeliculas);
			fprintf(f,"id,titulo,genero,rating\n");
			for(int i = 0; i < tam; i++)
			{
				aux = (eMovies*)ll_get(pListaPeliculas, i);
				if(aux != NULL)
				{
					if((movie_getRating(aux, &rating) &&
					    movie_getId(aux, &id) &&
					    movie_getTitulo(aux, titulo) &&
					    movie_getGenero(aux, genero)))
					{
						fprintf(f,"%d, %s, %s, %.1f\n", id, titulo, genero, rating);
						todoOk = 1;

					}
				}
			}
			if(todoOk == 1)
			{
				printf("Guardado con exito\n");
			}
		}
		fclose(f);
	}
	return todoOk;
}
