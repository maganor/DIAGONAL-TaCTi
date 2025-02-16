#include <stdio.h>
#include <stdlib.h>
#include "TP.h"
#include <ctype.h>
//#include "API.h"

int main()
{
    tJuego juego;
    tConfig config;
    int cantJugadores = 0, contJugadores = 0;
    char respuesta;
    tJugador temp;
    TDAVector jugadores;
    TDAVector yaJugaron;

    crearVector(&jugadores, sizeof(tJugador), 5);
    crearVector(&yaJugaron, sizeof(tJugador), 5);
    if(leerConfig(&config) == -1)
    {
        printf("Error leyendo el archivo de configuracion, verifica que este bien escrito");
        system("exit");
    }
    cantJugadores = cargarJugadores(&jugadores, 3);
//    mostrarConfig(&config);
    mostrarVector(&jugadores, mostrarJugador);
    indiceVector(&jugadores, &temp, contJugadores); //Agarrar el primer jugador del vector para poder saber el nombre y preguntar si esta listo
    printf("Estas listo para jugar %s? : ", temp.nombre);
    fflush(stdin);
    scanf("%c", &respuesta);
    if(tolower(respuesta) == 's')
    {
        while(contJugadores < cantJugadores)
        {
            indiceVector(&jugadores, &temp, contJugadores);
            tPuntaje puntaje = empezarPartida(&juego, config.cantidad, temp.nombre);
            temp.puntos = calcularPuntaje(&puntaje);
            insertarVectorOrdenado(&yaJugaron, &temp, cmpPuntosJugador);
            contJugadores++;
        }
    }
    mostrarVector(&yaJugaron, mostrarJugador);
//    escribirResultado(&config);
    vaciarVector(&jugadores);
    vaciarVector(&yaJugaron);
    return 0;
}

//TESTEO TDA VECTOR DESPUES BORRO

//int cmpInt(void* a, void* b) {
//    return *(int*)b - *(int*)a;
//}
//
//void mostrar(void* data) {
//    int dato = *(int*)data;
//    printf("%d ", dato);
//}
//
//int main() {
//    TDAVector vec;
//    crearVector(&vec, sizeof(int), 6);
//    int num = 4;
//    insertarVectorOrdenado(&vec, &num, cmpInt);
//    num = 2;
//    insertarVectorOrdenado(&vec, &num, cmpInt);
//    num = 1;
//    insertarVectorOrdenado(&vec, &num, cmpInt);
//    num = 0;
//    insertarVectorOrdenado(&vec, &num, cmpInt);
//    num = 3;
//    insertarVectorOrdenado(&vec, &num, cmpInt);
//    mostrarVector(&vec, mostrar);
////    mezclarVector(&vec);
////    mostrarVector(&vec, mostrar);
//
//    return 0;
//}
