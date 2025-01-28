CC=clang
CFLAGS=-O3 -g -Wall -pedantic -std=c99

.PHONY: all ppmex libppm.so clean

all: ppmex

ppmex: main.c libppm.so
	mkdir -p bin
	$(CC) -o bin/$@ $(CFLAGS) -lppm -L. main.c

libppm.so: ppm.c
	$(CC) -o $@ $(CFLAGS) -fpic -shared $^

clean:
	@rm -rf bin *.so*
