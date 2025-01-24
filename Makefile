SRC = main.c lib.c

.PHONY: all ppmex clean

all: ppmex

ppmex: $(SRC)
	mkdir -p bin
	clang -o bin/$@ -Wall -pedantic -std=c99 $^

clean:
	@rm -rf bin
