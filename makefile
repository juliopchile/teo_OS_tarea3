# Variables
CC = gcc
CFLAGS = -Wall -pthread -std=c99
TARGET = filtro
SRCS = main.c funciones.c
OBJS = $(SRCS:.c=.o)

# Regla por defecto
all: $(TARGET)

# Regla para compilar el archivo principal
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regla para compilar los archivos fuente a objetos
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para ejecutar el programa con el patrón y archivos de prueba
run: $(TARGET)
	./$(TARGET) protocol rfc959.txt rfc2068.txt rfc6353.txt rfc9293.txt

# Regla para limpiar los archivos compilados
clean:
	rm -f $(OBJS) $(TARGET)

# Indicaciones adicionales de archivos que no son objetivos
.PHONY: all run clean