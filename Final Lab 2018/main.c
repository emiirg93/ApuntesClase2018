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

    ArrayList* numeroNatural = al_newArrayList();
    ArrayList* repetidos = al_newArrayList();
    ArrayList* depurado = al_newArrayList();

    do
    {
        switch(menuPrincipal())
        {
        case 1:
            cargarCsv(numeroNatural);
            mostrarNumeros(numeroNatural);
            break;
        case 2:
            completarCampos(numeroNatural);
            mostrarNumeros(numeroNatural);
            repetidos = numeroNatural->clone(numeroNatural);
            depurado = numeroNatural->clone(numeroNatural);
            break;
        case 3:
            listar(numeroNatural,repetidos,depurado);
            break;
        case 4:
            if(generarArchivo("depurados.csv",depurado)== 0 && generarArchivo("repetidos.csv",repetidos) == 0)
            {
                system("cls");
                printf("Archivos Generados con exito.\n");
                system("pause");
            }
            break;
        case 5:
            salida = 1;
            break;
        default:
            printf("Ingrese una opcion entre 1 y 5\n");
            system("pause");
            break;

        }
    }
    while(salida != 1);
    return 0;
}
