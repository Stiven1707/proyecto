#include<string.h>
#include<stdbool.h>
#define MAXIMA_LONGITUD_CADENA 50
bool existeProductoASubastar (char nombreProducto[], char vectorProductos [] [MAXIMA_LONGITUD_CADENA]){
    bool bandera = false;
    for (int i = 0; i < 5; i++)
    {
        if (strcmp(nombreProducto, vectorProductos[i]) == 0)
        {
            bandera = true;
        }
    }
    return bandera;
}