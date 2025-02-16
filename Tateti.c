#include "Tateti.h"
void llenarTablero(unsigned char tablero[3][3])
{
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++) tablero[i][j] = '0';
}

int revisarVictoria(tJuego* juego, char jugador)
{
    //Horizontal
    int i, j;
    int cont;
    for(i=0; i<3; i++)
    {
        cont = 0;
        for(j=0; j<3; j++) if(juego->tablero[i][j] == jugador) cont++;
        if(cont == 3) return 0;
    }
    //Vertical
    for(i=0; i<3; i++)
    {
        cont = 0;
        for(j=0; j<3; j++) if(juego->tablero[j][i] == jugador) cont++;
        if(cont == 3) return 0;
    }
    //Diagonal principal
    cont = 0;
    for(i=0; i<3; i++) if(juego->tablero[i][i] == jugador) cont++;
    if(cont == 3) return 0;
    //Diagonal secundaria
    cont = 0;
    for(i=0; i<3; i++) if(juego->tablero[i][2-i] == jugador) cont++;
    if(cont == 3) return 0;
    return -1;
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
    //Horizontal
    int cont, i, j;
    tPos pos = {-1, -1};
    for(i=0; i<3; i++)
    {
        cont = 0;
        for(j=0; j<3; j++)
        {
            if(juego->tablero[i][j] == '0')
            {
                pos.fila = i;
                pos.col = j;
            }
            if(juego->tablero[i][j] == jugador) cont++;
        }
        if(cont == 2) return pos;
    }
    cont = 0;
    for(i=0; i<3; i++)
    {
        cont = 0;
        for(j=0; j<3; j++)
        {
            if(juego->tablero[j][i] == '0')
            {
                pos.fila = j;
                pos.col = i;
            }
            if(juego->tablero[j][i] == jugador) cont++;
        }
        if(cont == 2) return pos;
    }
    //Vertical
    //Faltan diagonales
    cont = 0;
    for(i=0; i<3; i++)
    {
        if(juego->tablero[i][i] == '0')
        {
            pos.fila = i;
            pos.col = i;
        }
        if(juego->tablero[i][i] == jugador) cont++;
    }
    if(cont == 2) return pos;
    //Diagonal secundaria
    cont = 0;
    for(i=0; i<3; i++)
    {
        if(juego->tablero[i][2-i] == '0')
        {
            pos.fila = i;
            pos.col = 2-i;
        }
        if(juego->tablero[i][2-i] == jugador) cont++;
    }
    if(cont == 2) return pos;
    return pos;
}

void jugadaAleatoria(unsigned char tablero[3][3], char pieza)
{
    int x, y;
    do
    {
        x = rand() % 3;
        y = rand() % 3;
//        printf("%d %d", x, y);
    }
    while (tablero[y][x] != '0');
    tablero[y][x] = pieza;
}

void jugadaMaquina(tJuego* juego, unsigned char pieza)
{
    tPos pos;
    if(juego->jugador >= 2)   //Si se jugo dos o mas veces, ya tiene chances de ganar tengo que tratar de que no.
    {
        pos = buscarPosicion(juego, juego->jugadorC);
        if(pos.fila != -1)   //Si encuentra una posicion para jugar
        {
            if(juego->tablero[pos.fila][pos.col] == '0')   //Si la fila no es
            {
                juego->tablero[pos.fila][pos.col] = pieza;
                return;
            }
        }
        else if (juego->maquina>=2)
        {
            pos = buscarPosicion(juego, juego->maquinaC);
            if(pos.fila != -1)   //Si encuentra una posicion para jugar
            {
                if(juego->tablero[pos.fila][pos.col] == '0')   //Si la fila no es
                {
                    juego->tablero[pos.fila][pos.col] = pieza;
                    return;
                }
            }
        }
    }
    jugadaAleatoria(juego->tablero, pieza);
}


tPuntaje empezarPartida(tJuego* juego, int cantRondas, char nombre[50])
{
    tPuntaje puntaje = {0, 0, 0};
    juego->rondas = cantRondas;
    juego->jugador = 0;
    juego->maquina = 0;
    juego->rondaActual = 1;
    juego->espaciosDisponibles = 9;
    strcpy(juego->nombreJugador, nombre);

    srand(time(NULL));
    int x, y, numeroAleatorio;
    Jugador jugadorAleatorio;
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
            if(juego->actual == Maquina)
            {
                jugadaMaquina(juego, juego->maquinaC);
                juego->maquina+=1;
                juego->espaciosDisponibles-=1;
            }
            else
            {
                int bien;
                do
                {
                    printf("Ingresar col/fila: ");
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
            //La forma del jugador actual
            char formaActual = juego->actual == Usuario ? juego->jugadorC : juego->maquinaC;
            //Solo revisar victoria si se jugaron al menos 5 turnos.
            if(juego->espaciosDisponibles < 5)
            {
                if(revisarVictoria(juego, formaActual) == 0) //Gano el jugador actual?
                {
                    system("cls");
                    mostrarTablero(juego);
                    if(formaActual == juego->jugadorC)
                    {
                        puntaje.jugador++;
                        printf("Gano el jugador\n");
                    }
                    else
                    {
                        puntaje.maquina++;
                        printf("Gano la maquina\n");
                    }
                    break;
                }
            }
            if(juego->espaciosDisponibles <= 0)
            {
                puntaje.empates++;
                break;
            }
            juego->actual = !juego->actual; //Cambiar de jugador
        }
        getch();
        //Reiniciar ronda
        juego->rondaActual+=1;
        juego->jugador = 0;
        juego->maquina = 0;
        juego->espaciosDisponibles = 9;
    }
    return puntaje;
}
