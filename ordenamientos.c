#include "ordenamientos.h"
#include <stdbool.h>

void bubbleSort(Deportista *arreglo, int n) {
    int i, j;
    bool intercambio;

    for (i = 0; i < n - 1; i++) {
        intercambio = false;

        for (j = 0; j < n - i - 1; j++) {
            if (arreglo[j].puntaje < arreglo[j + 1].puntaje) {
                Deportista temp = arreglo[j];
                arreglo[j] = arreglo[j + 1];
                arreglo[j + 1] = temp;
                intercambio = true;
            }
        }

        if (!intercambio)
            break;
    }
}

void insertionSort(Deportista *arreglo, int n) {
    int i, j;
    Deportista key;

    for (i = 1; i < n; i++) {
        key = arreglo[i];
        j = i - 1;

        while (j >= 0 && arreglo[j].puntaje < key.puntaje) {
            arreglo[j + 1] = arreglo[j];
            j--;
        }

        arreglo[j + 1] = key;
    }
}