#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "deportista.h"
#include "funciones.h"
#include "interfaz.h"


void finalizar_programa() { 
    printf("%sLimpiando cache y saliendo del programa...\n%s", AMARILLO, RESET);
    exit(0);
}

void help() {
    printf("%sComandos disponibles:%s\n", CYAN, RESET);
    printf("%s- generar <n>: %sGenera un archivo con n deportistas aleatorios.\n", VERDE, RESET);
    printf("%s- cargar <archivo>: %sCarga los datos de deportistas desde el archivo especificado.\n", VERDE, RESET);
    printf("%s- busqueda <nombre>: %sBusca y muestra la información del deportista con el nombre dado.\n", VERDE, RESET);
    printf("%s- ranking <deporte>: %sMuestra el ranking de los deportistas en el deporte especificado.\n", VERDE, RESET);
    printf("%s- all: %sMuestra la información de todos los deportistas cargados.\n", VERDE, RESET);
    printf("%s- exit: %sSale del programa.\n", VERDE, RESET);
}

void generarDatos(Deportista **arreglo, int *cantidad) {
    if (*cantidad <= 0) return;

    *arreglo = (Deportista *)malloc((*cantidad) * sizeof(Deportista));
    if (*arreglo == NULL) return;

    const char *equipos_locales[] = EQUIPOS_INIT;
    srand(time(NULL)); 

    for (int i = 0; i < *cantidad; i++) {
        (*arreglo)[i].id = i + 1;
        
        // --- LÓGICA DE NOMBRES ALEATORIOS (Letras al azar) ---
        int largo_nombre = 5; // Puedes hacer que varíe entre 4 y 8 si quieres
        for (int j = 0; j < largo_nombre; j++) {
            // Genera una letra mayúscula aleatoria (A-Z)
            // 'A' es 65 y hay 26 letras en el alfabeto inglés
            (*arreglo)[i].nombre[j] = 'A' + (rand() % 26);
        }
        (*arreglo)[i].nombre[largo_nombre] = '\0'; // ¡IMPORTANTE! Cerrar el string
        // ------------------exit----------------------------------

        strcpy((*arreglo)[i].equipo, equipos_locales[rand() % NUM_EQUIPOS]);
        (*arreglo)[i].puntaje = (float)(rand() % 1001) / 10.0;
        (*arreglo)[i].competencias = (rand() % 15) + 1;
    }

    printf("%sSe han generado %d deportistas con nombres aleatorios (ej: %s).%s\n", 
           VERDE, *cantidad, (*arreglo)[0].nombre, RESET);
}

void guardarCSV(Deportista *arreglo, int cantidad, const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL) {
        printf("%sNo se pudo crear el archivo %s%s\n", ROJO, nombreArchivo, RESET);
        return;
    }

    // Cabecera del CSV
    fprintf(archivo, "ID,Nombre,Equipo,Puntaje,Competencias\n");

    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%d,%s,%s,%.2f,%d\n", 
                arreglo[i].id, 
                arreglo[i].nombre, 
                arreglo[i].equipo, 
                arreglo[i].puntaje, 
                arreglo[i].competencias);
    }

    fclose(archivo);
    printf("%sDatos guardados en %s%s\n", AMARILLO, nombreArchivo, RESET);
}

void cargarCSV(Deportista **arreglo, int *cantidad, const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("%sError: No se pudo abrir el archivo %s%s\n", ROJO, nombreArchivo, RESET);
        return;
    }

    char linea[256];
    // Leer y descartar la cabecera (ID,Nombre,Equipo...)
    fgets(linea, sizeof(linea), archivo);

    // Contar cuántas líneas tiene el archivo para saber cuánto malloc pedir
    int contador = 0;
    while (fgets(linea, sizeof(linea), archivo)) contador++;
    
    *cantidad = contador;
    rewind(archivo); // Volver al inicio del archivo
    fgets(linea, sizeof(linea), archivo); // Saltar la cabecera de nuevo

    // Pedir memoria
    *arreglo = (Deportista *)malloc((*cantidad) * sizeof(Deportista));

    // Leer los datos línea por línea
    for (int i = 0; i < *cantidad; i++) {
        fgets(linea, sizeof(linea), archivo);
        // sscanf con formato CSV (separado por comas)
        sscanf(linea, "%d,%[^,],%[^,],%f,%d", 
               &(*arreglo)[i].id, 
               (*arreglo)[i].nombre, 
               (*arreglo)[i].equipo, 
               &(*arreglo)[i].puntaje, 
               &(*arreglo)[i].competencias);
    }

    fclose(archivo);
    printf("%sSe cargaron %d deportistas desde %s%s\n", VERDE, *cantidad, nombreArchivo, RESET);
}

void mostrarTodo(Deportista *arreglo, int cantidad) {
    if (arreglo == NULL || cantidad <= 0) {
        printf("%sNo hay deportistas cargados. Usa 'generar' o 'cargar' primero.%s\n", AMARILLO, RESET);
        return;
    }

    // Encabezado de la tabla con colores
    printf("\n%s%-5s %-15s %-15s %-10s %-5s%s\n", CYAN, "ID", "NOMBRE", "EQUIPO", "PUNTAJE", "COMP.", RESET);
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < cantidad; i++) {
        // %-15s significa: reserva 15 espacios y alinea a la izquierda (-)
        printf("%-5d %-15s %-15s %-10.2f %-5d\n", 
               arreglo[i].id, 
               arreglo[i].nombre, 
               arreglo[i].equipo, 
               arreglo[i].puntaje, 
               arreglo[i].competencias);
    }
    printf("------------------------------------------------------------\n");
    printf("%sTotal: %d deportistas.%s\n\n", VERDE, cantidad, RESET);
}


// ORDENAMIENTO

void bubbleSort(Deportista *a, int n) {
    int i, j, intercambio;
    for (i = 0; i < n - 1; i++) {
        intercambio = 0;
        for (j = 0; j < n - i - 1; j++) {
            if (strcmp(a[j].nombre, a[j+1].nombre) > 0) {
                Deportista temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
                intercambio = 1;
            }
        }
        if (intercambio == 0) break; // Optimización
    }
    printf("%sOrdenado con Bubble Sort (Optimizado).%s\n", VERDE, RESET);
}

void selectionSort(Deportista *a, int n, int criterio) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            int comparacion = 0;
            if (criterio == 1) comparacion = (a[j].id < a[min_idx].id);
            else if (criterio == 2) comparacion = (strcmp(a[j].nombre, a[min_idx].nombre) < 0);
            else if (criterio == 3) comparacion = (a[j].puntaje < a[min_idx].puntaje);
            
            if (comparacion) min_idx = j;
        }
        if (min_idx != i) {
            Deportista temp = a[min_idx];
            a[min_idx] = a[i];
            a[i] = temp;
        }
    }
}

void insertionSort(Deportista *a, int n) {
    for (int i = 1; i < n; i++) {
        Deportista clave = a[i];
        int j = i - 1;
        while (j >= 0 && strcmp(a[j].nombre, clave.nombre) > 0) {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = clave;
    }
    printf("%sOrdenado con Insertion Sort.%s\n", VERDE, RESET);
}

void cocktailSort(Deportista *a, int n) {
    int intercambio = 1;
    int inicio = 0;
    int fin = n - 1;
    while (intercambio) {
        intercambio = 0;
        for (int i = inicio; i < fin; ++i) {
            if (strcmp(a[i].nombre, a[i + 1].nombre) > 0) {
                Deportista temp = a[i];
                a[i] = a[i+1];
                a[i+1] = temp;
                intercambio = 1;
            }
        }
        if (!intercambio) break;
        intercambio = 0;
        --fin;
        for (int i = fin - 1; i >= inicio; --i) {
            if (strcmp(a[i].nombre, a[i + 1].nombre) > 0) {
                Deportista temp = a[i];
                a[i] = a[i+1];
                a[i+1] = temp;
                intercambio = 1;
            }
        }
        ++inicio;
    }
    printf("%sOrdenado con Cocktail Shaker Sort.%s\n", VERDE, RESET);
}

// 1. Búsqueda Secuencial (Estándar)
// Recorre el arreglo de principio a fin. Complejidad: O(n)
void busquedaSecuencial(Deportista *arreglo, int cantidad, const char *nombreBuscar) {
    if (arreglo == NULL || cantidad == 0) {
        printf("%sError: No hay datos cargados.%s\n", ROJO, RESET);
        return;
    }

    int encontrado = 0;
    for (int i = 0; i < cantidad; i++) {
        if (strcmp(arreglo[i].nombre, nombreBuscar) == 0) {
            printf("\n%s[RESULTADO ENCONTRADO - SECUENCIAL]%s\n", VERDE, RESET);
            printf("ID: %-5d | Nombre: %-15s | Equipo: %-15s | Puntaje: %.2f\n", 
                   arreglo[i].id, arreglo[i].nombre, arreglo[i].equipo, arreglo[i].puntaje);
            encontrado = 1;
            break; // Terminamos al hallar el primero
        }
    }

    if (!encontrado) {
        printf("%sNo se encontro ningun deportista con el nombre '%s'.%s\n", ROJO, nombreBuscar, RESET);
    }
}

// 2. Búsqueda Binaria (Versión Iterativa)
// Requiere que el arreglo esté ordenado previamente. Complejidad: O(log n)
void busquedaBinaria(Deportista *arreglo, int cantidad, const char *nombreBuscar) {
    if (arreglo == NULL || cantidad == 0) {
        printf("%sError: No hay datos cargados.%s\n", ROJO, RESET);
        return;
    }

    int inicio = 0;
    int fin = cantidad - 1;
    int encontrado = 0;

    while (inicio <= fin) {
        int medio = inicio + (fin - inicio) / 2;
        int comparacion = strcmp(arreglo[medio].nombre, nombreBuscar);

        if (comparacion == 0) {
            printf("\n%s[RESULTADO ENCONTRADO - BINARIA]%s\n", VERDE, RESET);
            printf("ID: %-5d | Nombre: %-15s | Equipo: %-15s | Puntaje: %.2f\n", 
                   arreglo[medio].id, arreglo[medio].nombre, arreglo[medio].equipo, arreglo[medio].puntaje);
            encontrado = 1;
            break;
        }

        if (comparacion < 0) {
            inicio = medio + 1; // El nombre está en la mitad derecha
        } else {
            fin = medio - 1;    // El nombre está en la mitad izquierda
        }
    }

    if (!encontrado) {
        printf("%sNo se encontro a '%s'. Asegurate de haber ordenado el arreglo primero.%s\n", ROJO, nombreBuscar, RESET);
    }
}

// 1. Algoritmo Fisher-Yates para mezclar registros (Requisito pág. 2)
void mezclarDatos(Deportista *arreglo, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Deportista temp = arreglo[i];
        arreglo[i] = arreglo[j];
        arreglo[j] = temp;
    }
}

// 2. Función de Ranking (Requisito pág. 2)
void mostrarRanking(Deportista *arreglo, int cantidad, int n_tops) {
    if (arreglo == NULL || cantidad <= 0) return;
    
    // Para el ranking debemos ordenar por puntaje de mayor a menor
    // Usaremos una adaptación de Selection Sort para no alterar el orden principal
    Deportista *copia = (Deportista *)malloc(cantidad * sizeof(Deportista));
    memcpy(copia, arreglo, cantidad * sizeof(Deportista));

    for (int i = 0; i < cantidad - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < cantidad; j++) {
            if (copia[j].puntaje > copia[max_idx].puntaje) max_idx = j;
        }
        Deportista temp = copia[max_idx];
        copia[max_idx] = copia[i];
        copia[i] = temp;
    }

    printf("\n%s--- RANKING TOP %d DEPORTISTAS ---%s\n", CYAN, n_tops, RESET);
    for (int i = 0; i < n_tops && i < cantidad; i++) {
        printf("%d. %-15s - Puntaje: %.2f - Equipo: %s\n", 
               i + 1, copia[i].nombre, copia[i].puntaje, copia[i].equipo);
    }
    free(copia);
}