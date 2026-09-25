CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

OBJS = grafo_lista.o busca_largura.o busca_profundidade.o main.o
TARGET = pratica02

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

grafo_lista.o: grafo_lista.c grafo_lista.h
	$(CC) $(CFLAGS) -c grafo_lista.c

busca_largura.o: busca_largura.c busca_largura.h grafo_lista.h
	$(CC) $(CFLAGS) -c busca_largura.c

busca_profundidade.o: busca_profundidade.c busca_profundidade.h grafo_lista.h
	$(CC) $(CFLAGS) -c busca_profundidade.c

main.o: main.c grafo_lista.h busca_largura.h busca_profundidade.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean