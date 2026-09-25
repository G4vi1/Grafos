CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

OBJS = grafo_matriz.o grafo_lista.o main.o
TARGET = pratica01

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

grafo_matriz.o: grafo_matriz.c grafo_matriz.h
	$(CC) $(CFLAGS) -c grafo_matriz.c

grafo_lista.o: grafo_lista.c grafo_lista.h
	$(CC) $(CFLAGS) -c grafo_lista.c

main.o: main.c grafo_matriz.h grafo_lista.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean