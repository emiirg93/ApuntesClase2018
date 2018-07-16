#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "funciones.h"
#include "ArrayList.h"

eNumero* constructorNumero()
{
    eNumero* aux;

    aux = (eNumero*)malloc(sizeof(eNumero));

    if(aux != NULL)
    {
        aux->numero = 0;
        strcpy(aux->nombre,"");
        aux->par = 0;
        aux->impar = 0;
        aux->primo = 0;
    }

    return aux;
}

FILE* leerArchivo(char* nombre)
{
    FILE* archivo;

    archivo = fopen(nombre,"r");

    if(archivo == NULL)
    {
        printf("El archivo no existe en el directorio del programa.\n");
        system("pause");
    }

    return archivo;
}

void cargarCsv (ArrayList* numero)
{
    FILE* archivo;
    eNumero* aux;
    int cantidad,resNombre,resNumero,resPar,resImpar,resPrimo;
    char auxNombre[50];
    char auxNumero[50];
    char auxPar[50];
    char auxImpar[50];
    char auxPrimo[50];

    archivo = leerArchivo("datos.csv");

    if (numero != NULL && archivo != NULL)
    {
        while(!feof(archivo))
        {
            cantidad = fscanf(archivo,"%[^,],%[^,],%[^,],%[^,],%[^\n]\n",auxNumero,auxNombre,auxPar,auxImpar,auxPrimo);

            aux = constructorNumero();

            if(cantidad == 5 && aux != NULL)
            {

                resNombre = setNombre(aux,auxNombre);
                resNumero = setNumero(aux,auxNumero);
                resPar = setPar(aux,auxPar);
                resImpar= setImpar(aux,auxImpar);
                resPrimo = setPrimo(aux,auxPrimo);

                if(resNombre == 0 && resNumero == 0 && resPar == 0 && resImpar == 0 && resPrimo == 0)
                {
                    numero->add(numero,aux);
                }
                else
                {
                    printf("No se cargaron el en arraylist.\n");
                    system("pause");
                    break;
                }

            }
            else
            {
                printf("error al leer el archivo.\n");
                system("pause");
                break;
            }
        }

        printf("Archivo cargado con exito!\n");
        system("pause");
    }

    feof(archivo);
}

void funcionParImparPrimo (eNumero* num)
{
    int numero,i,a=0;

    numero = getNumero(num);

    if (numero%2 == 0)
    {
        num->par = 1;
        num->impar = 0;
    }
    else
    {
        num->par = 0;
        num-> impar = 1;
    }

    for(i=1; i<=numero; i++)
    {
        if(numero%i==0)
        {
            a++;
        }
    }

    if(a == 2)
    {
        num->primo = 1;
    }
    else
    {
        num->primo = 0;
    }

}

void completarCampos(ArrayList* num)
{
    int i;
    eNumero* aux;

    if(num != NULL)
    {
        for(i=0; i<num->len(num); i++)
        {
            aux = (eNumero*)num->get(num,i);

            if(aux!= NULL)
            {
                funcionParImparPrimo(aux);

                num->set(num,i,aux);
            }
        }
    }
}

int compararNumeros(void* numeroA,void* numeroB)
{
    eNumero* numA;
    eNumero* numB;

    int respuesta;

    if(numA != NULL && numB != NULL)
    {
        numA = (eNumero*)numeroA;
        numB = (eNumero*)numeroB;

        if(numA->numero > numB->numero)
        {
            respuesta = 1;
        }
        else if(numA->numero < numB->numero)
        {
            respuesta = -1;
        }
        else
        {
            respuesta = 0;
        }

        return respuesta;
    }

    return 0;
}

void ordenarDescendente (ArrayList* num)
{
    if(num != NULL)
    {
        num->sort(num,compararNumeros,0);
    }
}

void ordenarAscendente (ArrayList* num)
{
    if(num != NULL)
    {
        num->sort(num,compararNumeros,1);
    }
}

ArrayList* depurarLista (ArrayList* repetidos)
{
    int i,j,flag;
    eNumero* numeroA;
    eNumero* numeroB;

    if(repetidos != NULL)
    {

        for(i=0; i<repetidos->len(repetidos); i++)
        {
            numeroA = (eNumero*)repetidos->get(repetidos,i);

            for(j=i+1; j<repetidos->len(repetidos); j++)
            {
                numeroB = (eNumero*)repetidos->get(repetidos,j);

                if(numeroA->numero == numeroB->numero && strcmpi(numeroA->nombre,numeroB->nombre)== 0)
                {
                    repetidos->remove(repetidos,j);
                }
            }
        }

        /** hago doble depuramiento porque me seguia mostrando algunos repetidos **/

        for(i=0; i<repetidos->len(repetidos); i++)
        {
            numeroA = (eNumero*)repetidos->get(repetidos,i);

            for(j=i+1; j<repetidos->len(repetidos); j++)
            {
                numeroB = (eNumero*)repetidos->get(repetidos,j);

                if(numeroA->numero == numeroB->numero && strcmpi(numeroA->nombre,numeroB->nombre)== 0)
                {
                    repetidos->remove(repetidos,j);
                }
            }
        }


        system("cls");
        printf("Lista depurada.\n");
        system("pause");

    }

    return repetidos;

}
void listar(ArrayList* num,ArrayList* repetidos,ArrayList* depurado)
{
    int i,salir = 0;

    do
    {
        switch (menuListar())
        {
        case 1:
            ordenarDescendente(repetidos);
            mostrarNumeros(repetidos);
            break;
        case 2:
            depurado = depurarLista(depurado);
            ordenarAscendente(depurado);
            mostrarNumeros(depurado);
            break;
        case 3:
            salir =1;
            break;
        default:
            printf("Elija una opcion entre 1 y 3.\n");
            system("pause");
        }
    }while(salir != 1);
}

int generarArchivo(char* nombre,ArrayList* lista)
{
    FILE* archivo;
    eNumero* aux;
    int retorno = -1,i,cantidad;

    if(nombre != NULL)
    {
        archivo = fopen(nombre,"w");

        if(archivo != NULL && lista != NULL)
        {
            printf("entre aca");
            getch();
            for(i=0;i<lista->len(lista);i++)
            {
                aux = (eNumero*)lista->get(lista,i);

                fprintf(archivo,"%d,%s,%d,%d,%d\n",getNumero(aux),getNombre(aux),getPar(aux),getImpar(aux),getPrimo(aux));
            }

            retorno = 0;
        }
    }

    fclose(archivo);

    return retorno;

}

void mostrarNumeros (ArrayList* numeros)
{
    int i,flag = 0;
    eNumero* aux;

    if(numeros != NULL && numeros->isEmpty(numeros) == 0)
    {
        system("cls");

        for (i=0; i<numeros->len(numeros); i++)
        {
            aux = (eNumero*)numeros->get(numeros,i);
            if(flag == 0)
            {
                printf("i     Numero    Nombre\t            Par\t      Impar     Primo\n");
                flag = 1;
            }

            printf("%-6d%-10d%-20s%-10d%-10d%d\n",i+1,getNumero(aux),getNombre(aux),getPar(aux),getImpar(aux),getPrimo(aux));
        }

        system("pause");
    }
    else if(numeros->isEmpty(numeros)==1)
    {
        printf("No hay numeros ingresados.\n");
        system("pause");
    }
}

/***************************************VALIDACIONES/MENUS*************************************************/

int menuPrincipal ()
{
    char opcion[10];
    int datoInt;

    system("cls");

    printf("-------Bienvenidos-------\n\n");
    printf("1- Alta.\n");
    printf("2- Completar.\n");
    printf("3- Listar.\n");
    printf("4- Generar.\n");
    printf("5- Salir.\n\n");

    printf("Ingrese Respuesta: ");

    scanf("%s",opcion);

    while (validarLetra(opcion)== 1)
    {
        printf("Usted no puede ingresar un caracter!\nIngrese un numero ente 1 y 5 :");
        scanf("%s",opcion);
    }

    datoInt = atoi(opcion);

    return datoInt;
}

int menuListar ()
{
    char opcion[10];
    int datoInt;

    system("cls");

    printf("-------Bienvenidos-------\n\n");
    printf("1- Array ordenado con los numeros repetidos (DESCENDENTE).\n");
    printf("2- Array ordenado depurado (ASCEDENTE).\n");
    printf("5- Salir.\n\n");

    printf("Ingrese Respuesta: ");

    scanf("%s",opcion);

    while (validarLetra(opcion)== 1)
    {
        printf("Usted no puede ingresar un caracter!\nIngrese un numero ente 1 y 3 :");
        scanf("%s",opcion);
    }

    datoInt = atoi(opcion);

    return datoInt;
}

int validarLetra (char opcion[])
{
    int flag = 0,cant,i;

    cant = strlen(opcion);

    for(i=0; i<cant; i++)
    {
        if(!isdigit(opcion[i]))
        {
            flag = 1;
            break;
        }
    }

    return flag;
}

int setNombre (eNumero* numero,char* nombre)
{
    int aux = -1;

    if(numero != NULL && nombre != NULL)
    {
        if(strlen(nombre)>0 && strlen(nombre)<50)
        {
            strcpy(numero->nombre,nombre);
            aux = 0;
        }
    }

    return aux;
}

int setNumero(eNumero* numero,char* num)
{
    int aux = -1,auxNum;

    if(numero != NULL && num != NULL)
    {

        auxNum = atoi(num);

        if(auxNum>=0)
        {
            numero->numero = auxNum;
            aux = 0;
        }
    }

    return aux;
}

int setPar(eNumero* numero,char* num)
{
    int aux = -1,auxNum;

    if(numero != NULL && num != NULL)
    {

        auxNum = atoi(num);

        if(auxNum == 0 || auxNum == 1)
        {
            numero->par = auxNum;
            aux = 0;
        }
    }

    return aux;
}

int setImpar(eNumero* numero,char* num)
{
    int aux = -1,auxNum;

    if(numero != NULL && num != NULL)
    {

        auxNum = atoi(num);

        if(auxNum == 0 || auxNum == 1)
        {
            numero->impar = auxNum;
            aux = 0;
        }
    }

    return aux;
}

int setPrimo(eNumero* numero,char* num)
{
    int aux = -1,auxNum;

    if(numero != NULL && num != NULL)
    {

        auxNum = atoi(num);

        if(auxNum == 0 || auxNum == 1)
        {
            numero->primo = auxNum;
            aux = 0;
        }
    }

    return aux;
}

int getNumero(eNumero* num)
{
    int aux;

    if(num!= NULL)
    {
        aux = num->numero;
    }

    return aux;
}

char* getNombre (eNumero* num)
{
    char* aux;

    aux = (char*)malloc(sizeof(char)*50);

    if(aux!= NULL && num != NULL)
    {
        strcpy(aux,num->nombre);
    }

    return aux;
}

int getPar(eNumero* num)
{
    int aux;

    if(num!= NULL)
    {
        aux = num->par;
    }

    return aux;
}

int getImpar(eNumero* num)
{
    int aux;

    if(num!= NULL)
    {
        aux = num->impar;
    }

    return aux;
}

int getPrimo(eNumero* num)
{
    int aux;

    if(num!= NULL)
    {
        aux = num->primo;
    }

    return aux;
}
