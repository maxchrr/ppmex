#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ppm.h"

int main(int argc, char* argv[]) {
	int width, height;

	if (argc == 3) {
		width = strtol(argv[1], NULL, 10);
		height = strtol(argv[2], NULL, 10);
	}
	else {
		width = 8;
		height = 8;
	}

	Pic* pic = createPicture(width, height);

	srand(time(NULL));
	for (int y=0; y<height; ++y) {
		for (int x=0; x<width; ++x) {
			pic->pixels[y][x].r = rand() % 256;
			pic->pixels[y][x].g = rand() % 256;
			pic->pixels[y][x].b = rand() % 256;
		}
	}

	savePicture("random.ppm", pic);

	freePicture(pic);
	return EXIT_SUCCESS;
}
