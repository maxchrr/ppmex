#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"

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
			fscanf(file, "%d %d %d ", &pic.pixels[y][x].r, &pic.pixels[y][x].g, &pic.pixels[y][x].b);
		}
	}

	fclose(file);
	return pic;
}
