#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "funciones.h"
#include "ArrayList.h"

int main()
{
    int salida = 0;
    ArrayList* listaLong = al_newArrayList();
    ArrayList* listaServices = al_newArrayList();
    ArrayList* warnings = al_newArrayList();
    ArrayList* errores = al_newArrayList();

    do
    {
        switch(menuPrincipal())
        {
        case 1:
            cargarStructLong(listaLong);
            cargarStructServices(listaServices);
            break;
        case 2:
            procesarInformacion(listaLong,listaServices,warnings,errores);
            break;
        case 3:
            mostrarEstadisticas(listaLong,listaServices);
            break;
        case 4:
            salida = 1;
            break;
        default:
            printf("Ingrese una opcion entre 1 y 4\n");
            system("pause");
            break;

        }
    }
    while(salida != 1);
    return 0;
}
