#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "menu.h"
#include "input.h"

int menu()
{
    int opcion;

    printf("**********      MENU DE OPCIONES      **********\n\n");
    printf("1- Cargar Archivo\n");
    printf("2- Imprimir Lista\n");
    printf("3- Asignar Rating\n");
    printf("4- Asignar Genero\n");
    printf("5- Filtrar por Genero\n");
    printf("6- Ordenar Peliculas\n");
    printf("7- Guardar Peliculas\n");
    printf("8- Salir\n");

    utn_getInt("Ingrese opcion: ", "Error, reingrese.", 1, 8, 100, &opcion);

    return opcion;
}
