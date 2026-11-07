CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
TARGET = main
OBJ = main.o cobertura.o cobertura_grafos.o grafo_matriz.o grafo_lista.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o: %.c cobertura.h grafo_matriz.h grafo_lista.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

test: tests/test_cobertura.c cobertura.c cobertura_grafos.c grafo_matriz.c grafo_lista.c cobertura.h grafo_matriz.h grafo_lista.h
	$(CC) $(CFLAGS) tests/test_cobertura.c cobertura.c cobertura_grafos.c grafo_matriz.c grafo_lista.c -o tests/test_cobertura
	./tests/test_cobertura

clean:
	rm -f $(TARGET) $(TARGET).exe $(OBJ) tests/test_cobertura tests/test_cobertura.exe

.PHONY: all run test clean
