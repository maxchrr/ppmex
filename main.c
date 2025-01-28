#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ppm.h"

int main(int argc, char** argv) {
	/*int width = 940;
	int height = 3;
	Pic* pic = createPicture(width, height);

	srand(time(NULL));
	for (int y=0; y<height; ++y) {
		for (int x=0; x<width; ++x) {
			pic->pixels[y][x].r = rand() % 256;
			pic->pixels[y][x].g = rand() % 256;
			pic->pixels[y][x].b = rand() % 256;
		}
	}

	savePicture("random.ppm", pic);*/

	Pic* npic = loadPicture("bclc.ppm");

	transformBlue(npic);

	savePicture("bclc_blue.ppm", npic);

	//freePicture(pic);
	freePicture(npic);
	return 0;
}
