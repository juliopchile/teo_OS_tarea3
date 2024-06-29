#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "funciones.h"

/* Definición del semáforo */ 
sem_t semaforo;

void* buscar_patron(void *arg) {
    /* Inicializar varables de estado y sanity check */
    char *filename = (char *)arg;
    FILE *file = abrir_archivo_lectura(filename);
    if (!file) {
        return NULL;
    }

    /* Leer linea por linea del archivo */
    char linea[256];
    int num_linea = 1;
    while (fgets(linea, sizeof(linea), file)) {
        /* Buscar el "patrón" en la línea y procesarla acorde*/
        procesar_linea(filename, linea, num_linea);
        num_linea++;
    }
    fclose(file);
    return NULL;
}

int main(int argc, char *argv[]) {
    /* Checkear entrada válida */
    if (argc < 3) {
        fprintf(stderr, "Uso: %s patrón archivo1 archivo2 ... archivoN\n", argv[0]);
        return 1;
    }

    /* Inicializar variables de estado y semáforo*/
    sem_init(&semaforo, 0, 1);
    int num_archivos = argc - 2;
    pthread_t hilos[num_archivos];

    /* Crear los hilos */
    for (int i = 0; i < num_archivos; i++)
        pthread_create(&hilos[i], NULL, buscar_patron, argv[i + 2]);

    /* Esperar a que los hilos terminen */
    for (int i = 0; i < num_archivos; i++)
        pthread_join(hilos[i], NULL);

    /* Destruir semáforo */
    sem_destroy(&semaforo);

    /* Terminar programa */
    return 0;
}