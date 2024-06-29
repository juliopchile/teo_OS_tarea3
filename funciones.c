#include "funciones.h"

/* ----------------------------------
* Definición de variables externas 
 --------------------------------- */

extern sem_t semaforo;


/* ----------------------------------
* Definición de las funciones
 --------------------------------- */

FILE* abrir_archivo_lectura(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error abriendo el archivo");
    }
    return file;
}

FILE* abrir_archivo_salida() {
    FILE *salida = fopen("salida.txt", "a");
    if (!salida) {
        perror("Error abriendo el archivo de salida");
    }
    return salida;
}

void escribir_resultado(FILE *salida, const char *filename, int num_linea, const char *linea) {
    fprintf(salida, "%s:%d:%s", filename, num_linea, linea);
}

void procesar_linea(const char *filename, const char *linea, int num_linea) {
    // Check si la palabra protocol está en la linea
    if (strstr(linea, "protocol")) {
        // ? Obtener semáforo (sección crítica)
        sem_wait(&semaforo);
        FILE *salida = abrir_archivo_salida();
        if (salida) {
            // ! Escribir en el archivo salida.txt
            escribir_resultado(salida, filename, num_linea, linea);
            fclose(salida);
            // ! Cerrar el archivo salida.txt
        }
        sem_post(&semaforo);
        // ? Devolver el semáforo (termina seción crítica)
    }
}