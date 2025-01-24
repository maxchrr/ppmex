#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ppm.h"

int main(int argc, char** argv) {
	/*int width = 256;
	int height = 256;
	Pic* pic = createPicture(width, height);

	for (int y=0; y<height; ++y) {
		for (int x=0; x<width; ++x) {
			pic->pixels[y][x].r = 255;
			pic->pixels[y][x].g = 0;
			pic->pixels[y][x].b = 0;
		}
	}

	savePicture("red.ppm", pic);*/

	srand(time(NULL));
	int width = rand() % 256;
	int height = rand() % 256;
	Pic* pic = loadPicture("red.ppm");

	for (int y=0; y<height; ++y) {
		for (int x=0; x<width; ++x) {
			pic->pixels[y][x].r = rand() % 256;
			pic->pixels[y][x].g = rand() % 256;
			pic->pixels[y][x].b = rand() % 256;
		}
	}

	transformRed(pic);
	transformSepia(pic);

	savePicture("red_alt.ppm", pic);

	freePicture(pic);
	return 0;
}
