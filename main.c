#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "deportista.h"
#include "ordenamientos.h"

#define MAX_NOMBRE 50
#define NUM_EQUIPOS 5

// Arreglo de equipos disponibles
const char *EQUIPOS[NUM_EQUIPOS] = {"Equipo1", "Equipo2", "Equipo3", "Equipo4", "Equipo5"};

// Estructura 
typedef struct {
    int id;
    char nombre[MAX_NOMBRE];
    char equipo[MAX_NOMBRE];
    float puntaje;
    int competencias;
} Deportista;

// Funciones del sistema
void generarDatos(Deportista **arreglo, int *cantidad);
void guardarCSV(Deportista *arreglo, int cantidad, const char *nombreArchivo);
void mostrarMenu();

// Algoritmos de Ordenamiento
void bubbleSort(Deportista *arreglo, int n); // Agregar optimizacion
void insertionSort(Deportista *arreglo, int n);
void selectionSort(Deportista *arreglo, int n); // Optimizar tambien
void cocktailShakerSort(Deportista *arreglo, int n);

// Algoritmos de Búsqueda
int busquedaSecuencial(Deportista *arreglo, int n, int idBuscado);
int busquedaBinariaIterativa(Deportista *arreglo, int n, int idBuscado);

int main() {
    // Inicializar semilla para la generación aleatoria
    srand(time(NULL));
    
    Deportista *deportistas = NULL;
    int cantidadDeportistas = 0;
    int opcion;

    do {
        mostrarMenu();
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                printf("\nGenerando datos \n");
                break;
           case 2:
                if (cantidadDeportistas == 0) {
                    printf("\nPrimero debes generar datos\n");
                    break;
                }

                int tipo;
                printf("\n1. Bubble Sort");
                printf("\n2. Insertion Sort");
                printf("\nSeleccione algoritmo: ");
                scanf("%d", &tipo);

                if (tipo == 1)
                    bubbleSort(deportistas, cantidadDeportistas);
                else
                    insertionSort(deportistas, cantidadDeportistas);

                printf("\nDatos ordenados correctamente\n");
                break;
            case 3:
                printf("\nBuscar Deportista (ID)\n");
                break;
            case 4:
                printf("\nRanking Mejores N Deportistas\n");
                break;
            case 0:
                printf("\nSaliendo del sistema... ¡Exito en la evaluacion!\n");
                break;
            default:
                printf("\nOpcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 0);

    // Liberar memoria
    if (deportistas != NULL) {
        free(deportistas);
    }

    return 0;
}

void mostrarMenu() {
    printf("\n========================================\n");
    printf("       SISTEMA DE DEPORTISTAS UMAG        \n");
    printf("========================================\n");
    printf("1. Generar y cargar datos\n");
    printf("2. Ordenar datos\n");
    printf("3. Buscar deportista por ID\n");
    printf("4. Mostrar ranking (Mejores N)\n");
    printf("0. Salir\n");
    printf("========================================\n");
}
