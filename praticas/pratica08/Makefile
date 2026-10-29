# Compilador C utilizado para transformar os fontes em objetos e executavel.
CC = gcc
# Habilita avisos, trata avisos como erros e seleciona o padrao C11.
CFLAGS = -Wall -Wextra -Werror -std=c11

# Nome do executavel e objetos gerados a partir dos quatro arquivos .c.
TARGET = main
OBJ = main.o agm.o grafo_lista.o grafo_matriz.o

# Alvo padrao: construir o executavel.
all: $(TARGET)

# Liga os objetos. $@ representa o nome do alvo (main).
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

# Compila cada .c separadamente. $< e o primeiro requisito (o fonte).
# Mudancas nos cabecalhos tambem provocam recompilacao.
%.o: %.c agm.h grafo_lista.h grafo_matriz.h
	$(CC) $(CFLAGS) -c $< -o $@

# Garante que o executavel esteja atualizado antes de executa-lo.
run: $(TARGET)
	./$(TARGET)

# Remove somente o executavel e os objetos gerados pela compilacao.
clean:
	rm -f $(TARGET) $(OBJ)

# Estes nomes representam acoes, mesmo que existam arquivos com esses nomes.
.PHONY: all run clean
