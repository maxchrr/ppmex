#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "lib.h"

Pic loadAsPic(const char* filename) {
	Pic pic = {NULL, 0, 0};
	int max_color;

	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		perror("Unable to read file");
		return pic;
	}

	// read PPM header
	char format[3];
	fscanf(file, "%s", format);
	if (strcmp(format, "P3") != 0) {
		printf("Invalid file format");
		fclose(file);
		return pic;
	}
	fscanf(file, "%d %d", &pic.sizeX, &pic.sizeY);
	fscanf(file, "%d", &max_color);

	pic.pixels = malloc(pic.sizeY * sizeof(Px*));
	for (int i=0; i<pic.sizeY; ++i) {
		pic.pixels[i] = malloc(pic.sizeX * sizeof(Px));
	}

	// read RGB triplets
	for (int y=0; y<pic.sizeY; ++y) {
		for (int x=0; x<pic.sizeX; ++x) {
			fscanf(file, "%hhu %hhu %hhu ", &pic.pixels[y][x].r, &pic.pixels[y][x].g, &pic.pixels[y][x].b);
		}
	}

	fclose(file);
	return pic;
}

int saveAsFile(const Pic* pic, const char* filename) {
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		perror("Unable to write file");
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

int transformRed(const Pic* pic) {
	for (int y=0; y<pic->sizeY; ++y) {
		for (int x=0; x<pic->sizeX; ++x) {
			pic->pixels[y][x].g = pic->pixels[y][x].b = 0;
		}
	}
	return 0;
}

int transformGreen(const Pic* pic) {
	for (int y=0; y<pic->sizeY; ++y) {
		for (int x=0; x<pic->sizeX; ++x) {
			pic->pixels[y][x].r = pic->pixels[y][x].b = 0;
		}
	}
	return 0;
}

int transformBlue(const Pic* pic) {
	for (int y=0; y<pic->sizeY; ++y) {
		for (int x=0; x<pic->sizeX; ++x) {
			pic->pixels[y][x].r = pic->pixels[y][x].g = 0;
		}
	}
	return 0;
}

int transformGrayscale(const Pic* pic) {
	for (int y=0; y<pic->sizeY; ++y) {
		for (int x=0; x<pic->sizeX; ++x) {
			int sum = pic->pixels[y][x].r + pic->pixels[y][x].g + pic->pixels[y][x].b;
			pic->pixels[y][x].r = pic->pixels[y][x].g = pic->pixels[y][x].b = sum/3;
		}
	}
	return 0;
}

int transformGrayscaleAlt(const Pic* pic) {
	for (int y=0; y<pic->sizeY; ++y) {
		for (int x=0; x<pic->sizeX; ++x) {
			double max = fmax(fmax(pic->pixels[y][x].r,pic->pixels[y][x].g),pic->pixels[y][x].b);
			pic->pixels[y][x].r = pic->pixels[y][x].g = pic->pixels[y][x].b = max;
		}
	}
	return 0;
}

int transformSepia(const Pic* pic) {
	for (int y=0; y<pic->sizeY; ++y) {
		for (int x=0; x<pic->sizeX; ++x) {
			pic->pixels[y][x].r = 0.393*pic->pixels[y][x].r + 0.769*pic->pixels[y][x].g + 0.189*pic->pixels[y][x].b;
			pic->pixels[y][x].g = 0.349*pic->pixels[y][x].r + 0.686*pic->pixels[y][x].g + 0.168*pic->pixels[y][x].b;
			pic->pixels[y][x].b = 0.272*pic->pixels[y][x].r + 0.534*pic->pixels[y][x].g + 0.131*pic->pixels[y][x].b;
		}
	}
	return 0;
}
