#ifndef FUNCIONES_H
#define FUNCIONES_H

// Agregamos esto para que reconozca el struct Deportista
#include "deportista.h" 

void finalizar_programa();
void help();

// Ahora el compilador ya sabe qué es 'Deportista' cuando llegue aquí
void generarDatos(Deportista **arreglo, int *cantidad);
void guardarCSV(Deportista *arreglo, int cantidad, const char *nombreArchivo);
void cargarCSV(Deportista **arreglo, int *cantidad, const char *nombreArchivo);
void mostrarTodo(Deportista *arreglo, int cantidad);


// ordenamiento
void bubbleSort(Deportista *a, int n);
void selectionSort(Deportista *a, int n);
void insertionSort(Deportista *a, int n);
void cocktailSort(Deportista *a, int n);

void busquedaSecuencial(Deportista *arreglo, int cantidad, const char *nombreBuscar);
void busquedaBinaria(Deportista *arreglo, int cantidad, const char *nombreBuscar);

#endif