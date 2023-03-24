#include<stdbool.h>
#include "funciones.h"
#include <stdio.h>
#include <string.h>

#define MAXIMA_LONGITUD_CADENA 50

int main(){
    char vectorProductos [] [MAXIMA_LONGITUD_CADENA] =
    {"Primer computador MAC", "Codigo fuente de la WWWW", 
    "Cuadro Guernica de Pablo Picasso", "Escultura de Botero"};
    char producto [MAXIMA_LONGITUD_CADENA];
    bool bandera=false;
    int cantidadCaracteres;
    printf("Digite el nombre del producto a buscar: ");
    fgets(producto, 50, stdin);
    strtok(producto, "\n");
    bandera = existeProductoASubastar (producto, vectorProductos);
    if (bandera)
    {
        cantidadCaracteres = strlen(producto);
        printf("El producto %s con una cantidad de caracteres %d fue encontrado \n", producto, cantidadCaracteres);
    }
    else{
        printf("El producto %s no fue encontrado \n", producto);
    }
    return 0;
}