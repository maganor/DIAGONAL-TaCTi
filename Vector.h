#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
typedef void(*Accion)(void*, FILE*);
typedef void(*AccionVar)(void*, char*);
typedef int(*Cmp)(void* a, void* b);
typedef struct {
    void* data;
    size_t tamDato;
    int capacidad;
    int tam_actual;
} TDAVector;

void crearVector(TDAVector* vec, size_t tamDato, size_t cantidad);
void agregarVector(TDAVector* vec, void* data);
int tamVector(TDAVector* vec);
void mostrarVector(TDAVector* vec, Accion mostrar, FILE* donde);
void mostrarVectorVar(TDAVector* vec, AccionVar mostrar, char* var);
void mezclarVector(TDAVector* vec);
void indiceVector(TDAVector* vec, void* data, int idx);
void insertarVectorOrdenado(TDAVector* vec, void* data, Cmp cmp);
void vaciarVector(TDAVector* vec);
void imprimirMayores(TDAVector* vec, Cmp cmp, Accion mostrar, FILE* donde);
#endif // VECTOR_H_INCLUDED
