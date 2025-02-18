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
