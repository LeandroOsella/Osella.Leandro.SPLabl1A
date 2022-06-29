#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "parser.h"
#include "movie.h"

int parser_movieFromText(FILE* pFile , LinkedList* pListaPeliculas)
{
	int todoOk = 0;
	char buffer[4][128];
	int titulo = 1;
	eMovies* newMovie = NULL;

	if(pFile != NULL && pListaPeliculas != NULL)
	{
		while(!feof(pFile))
		{
			if((fscanf(pFile, "%[^,], %[^,], %[^,], %[^\n]\n", buffer[0],buffer[1],buffer[2],buffer[3]) == 4) && titulo != 1)
			{
				newMovie = movie_newParametros(buffer[0],buffer[1],buffer[2],buffer[3]);
				if(newMovie != NULL)
				{
					ll_add(pListaPeliculas, newMovie);
					todoOk = 1;
				}
			}
			else
			{
				titulo = 0;
			}
		}
	}
    return todoOk;
}

