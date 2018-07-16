#include "ArrayList.h"

#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

typedef struct
{
    int numero;
    char nombre[51];
    int par;
    int impar;
    int primo;
}eNumero;


int menuPrincipal ();
int validarLetra (char opcion[]);
eNumero* constructorNumero();
FILE* leerArchivo(char* nombre);
void cargarCsv (ArrayList* numero);
void mostrarNumeros (ArrayList* numeros);
int setNumero(eNumero* numero,char* num);
int getNumero(eNumero* num);
int setNombre (eNumero* numero,char* nombre);
char* getNombre (eNumero* num);
int setPar(eNumero* numero,char* num);
int getPar(eNumero* num);
int setImpar(eNumero* numero,char* num);
int getImpar(eNumero* num);
int setPrimo(eNumero* numero,char* num);
int getPrimo(eNumero* num);

#endif // FUNCIONES_H_INCLUDED
