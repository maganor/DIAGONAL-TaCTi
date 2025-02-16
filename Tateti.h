#ifndef TATETI_H_INCLUDED
#define TATETI_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#define TERMINO_RONDA 0
#define EMPATE 0
#define MAQUINA -1
#define JUGADOR 1
#define TERMINO_PARTIDA 1
typedef unsigned char Tablero[3][3];
typedef void(*Mostrar)(Tablero);
typedef enum
{
    Circulo,
    Cruz
} Pieza;

typedef enum
{
    Maquina,
    Usuario
} Jugador;

// Este juego de TATETI es principalmente contra la maquina.
// Como parametros de inicializacion recibe cantidad de jugadores, cantidad de rondas, un callback para el resultado de la ronda.
typedef struct
{
    int jugador;
    int maquina;
    int empates;
} tPuntaje;

typedef struct
{
    Pieza simbolo;
    char nombre[50];
    char turnos;
} TJug;

typedef struct
{
    char jugador, maquina;
    unsigned char jugadorC, maquinaC;
    Tablero tablero;
    Jugador actual;
    Jugador esCruz; //0 = Maquina - 1 = Jugador
    int rondas, rondaActual;
    char espaciosDisponibles;
    Mostrar verTablero;
    char nombreJugador[50];
} tJuego;

typedef struct
{
    char fila;
    char col;
} tPos;

void mostrarTablero(tJuego* juego);

void iniciarJuego(tJuego* juego);

tPuntaje empezarPartida(tJuego* juego, int cantRondas, char nombre[50]);

#endif // TATETI_H_INCLUDED
