#include <stdio.h>
#include <stdlib.h>

#include "lib.h"

int saveAsFile(const Pic* pic, const char* filename) {
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		perror("Unable to open file");
		return 1;
	}

	// write PPM header
	fprintf(file, "P3\n");
	fprintf(file, "%d %d\n", pic->sizeX, pic->sizeY);
	fprintf(file, "255\n");

	// write RGB triplets
	for (int y=0; y<pic->sizeY; ++y) {
		for (int x=0; x<pic->sizeX; ++x) {
			Px p = pic->pixels[y][x];
			fprintf(file, "%d %d %d ", p.r, p.g, p.b);
		}
		fprintf(file, "\n");
	}

	fclose(file);
	return 0;
}
