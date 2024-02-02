CC = gcc
CFLAGS = -Wall -Wextra -g

TraitementS = traitementS.c
TraitementT = traitementT.c
main = main.c
HEADERS = fonctions.h

objet_S = $(TraitementS:.c=.o)
objet_T = $(TraitementT:.c=.o)
objet_main = $(main:.c=.o)

TARGET = programme_c

all: $(TARGET)

$(TARGET): $(objet_S) $(objet_T) $(objet_main)
	@$(CC) $(CFLAGS) -o $@ $^

$(objet_S): $(TraitementS) $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(objet_T): $(TraitementT) $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(objet_main): $(main) $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	@./$(TARGET) t

clean:
	@rm -f $(objet_S) $(objet_T) $(objet_main) $(TARGET)

.PHONY: all run clean
