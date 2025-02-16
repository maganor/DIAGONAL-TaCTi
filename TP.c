#include "TP.h"
void mostrarJugador(void* data)
{
    tJugador jugador = *(tJugador*)data;
    printf("%s %d\n", jugador.nombre, jugador.puntos);
}

void menuPrincipal()
{
    printf("TATETI\n");
    printf("[A] Iniciar Juego\n");
    printf("[B] Ver ranking equipo\n");
    printf("[C] Salir\n");
}

void mostrarConfig(tConfig* config)
{
    printf("Configuracion Actual: \n");
    printf("URL API: %s - Nombre Equipo: %s\n", config->apiUrl, config->codigo);
    printf("Rondas: %d\n", config->cantidad);
}

int cargarJugadores(TDAVector* jug, int cantidadMax)
{
    int cant = 0;
    printf("Ingresa los jugadores: ");
    while(cant < cantidadMax)
    {
        char temp[100];
        scanf("%s", temp);
        //Revisar que no este agregado
        if(strcmp(temp, "listo") == 0) break;
        else
        {
            tJugador tempJug;
            strcpy(tempJug.nombre, temp);
            tempJug.puntos = 0;
            agregarVector(jug, &tempJug);
            cant++;
        }
    }
    mezclarVector(jug);
    return cant;
}

int calcularPuntaje(tPuntaje *puntaje)
{
    return puntaje->empates * 2 + puntaje->jugador * 3 + puntaje->maquina * (-1);
}

int cmpPuntosJugador(void* a, void* b)
{
    tJugador jugadorA = *(tJugador*)a;
    tJugador jugadorB = *(tJugador*)b;

    return jugadorA.puntos - jugadorB.puntos;
}
