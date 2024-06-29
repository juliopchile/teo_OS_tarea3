#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>

/* ----------------------------------
* Declaración de variables externas 
 --------------------------------- */

extern sem_t semaforo;


/* ----------------------------------
* Declaración de las funciones 
 --------------------------------- */

/**
 * @brief Abre un archivo en modo lectura.
 * 
 * @param filename El nombre del archivo a abrir.
 * @return FILE* Puntero al archivo abierto o NULL si ocurre un error.
 */
extern FILE* abrir_archivo_lectura(const char *filename);

/**
 * @brief Abre el archivo de salida en modo de agregar (append).
 * 
 * @return FILE* Puntero al archivo de salida o NULL si ocurre un error.
 */
extern FILE* abrir_archivo_salida();

/**
 * @brief Escribe el resultado en el archivo de salida.
 * 
 * @param salida Puntero al archivo de salida.
 * @param filename Nombre del archivo de entrada.
 * @param num_linea Número de línea donde se encontró el patrón.
 * @param linea Contenido de la línea donde se encontró el patrón.
 */
extern void escribir_resultado(FILE *salida, const char *filename, int num_linea, const char *linea);

/**
 * @brief Procesa una línea del archivo buscando el patrón y escribiendo el resultado si es encontrado.
 * 
 * @param filename Nombre del archivo de entrada.
 * @param linea La línea leída del archivo.
 * @param num_linea El número de la línea actual.
 */
extern void procesar_linea(const char *filename, const char *linea, int num_linea);

/**
 * @brief Función ejecutada por cada hilo para buscar un patrón específico en un archivo.
 * 
 * @param arg Puntero a los argumentos, que en este caso es el nombre del archivo.
 * @return void* Siempre retorna NULL.
 */
extern void* buscar_patron(void *arg);

#endif // FUNCIONES_H
