#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef void(*Accion)(void*);
typedef int(*Cmp)(void* a, void* b);
typedef struct {
    void* data;
    size_t tamDato;
    int capacidad;
    int tam_actual;
} TDAVector;

void crearVector(TDAVector* vec, size_t tamDato, size_t cantidad);
void agregarVector(TDAVector* vec, void* data);
void mostrarVector(TDAVector* vec, Accion mostrar);
void mezclarVector(TDAVector* vec);
void indiceVector(TDAVector* vec, void* data, int idx);
void insertarVectorOrdenado(TDAVector* vec, void* data, Cmp cmp);
void vaciarVector(TDAVector* vec);
#endif // VECTOR_H_INCLUDED
