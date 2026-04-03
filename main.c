#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funciones.h"
#include "interfaz.h"
#include "deportista.h"

int main(void) {
    char linea[256];
    char comando[10], arg1[100];
    Deportista *mis_deportistas = NULL; // El arreglo empieza vacío
    int cantidad_actual = 0;

    printf("%sBienvenido al sistema de deportistas%s\n", VERDE, RESET);
    printf("%sPara obtener ayuda, escriba 'help'%s\n", AMARILLO, RESET);
    while (1) {
        printf("%s> %s", MORADO, RESET);

        if (fgets(linea, sizeof(linea), stdin) == NULL) {
            finalizar_programa();
            break;
        }

        linea[strcspn(linea, "\n")] = 0;  // Elimina el salto de linea
        int num_args = sscanf(linea, "%s %s", comando, arg1);

        if (strcmp(comando, "help") == 0) {
            help();

        } else if (strcmp(comando, "generar") == 0) {
            if (num_args < 2) {
            printf("%sUso: generar <n>%s\n", ROJO, RESET);
        } else {
            cantidad_actual = atoi(arg1);
            // Liberar memoria si ya existía algo previo
            if (mis_deportistas != NULL) free(mis_deportistas); 
            
            generarDatos(&mis_deportistas, &cantidad_actual);
            guardarCSV(mis_deportistas, cantidad_actual, "deportistas.csv");
        }
        } 
        else if (strcmp(comando, "cargar") == 0) {
            if (num_args < 2) {
                printf("%sUso: cargar <nombre_archivo.csv>%s\n", ROJO, RESET);
            } else {
                // Liberamos si ya había algo cargado
                if (mis_deportistas != NULL) free(mis_deportistas);
                
                cargarCSV(&mis_deportistas, &cantidad_actual, arg1);
            }
        } 
        else if (strcmp(comando, "ordenar") == 0) {
            if (num_args < 2) {
                printf("%sUso: ordenar <bubble|insertion|selection|cocktail>%s\n", ROJO, RESET);
            } else {
                if (strcmp(arg1, "bubble") == 0) {
                    bubbleSort(mis_deportistas, cantidad_actual);
                } else if (strcmp(arg1, "insertion") == 0) {
                    insertionSort(mis_deportistas, cantidad_actual);
                } else if (strcmp(arg1, "selection") == 0) {
                    selectionSort(mis_deportistas, cantidad_actual);
                } else if (strcmp(arg1, "cocktail") == 0) {
                    cocktailSort(mis_deportistas, cantidad_actual);
                } else {
                    printf("%sAlgoritmo no reconocido.%s\n", ROJO, RESET);
                }
            }
        }  
        else if (strcmp(comando, "busqueda") == 0) {
            if (num_args < 2) {
                printf("%sUso: busqueda <secuencial|binaria>%s\n", ROJO, RESET);
            } else {
                char nombre[MAX_NOMBRE];
                printf("%sIngrese el nombre a buscar: %s", CYAN, RESET);
                
                // Limpiamos el buffer por si quedo un \n de antes
                fflush(stdin); 
                fgets(nombre, sizeof(nombre), stdin);
                nombre[strcspn(nombre, "\n")] = 0; // Quitar el enter

                if (strcmp(arg1, "secuencial") == 0) {
                    busquedaSecuencial(mis_deportistas, cantidad_actual, nombre);
                } else if (strcmp(arg1, "binaria") == 0) {
                    printf("%s[INFO] Asegurese que los datos esten ordenados.%s\n", AMARILLO, RESET);
                    busquedaBinaria(mis_deportistas, cantidad_actual, nombre);
                }
            }
        }
        else if (strcmp(comando, "ranking") == 0 ) {
            //

        } else if (strcmp(comando, "all") == 0 ) {
            mostrarTodo(mis_deportistas, cantidad_actual);

        } else if (strcmp(comando, "exit") == 0) {
            finalizar_programa();
            break;

        } else {
            printf("%sComando o argumento invalido. Revise la sintaxis.%s\n", ROJO, RESET);
        }
    }

    return 0;
}