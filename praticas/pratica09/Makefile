CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
TARGET = main
OBJ = main.o cobertura.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o: %.c cobertura.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

test: tests/test_cobertura.c cobertura.c cobertura.h
	$(CC) $(CFLAGS) tests/test_cobertura.c cobertura.c -o tests/test_cobertura
	./tests/test_cobertura

clean:
	rm -f $(TARGET) $(TARGET).exe $(OBJ) tests/test_cobertura tests/test_cobertura.exe

.PHONY: all run test clean
