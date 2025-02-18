#include "Vector.h"

void crearVector(TDAVector* vec, size_t tamDato, size_t cantidad)
{
    vec->tamDato = tamDato;
    vec->capacidad = cantidad;
    vec->tam_actual = 0;
    vec->data = malloc(tamDato * cantidad);
}

void agregarVector(TDAVector* vec, void* data)
{
    if(vec->tam_actual >= vec->capacidad)
    {
        vec->data = realloc(vec->data, vec->capacidad * 2);
        vec->capacidad = vec->capacidad * 2;
    }
    memcpy(vec->data + vec->tamDato * vec->tam_actual, data, vec->tamDato);
    vec->tam_actual+= 1;
}

void mezclarVector(TDAVector* vec)
{
    srand(time(NULL));
    void* temp = malloc(vec->tamDato);
    for(int i= vec->tam_actual-1; i>=1; i--)
    {
        int j = rand() % i;
        memcpy(temp, vec->data + i * vec->tamDato, vec->tamDato);
        memcpy(vec->data + i * vec->tamDato, vec->data + j * vec->tamDato, vec->tamDato);
        memcpy(vec->data + j * vec->tamDato, temp, vec->tamDato);
    }
    free(temp);
}

void mostrarVector(TDAVector* vec, Accion mostrar, FILE* donde)
{
    for(int i=0; i<vec->tam_actual; i++)
    {
        mostrar(vec->data+i*vec->tamDato, donde);
    }
}

void mostrarVectorVar(TDAVector* vec, AccionVar mostrar, char* var)
{
    for(int i=0; i<vec->tam_actual; i++)
    {
        mostrar(vec->data+i*vec->tamDato, var);
    }
}

int tamVector(TDAVector* vec) {
    return vec->tam_actual;
}


void indiceVector(TDAVector* vec, void* data, int idx)
{
    memcpy(data, vec->data + idx * vec->tamDato, vec->tamDato);
}

void insertarVectorOrdenado(TDAVector* vec, void* data, Cmp cmp)
{
    int i = 0;
    while(cmp(vec->data + i*vec->tamDato, data) < 0 && i<vec->tam_actual)
    {
        i++;
    }
    for(int j = vec->tam_actual; j > i; j--)
    {
        memcpy(vec->data + j*vec->tamDato, vec->data + j*vec->tamDato - vec->tamDato, vec->tamDato);
    }
    memcpy(vec->data + vec->tamDato * i, data, vec->tamDato);
    vec->tam_actual+= 1;
}

void vaciarVector(TDAVector* vec)
{
    free(vec->data);
    vec->tam_actual = 0;
}

void imprimirMayores(TDAVector* vec, Cmp cmp, Accion mostrar, FILE* donde)
{
    void* max = malloc(vec->tamDato);
    memcpy(max, vec->data, vec->tamDato);
    //Busco el mayor valor
    for(int i=1; i<vec->tam_actual; i++)
    {
        if(cmp(max, vec->data+i*vec->tamDato) < 0)
        {
            memcpy(max, vec->data+i*vec->tamDato, vec->tamDato);
        }
    }
    for(int i=0; i<vec->tam_actual; i++)
    {
        if(cmp(max, vec->data+i*vec->tamDato) == 0)
        {
            mostrar(vec->data+i*vec->tamDato, donde);
        }
    }
    free(max);
}
//Insertar en vector ordenado
