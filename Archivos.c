#include "Archivos.h"

int leerConfig(tConfig* config)
{
    FILE* configArch = fopen("config.txt", "rt");
    if(!configArch)
    {
        return -1;
    }
    char primeraLinea[100];
    fgets(primeraLinea, 100, configArch);
    char* aux = primeraLinea;
    aux = strchr(primeraLinea, '\n');
    *aux = '\0';
    aux = strchr(primeraLinea, '|');
    strcpy(config->codigo, aux+1);
    *aux = '\0';

    strcpy(config->apiUrl, primeraLinea);
    fgets(primeraLinea, 100, configArch);
    aux = strchr(primeraLinea, '\n');
    *aux = '\0';
    long num = strtol(primeraLinea, NULL, 10);
    config->cantidad = (int)num;
//    printf("%s %s %d\n", config->apiUrl, config->codigo, config->cantidad);
    fclose(configArch);
    return 0;
}
