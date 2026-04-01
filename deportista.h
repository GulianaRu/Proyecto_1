#ifndef DEPORTISTA_H
#define DEPORTISTA_H

#define MAX_NOMBRE 50

typedef struct {
    int id;
    char nombre[MAX_NOMBRE];
    char equipo[MAX_NOMBRE];
    float puntaje;
    int competencias;
} Deportista;

#endif