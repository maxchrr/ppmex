CC = clang
CFLAGS = -Wall -Wextra -pedantic -std=c99 -I.

SRC = ppm.c main.c
OBJ = $(SRC:.c=.so)
EXEC = ppmex

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) -o $@ $^

%.so: $(SRC)
	$(CC) $(CFLAGS) -fpic -shared -c $< -o $@

clean:
	@rm -f *.so $(EXEC)

.PHONY: all clean
