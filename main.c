#include <stdio.h>
#include <stdlib.h>
#include "TP.h"
#include <ctype.h>
//#include "API.h"

int main()
{
    tConfig config;
    char respuesta;

    if(leerConfig(&config) == -1)
    {
        printf("Error leyendo el archivo de configuracion, verifica que este bien escrito");
        system("exit");
    }

    do {
        system("cls");
        menuPrincipal();
        printf("Ingrese la opcion deseada: ");
        fflush(stdin);
        scanf("%c", &respuesta);
        if(respuesta == 'A') {
            iniciarPartida(&config);
        } else if (respuesta == 'B') {
            printf("Mostrando ranking del team");
        } else if (respuesta == 'C') {
            system("exit");
        } else {
            printf("Opcion Incorrecta");
        }
    } while(respuesta != 'C');
    return 0;
}

