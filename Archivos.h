#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
typedef struct
{
    char apiUrl[100];
    char codigo[20];
    int cantidad;
} tConfig;

int leerConfig(tConfig* config);
#endif // ARCHIVOS_H_INCLUDED
