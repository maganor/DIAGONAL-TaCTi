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

int escribirResultado(tConfig* config)
{
    time_t fecha;
    char fechastr[100];
    fecha = time(NULL);
    struct tm* fecha2;
    fecha2 = localtime(&fecha);
    strftime(fechastr, 100, "%Y-%m-%d-%H-%m.txt", fecha2);
    printf("%s", fechastr);
    FILE* resArch = fopen("wep.txt", "wt");
    fprintf(resArch, "{\n");
    fprintf(resArch, "\t\"codigoGrupo\": %s,\n", config->codigo);
    fprintf(resArch, "\t\"jugadores\": [\n");
    //Iterar los jugadores y escribir
    fclose(resArch);
    return 0;
}
