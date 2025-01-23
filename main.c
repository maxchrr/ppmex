#include <stdio.h>
#include <stdlib.h>

#include "lib.h"

int main(int argc, char** argv) {
	int sizeX = 128;
	int sizeY = 128;

	Pic pic;
	pic.sizeX = sizeX;
	pic.sizeY = sizeY;
	pic.pixels = calloc(sizeY, sizeof(Px*));
	for (int i=0; i<sizeY; ++i) pic.pixels[i] = calloc(sizeX, sizeof(Px*));

	for (int y=0; y<sizeY; ++y) {
		for (int x=0; x<sizeX; ++x) {
			// full red picture
			pic.pixels[y][x].r = 255;
			pic.pixels[y][x].g = 0;
			pic.pixels[y][x].b = 0;
		}
	}

	saveAsFile(&pic, "red_picture.ppm");

	for (int i=0; i<sizeY; ++i) free(pic.pixels[i]);
	free(pic.pixels);

	return 0;
}
