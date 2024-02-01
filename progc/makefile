CC = gcc
CFLAGS = -Wall -Wextra -g

SRC_S = traitementS.c
SRC_T = traitementT.c
SRC_MAIN = main.c
HEADERS = fonctions.h

OBJ_S = $(SRC_S:.c=.o)
OBJ_T = $(SRC_T:.c=.o)
OBJ_MAIN = $(SRC_MAIN:.c=.o)

TARGET = myprogram

all: $(TARGET)

$(TARGET): $(OBJ_S) $(OBJ_T) $(OBJ_MAIN)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_S): $(SRC_S) $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_T): $(SRC_T) $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_MAIN): $(SRC_MAIN) $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET) t

clean:
	rm -f $(OBJ_S) $(OBJ_T) $(OBJ_MAIN) $(TARGET)

.PHONY: all run clean

