#ifndef API_H_INCLUDED
#define API_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

int enviarInformacionAPI(char* urlApi, char* jsonDatos);

#endif // API_H_INCLUDED
