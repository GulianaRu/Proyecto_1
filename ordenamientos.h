#ifndef ORDENAMIENTOS_H
#define ORDENAMIENTOS_H

#include "deportista.h"

// Algoritmos de ordenamiento
void bubbleSort(Deportista *arreglo, int n);
void insertionSort(Deportista *arreglo, int n);
void selectionSort(Deportista *arreglo, int n);
void cocktailShakerSort(Deportista *arreglo, int n);

// Algoritmos de Busqueda
int busquedaSecuencial(Deportista *arreglo, int n, int idBuscado);
int busquedaBinariaIterativa(Deportista *arreglo, int n, int idBuscado);
#endif