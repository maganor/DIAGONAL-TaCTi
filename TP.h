#ifndef TP_H_INCLUDED
#define TP_H_INCLUDED
#include "Archivos.h"
#include "Tateti.h"
#include "Vector.h"

typedef struct
{
    char nombre[50];
    int puntos;
} tJugador;

void mostrarJugador(void* data);
void menuPrincipal();
void mostrarConfig(tConfig* config);
int cargarJugadores(TDAVector* jug, int cantidadMax);
int calcularPuntaje(tPuntaje *puntaje);
int cmpPuntosJugador(void* a, void* b);


#endif // TP_H_INCLUDED
