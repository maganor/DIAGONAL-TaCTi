#include "TP.h"
void mostrarJugador(void* data, FILE* donde)
{
    tJugador jugador = *(tJugador*)data;
    fprintf(donde, "%s %d\n", jugador.nombre, jugador.puntos);
}

void menuPrincipal()
{
    printf("\n");
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
        char nombre[100];
        scanf("%s", nombre);
        //Revisar que no este agregado
        if(strcmp(nombre, "listo") == 0) break;
        else
        {
            tJugador tempJug;
            strcpy(tempJug.nombre, nombre);
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


void mostrarVectorJSON(void* data, char* var) {
    tJugador jugador = *(tJugador*) data;
    sprintf(var + strlen(var), "\t{\n");
    sprintf(var + strlen(var), "\t\t\"nombre\": \"%s\",\n", jugador.nombre);
    sprintf(var + strlen(var), "\t\t\"puntos\": %d\n", jugador.puntos);
    sprintf(var + strlen(var), "\t},\n");
}

void generarJSONFinal(tJuego* juego, tConfig* config, TDAVector* jugadores) {
    char* json = (char*)malloc(1000);
    json[0] = '\0';
    sprintf(json, "{\n");
    sprintf(json + strlen(json), "\t\"Codigo Grupo\": \"%s\",\n", config->codigo);
    sprintf(json + strlen(json), "\t\"JUGADORES\":[\n");
    mostrarVectorVar(jugadores, mostrarVectorJSON, json);
    sprintf(json + strlen(json), "\t]\n");
    sprintf(json + strlen(json), "}");
//    enviarInformacionAPI("http://localhost:8080", json);
//    printf("\n%s", json);
    free(json);
}


void iniciarPartida(tConfig* config) {
    tJuego juego;
    int cantJugadores = 0, contJugadores = 0;
    char respuesta;
    tJugador temp;
    TDAVector jugadores, yaJugaron;

    time_t fecha = time(NULL);
    char fechastr[100];
    struct tm* fecha2;
    fecha2 = localtime(&fecha);
    strftime(fechastr, 100, "%Y-%m-%d-%H-%M.txt", fecha2);
    FILE* resArch = fopen(fechastr, "at");

    crearVector(&jugadores, sizeof(tJugador), 5);
    crearVector(&yaJugaron, sizeof(tJugador), 5);
    cantJugadores = cargarJugadores(&jugadores, 3);
//    mostrarConfig(&config);
    printf("El orden los jugadores sera: \n");
    mostrarVector(&jugadores, mostrarJugador, stdout);
    indiceVector(&jugadores, &temp, contJugadores); //Agarrar el primer jugador del vector para poder saber el nombre y preguntar si esta listo

    do {
        printf("Si estas listo para jugar escribi la letra s: ");
        fflush(stdin);
        scanf("%c", &respuesta);
    } while (tolower(respuesta) != 's');

    while(contJugadores < cantJugadores)
    {
        indiceVector(&jugadores, &temp, contJugadores);
        tPuntaje puntaje = empezarPartida(&juego, config->cantidad, temp.nombre, resArch);
        temp.puntos = calcularPuntaje(&puntaje);
        insertarVectorOrdenado(&yaJugaron, &temp, cmpPuntosJugador);
        contJugadores++;
    }
    fprintf(resArch, "Los jugadores con mas puntos fueron: \n");
    mostrarVector(&yaJugaron, mostrarJugador, stdout); //Escribir vector en el archivo
    imprimirMayores(&yaJugaron, cmpPuntosJugador, mostrarJugador, resArch);
//    generarJSONFinal(&juego, config, &jugadores);
    fclose(resArch);
    vaciarVector(&jugadores);
    vaciarVector(&yaJugaron);
}

