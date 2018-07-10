#include "ArrayList.h"

#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

typedef struct
{
    char date[11];
    char time[6];
    int serviceId;
    int gravedad;
    char msg[65];
}eLong;

typedef struct
{
    int id;
    char name[33];
    char email[65];
    int fallosTotal;
}eServices;

typedef struct
{
    char date[11];
    char time[6];
    char name[33];
    char msg[65];
    char email[65];
}eErrores;

int menuPrincipal ();
int validarLetra (char opcion[]);
eLong* constructorLong();
eServices* constructorServices();
eErrores* constructorWarnings();
void cargarStructLong(ArrayList* lista);
void cargarStructServices(ArrayList* lista);
void procesarInformacion(ArrayList* listaLong,ArrayList* listaServices,ArrayList* listaWarnings,ArrayList* listaErrores);
void mostrarEstadisticas(ArrayList* listaLong,ArrayList* listaServices);
void contarFallosServicio(ArrayList* listaLong,ArrayList* listaServices);
void crearArchivoWarnings(ArrayList* warnings);
void crearArchivoErrores(ArrayList* errores);
void mostrarListaWarnings (ArrayList* lista);
void mostrarListaErrores (ArrayList* lista);
void mostrarListaLong (ArrayList* lista);
void mostrarListaServices (ArrayList* lista);
#endif // FUNCIONES_H_INCLUDED
