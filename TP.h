#ifndef TP_H_INCLUDED
#define TP_H_INCLUDED
#include "Archivos.h"
#include "ctype.h"
#include "Tateti.h"
#include "Vector.h"
#include "API.h"

typedef struct
{
    char nombre[50];
    int puntos;
} tJugador;

void mostrarJugador(void* data, FILE* donde);
void menuPrincipal();
void mostrarConfig(tConfig* config);
int cargarJugadores(TDAVector* jug);
int calcularPuntaje(tPuntaje *puntaje);
int cmpPuntosJugador(void* a, void* b);
void iniciarPartida(tConfig* config);

#endif // TP_H_INCLUDED
