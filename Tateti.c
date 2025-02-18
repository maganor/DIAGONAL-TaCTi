#include "Tateti.h"
#include "TP.h"
void llenarTablero(unsigned char tablero[3][3])
{
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++) tablero[i][j] = '0';
}

//Devuelve 0 si el jugador enviado gano
int revisarVictoria(tJuego* juego, char jugador)
{
    int i, j, cont;
    //Horizontal
    for(i=0; i<3; i++)
    {
        cont = 0;
        for(j=0; j<3; j++)
            if(juego->tablero[i][j] == jugador) cont++;
        if(cont == 3) return 1;
    }
    //Vertical
    for(i=0; i<3; i++)
    {
        cont = 0;
        for(j=0; j<3; j++) if(juego->tablero[j][i] == jugador) cont++;
        if(cont == 3) return 1;
    }
    //Diagonal principal
    cont = 0;
    for(i=0; i<3; i++) if(juego->tablero[i][i] == jugador) cont++;
    if(cont == 3) return 1;
    //Diagonal secundaria
    cont = 0;
    for(i=0; i<3; i++) if(juego->tablero[i][2-i] == jugador) cont++;
    if(cont == 3) return 1;
    if(juego->espaciosDisponibles <= 0)
    {
        return -1;
    }
    return 0;
}

void mostrarTablero(tJuego* juego)
{
    printf("Jugador actual: %s\n", juego->nombreJugador);
    printf("Tu pieza es %c - Ronda: %d/%d\n", juego->jugadorC, juego->rondaActual, juego->rondas);
    for(int i=0; i<3; i++)
    {
        if(i == 0)
        {
            printf("  0 1 2");
            printf("\n  - - -\n");
        }
        for(int j=0; j<3; j++)
        {
            if(j==0) printf("%d|", i);
            if(juego->tablero[i][j] == '0') printf(" |");
            else printf("%c|", juego->tablero[i][j]);
        }
        printf("\n  - - -\n");
    }
}

tPos buscarPosicion(tJuego* juego, char jugador)
{
    //Busca cuantas veces se repite la pieza enviada
    //Horizontal
    int cont, i, j;
    tPos pos = {128, 128};
    for(i=0; i<3; i++)
    {
        cont = 0;
        pos.fila = 128;
        for(j=0; j<3; j++)
        {
            if(juego->tablero[i][j] == '0')
            {
                pos.fila = i;
                pos.col = j;
            }
            if(juego->tablero[i][j] == jugador) cont++;
        }
        if(cont == 2 && pos.fila != 128) return pos;
    }
    cont = 0;
    for(i=0; i<3; i++)
    {
        cont = 0;
        pos.fila = 128;
        for(j=0; j<3; j++)
        {
            if(juego->tablero[j][i] == '0')
            {
                pos.fila = j;
                pos.col = i;
            }
            if(juego->tablero[j][i] == jugador) cont++;
        }
        if(cont == 2 && pos.fila != 128) return pos;
    }
    //Vertical
    //Faltan diagonales
    cont = 0;
    pos.fila = 128;
    for(i=0; i<3; i++)
    {
        if(juego->tablero[i][i] == '0')
        {
            pos.fila = i;
            pos.col = i;
        }
        if(juego->tablero[i][i] == jugador) cont++;
    }
    if(cont == 2 && pos.fila != 128) return pos;
    //Diagonal secundaria
    cont = 0;
    pos.fila = 128;
    for(i=0; i<3; i++)
    {
        if(juego->tablero[i][2-i] == '0')
        {
            pos.fila = i;
            pos.col = 2-i;
        }
        if(juego->tablero[i][2-i] == jugador) cont++;
    }
    if(cont == 2 && pos.fila != 128) return pos;
    pos.fila = 128;
    return pos;
}

void jugadaAleatoria(unsigned char tablero[3][3], char pieza)
{
    int x, y;
    do
    {
        x = rand() % 3;
        y = rand() % 3;
    }
    while (tablero[y][x] != '0');
    tablero[y][x] = pieza;
}

void jugadaMaquina(tJuego* juego, unsigned char pieza)
{
    tPos pos;
    if (juego->maquina>=2)
    {
        pos = buscarPosicion(juego, juego->maquinaC); //Busca ganar la maquina
        if(pos.fila != 128)   //Si encuentra una posicion para jugar
        {
            juego->tablero[pos.fila][pos.col] = pieza;
            return;
        }
    }
    if(juego->jugador >= 2)   //Si se jugo dos o mas veces, ya tiene chances de ganar tengo que tratar de que no.
    {
        pos = buscarPosicion(juego, juego->jugadorC); //Trata de cancelar la victoria del jugador
        if(pos.fila != 128)   //Si encuentra una posicion para jugar
        {
            juego->tablero[pos.fila][pos.col] = pieza;
            return;
        }
    }
    jugadaAleatoria(juego->tablero, pieza);
}

void jugadaJugador(tJuego* juego)
{
    int bien, x, y;
    do
    {
        printf("Ingresar col fila: ");
        fflush(stdin);
        bien = scanf("%d %d", &x, &y); //scanf si leyo bien devuelve la cantidad de parametros mandados.
        if(x>2 || y>2 || juego->tablero[y][x] != '0' || bien != 2)
            printf("Posicion invalida\n");
    }
    while(x>2 || y>2 || juego->tablero[y][x] != '0');
    juego->tablero[y][x] = juego->jugadorC;
    juego->jugador+=1;
    juego->espaciosDisponibles-=1;
}

int revisarCondicionFin(tJuego* juego)
{
    //La forma del jugador actual
    char formaActual = juego->actual == Usuario ? juego->jugadorC : juego->maquinaC;
    //Solo revisar victoria si se jugaron al menos 5 turnos.
    int resultado = revisarVictoria(juego, formaActual);
    if(resultado == 1) //Victoria
    {
        return formaActual == juego->jugadorC;
    }
    else if(resultado == -1)     //EMPATE
    {
        return -1;
    }
    return 2;
}

void escribirTableroArchivo(tJuego* juego, FILE* arch) {
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            if(juego->tablero[i][j] == '0') {
                fprintf(arch, "  ");
            }
            else fprintf(arch,"%c ", juego->tablero[i][j]);
        }
        fprintf(arch, "\n");
    }
}
tPuntaje empezarPartida(tJuego* juego, int cantRondas, char nombre[50], FILE* resultados)
{
    juego->puntaje = (tPuntaje)
    {
        0, 0, 0
    };
    juego->rondas = cantRondas;
    juego->jugador = 0;
    juego->maquina = 0;
    juego->rondaActual = 1;
    juego->espaciosDisponibles = 9;
    strcpy(juego->nombreJugador, nombre);

    srand(time(NULL));
    int numeroAleatorio, puntaje;
    Jugador jugadorAleatorio;
    fprintf(resultados, "TURNO DE %s\n", nombre);
    while(juego->rondaActual <= juego->rondas)
    {
        llenarTablero(juego->tablero);
        numeroAleatorio = rand() % 2;
        jugadorAleatorio = numeroAleatorio == 0 ? Maquina : Usuario;
        juego->esCruz = jugadorAleatorio; //Quien es el principal
        juego->actual = jugadorAleatorio; //Turno Actual
        if(juego->esCruz == Maquina)
        {
            juego->maquinaC = 'X';
            juego->jugadorC = 'O';
        }
        else
        {
            juego->maquinaC = 'O';
            juego->jugadorC = 'X';
        }
        while(1)   //Loop del juego
        {
            system("cls");
            mostrarTablero(juego);
            //Se decide si juega la maquina o el jugador
            if(juego->actual == Maquina) //Turno de la maquina
            {
                jugadaMaquina(juego, juego->maquinaC);
                juego->maquina+=1;
                juego->espaciosDisponibles-=1;
            }
            else //Turno del Jugador
            {
                jugadaJugador(juego);
            }
            //Tiene que breakear si es 1
            system("cls");
            mostrarTablero(juego);
            int condicion = revisarCondicionFin(juego);
            if(condicion != 2)
            {
                escribirTableroArchivo(juego, resultados);
                if(condicion == JUGADOR)
                {
                    // Gano el jugador
                    juego->puntaje.jugador++;
                    puntaje = calcularPuntaje(&(juego->puntaje));
                    fprintf(resultados, "Ganaste 3 puntos. Vas %d puntos\n", puntaje);
                    printf("Gano el jugador\n");
                }
                else if (condicion == MAQUINA)
                {
                    juego->puntaje.maquina++;
                    puntaje = calcularPuntaje(&(juego->puntaje));
                    fprintf(resultados, "Gano la maquina, Perdiste 1 punto. Vas %d puntos\n", puntaje);
                    printf("Gano la maquina\n");
                }
                else if (condicion == EMPATE)    //Empate
                {
                    juego->puntaje.empates++;
                    puntaje = calcularPuntaje(&(juego->puntaje));
                    fprintf(resultados, "Hubo empate, Ganaste 2 puntos. Vas %d puntos\n", puntaje);
                    printf("Hubo empate\n");
                }
                break;
            }
//            if(revisarCondicionFin(juego) == 1) break; //Hubo empate/victoria
            juego->actual = !juego->actual; //Cambiar de jugador
        }
        getch(); //Esperar entrada del usuario para poder continuar
        //Reiniciar ronda
        juego->rondaActual+=1;
        juego->jugador = 0;
        juego->maquina = 0;
        juego->espaciosDisponibles = 9;
    }

    return juego->puntaje;
}
