#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "funciones.h"
#include "ArrayList.h"

eLong* constructorLong()
{
    eLong* aux = NULL;

    aux = (eLong*)malloc(sizeof(eLong));

    if(aux!=NULL)
    {
        strcpy(aux->date,"");
        strcpy(aux->msg,"");
        strcpy(aux->time,"");
        aux->gravedad = 0;
        aux->serviceId = 0;
    }

    return aux;
}

eServices* constructorServices()
{
    eServices* aux = NULL;

    aux = (eServices*)malloc(sizeof(eServices));

    if(aux!=NULL)
    {
        strcpy(aux->name,"");
        strcpy(aux->email,"");
        aux->id = 0;
        aux->fallosTotal=0;
    }

    return aux;
}

eErrores* constructorWarnings()
{
    eErrores* aux = NULL;

    aux = (eErrores*)malloc(sizeof(eErrores));

    if(aux!=NULL)
    {
        strcpy(aux->date,"");
        strcpy(aux->time,"");
        strcpy(aux->name,"");
        strcpy(aux->msg,"");
        strcpy(aux->email,"");
    }

    return aux;
}

void cargarStructLong(ArrayList* lista)
{
    eLong* aux;
    FILE* archivo;
    int cantidad = 0;
    char auxDate[100];
    char auxTime[100];
    char auxMsg [100];
    char AuxServiceID[100];
    char auxGravedad[100];
    int serviceatoi,gravedadatoi;

    archivo = fopen("long.txt","r");

    if(lista != NULL && archivo != NULL)
    {
        lista->clear(lista);

        while(!feof(archivo))
        {
            cantidad = fscanf(archivo,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n",auxDate,auxTime,AuxServiceID,auxGravedad,auxMsg);

            aux = constructorLong();

            serviceatoi = atoi(AuxServiceID);
            gravedadatoi = atoi(auxGravedad);

            if(aux != NULL && cantidad == 5)
            {
                strcpy(aux->date,auxDate);
                strcpy(aux->msg,auxMsg);
                strcpy(aux->time,auxTime);
                aux->gravedad = gravedadatoi;
                aux->serviceId = serviceatoi;

                lista->add(lista,aux);
            }
            else
            {
                printf("No se pudo cargar el archivo correctamente.\n");
                system("pause");
                break;
            }
        }

        system("cls");
        printf("Archivo Long.txt Cargado Con Exito!\n");
        system("pause");
    }

    fclose(archivo);
}

void cargarStructServices(ArrayList* lista)
{
    eServices* aux;
    FILE* archivo;
    int cantidad = 0;
    char auxName[100];
    char auxEmail[100];
    char auxID[100];
    int idAtoi;

    archivo = fopen("services.txt","r");

    if(lista != NULL && archivo != NULL)
    {
        lista->clear(lista);

        while(!feof(archivo))
        {
            cantidad = fscanf(archivo,"%[^;];%[^;];%[^\n]\n",auxID,auxName,auxEmail);
            aux = constructorServices();

            idAtoi = atoi(auxID);

            if(aux != NULL && cantidad == 3)
            {
                strcpy(aux->name,auxName);
                strcpy(aux->email,auxEmail);
                aux->id = idAtoi;

                lista->add(lista,aux);
            }
            else
            {
                printf("No se pudo cargar el archivo correctamente.\n");
                system("pause");
                break;
            }
        }

        system("cls");
        printf("Archivo services.txt Cargado Con Exito!\n");
        system("pause");
    }

    fclose(archivo);
}

void procesarInformacion(ArrayList* listaLong,ArrayList* listaServices,ArrayList* listaWarnings,ArrayList* listaErrores)
{
    int l,s,flag=0;
    eLong* auxL;
    eServices* auxS;
    eErrores* auxWar;
    eErrores* auxErr;

    if(listaLong != NULL && listaServices != NULL)
    {
        system("cls");

        for(l=0; l<listaLong->len(listaLong); l++)
        {
            auxL = (eLong*)listaLong->get(listaLong,l);

            for(s=0; s<listaServices->len(listaServices); s++)
            {
                auxS = (eServices*)listaServices->get(listaServices,s);

                if((auxL->serviceId) == (auxS->id) && auxL->gravedad == 3)
                {
                    auxWar = constructorWarnings();

                    if(auxWar!= NULL)
                    {
                        strcpy(auxWar->date,auxL->date);
                        strcpy(auxWar->time,auxL->time);
                        strcpy(auxWar->name,auxS->name);
                        strcpy(auxWar->msg,auxL->msg);
                        strcpy(auxWar->email,auxS->email);

                        listaWarnings->add(listaWarnings,auxWar);
                    }

                }

                if( (auxL->serviceId) == (auxS->id) && (auxL->gravedad>3) && (auxL->gravedad<=7) )
                {
                    if(flag==0)
                    {
                        printf("Fallos con gravedad entre 4 y 7(inclusive) :\n\n");
                        flag=1;
                    }
                    printf("%s;%s;%s;%s;%d\n",auxL->date,auxL->time,auxS->name,auxL->msg,auxL->gravedad);
                }

                if((auxL->serviceId) == (auxS->id) && auxL->gravedad >7)
                {
                    auxErr = constructorWarnings();

                    if(auxErr != NULL)
                    {
                        strcpy(auxErr->date,auxL->date);
                        strcpy(auxErr->time,auxL->time);
                        strcpy(auxErr->name,auxS->name);
                        strcpy(auxErr->msg,auxL->msg);
                        strcpy(auxErr->email,auxS->email);

                        listaErrores->add(listaErrores,auxErr);
                    }


                }
            }
        }
        system("pause");
    }

    crearArchivoErrores(listaErrores);
    crearArchivoWarnings(listaWarnings);
}

void mostrarEstadisticas(ArrayList* listaLong,ArrayList* listaServices)
{
    int l,s;
    int conMenores3=0,conIgual3=0,conEntre4Y7=0,conMayor7=0;
    int falloMax;
    eLong* auxL;
    eServices* auxS;

    if(listaLong!= NULL && listaServices != NULL)
    {
        system("cls");
        for(l=0; l<listaLong->len(listaLong); l++)
        {
            auxL = (eLong*)listaLong->get(listaLong,l);

            if(auxL->gravedad<3)
            {
                conMenores3++;
            }
            if(auxL->gravedad==3)
            {
                conIgual3++;
            }
            if(auxL->gravedad>=4 && auxL->gravedad<=7)
            {
                conEntre4Y7++;
            }
            if(auxL->gravedad>7)
            {
                conMayor7++;
            }
        }
    }

    contarFallosServicio(listaLong,listaServices);

    for(s=0;s<listaServices->len(listaServices);s++)
    {
        auxS= (eServices*)listaServices->get(listaServices,s);

        falloMax = auxS->fallosTotal;
        break;
    }

    for(s=0;s<listaServices->len(listaServices);s++)
    {
        auxS= (eServices*)listaServices->get(listaServices,s);

        if(falloMax<auxS->fallosTotal)
        {
            falloMax = auxS->fallosTotal;
        }
    }

    for(s=0;s<listaServices->len(listaServices);s++)
    {
        auxS= (eServices*)listaServices->get(listaServices,s);

        if(falloMax == auxS->fallosTotal)
        {
            printf("Servicio con mas fallos : %s\n\n",auxS->name);
            break;
        }
    }

    printf("Fallos menores a 3 : %d\nFallos iguales a 3 : %d\nFallos entre 4 y 7(inclusive) : %d\nFallos mayores a 7: %d",conMenores3,conIgual3,conEntre4Y7,conMayor7);
    getch();
}

void contarFallosServicio(ArrayList* listaLong,ArrayList* listaServices)
{
    int l,s;
    eServices* auxS;
    eLong* auxL;
    int conFallos=0;

    if(listaLong!= NULL && listaServices != NULL)
    {
        for (s=0;s<listaServices->len(listaServices);s++)
        {
            auxS = (eServices*)listaServices->get(listaServices,s);

            for(l=0;l<listaLong->len(listaLong);l++)
            {
                auxL = (eLong*)listaLong->get(listaLong,l);

                if(auxL->serviceId == auxS->id && auxL->gravedad>=0)
                {
                    conFallos++;
                    auxS->fallosTotal = conFallos;

                    listaServices->set(listaServices,s,auxS);
                }
            }
        }
    }
}

void crearArchivoWarnings(ArrayList* warnings)
{
    FILE* archivo;
    eErrores* aux;
    int i;

    archivo = fopen("warnings.txt","w");

    if(warnings!= NULL && archivo != NULL)
    {
        for(i=0; i<warnings->len(warnings); i++)
        {
            aux = (eErrores*)warnings->get(warnings,i);

            fprintf(archivo,"%d  %s;%s;%s;%s;%s\n",i+1,aux->date,aux->time,aux->name,aux->msg,aux->email);
        }

        system("cls");
        printf("Archivo Warnings.txt Generado Con Exito!\n");
        system("pause");
    }

    fclose(archivo);
}

void crearArchivoErrores(ArrayList* errores)
{
    FILE* archivo;
    eErrores* aux;
    int i;

    archivo = fopen("errors.txt","w");

    if(errores!= NULL && archivo != NULL)
    {
        for(i=0; i<errores->len(errores); i++)
        {
            aux = (eErrores*)errores->get(errores,i);

            fprintf(archivo,"%-4d%s;%s;%s;%s;%s\n",i+1,aux->date,aux->time,aux->name,aux->msg,aux->email);
        }

        system("cls");
        printf("Archivo errors.txt Generado Con Exito!\n");
        system("pause");
    }

    fclose(archivo);
}

void mostrarListaWarnings (ArrayList* lista)
{
    int i;
    eErrores* aux;

    aux = constructorWarnings();

    if(lista != NULL && aux != NULL && lista->isEmpty(lista) == 0)
    {
        system("cls");
        printf("WARNINGS\n");
        for(i=0; i<lista->len(lista); i++)
        {
            aux = lista->get(lista,i);

            printf("%-4d%s;%s;%s;%s;%s\n",i+1,aux->date,aux->time,aux->name,aux->msg,aux->email);

        }
        system("pause");
    }

    if(lista->isEmpty(lista)==1)
    {
        system("cls");
        printf("No hay archivos cargados.");
        system("pause");
    }

}

void mostrarListaErrores (ArrayList* lista)
{
    int i;
    eErrores* aux;

    aux = constructorWarnings();

    if(lista != NULL && aux != NULL && lista->isEmpty(lista) == 0)
    {
        system("cls");
        printf("ERRORES\n");
        for(i=0; i<lista->len(lista); i++)
        {
            aux = lista->get(lista,i);

            printf("%-4d%s;%s;%s;%s;%s\n",i+1,aux->date,aux->time,aux->name,aux->msg,aux->email);

        }
        system("pause");
    }

    if(lista->isEmpty(lista)==1)
    {
        system("cls");
        printf("No hay archivos cargados.");
        system("pause");
    }

}
void mostrarListaLong (ArrayList* lista)
{
    int i;
    eLong* aux;

    aux = constructorLong();

    if(lista != NULL && aux != NULL && lista->isEmpty(lista) == 0)
    {
        system("cls");
        for(i=0; i<lista->len(lista); i++)
        {
            aux = lista->get(lista,i);

            printf("%s;%s;%d;%d;%s\n",aux->date,aux->time,aux->serviceId,aux->gravedad,aux->msg);

        }
        system("pause");
    }

    if(lista->isEmpty(lista)==1)
    {
        system("cls");
        printf("No hay archivos cargados.");
        system("pause");
    }

}

void mostrarListaServices (ArrayList* lista)
{
    int i;
    eServices* aux;

    aux = constructorServices();

    if(lista != NULL && aux != NULL && lista->isEmpty(lista) == 0)
    {
        system("cls");
        for(i=0; i<lista->len(lista); i++)
        {
            aux = lista->get(lista,i);

            printf("%d;%s;%s\nCantidad De Errores : %d \n",aux->id,aux->name,aux->email,aux->fallosTotal);

        }
        system("pause");
    }

    if(lista->isEmpty(lista)==1)
    {
        system("cls");
        printf("No hay archivos cargados.");
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
    printf("1- Leer Long.txt Y Services.txt.\n");
    printf("2- Procesar Informacion.\n");
    printf("3- Mostrar Estadisticas.\n");
    printf("4- Salir.\n\n");

    printf("Ingrese Respuesta: ");

    scanf("%s",opcion);

    while (validarLetra(opcion)== 1)
    {
        printf("Usted no puede ingresar un caracter!\nIngrese un numero ente 1 y 4 :");
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
