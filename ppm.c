#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ppm.h"

Pic* createPicture(int width, int height) {
	Pic* pic = malloc(sizeof *pic);
	pic->sizeX = width;
	pic->sizeY = height;
	pic->pixels = calloc(height, sizeof(Px*));

	for (int i=0; i<height; ++i) {
		pic->pixels[i] = calloc(width, sizeof(Px));
	}

	return pic;
}

int freePicture(Pic* pic) {
	for (int i=0; i<pic->sizeY; ++i) free(pic->pixels[i]);
	free(pic->pixels);
	free(pic);
	return 0;
}

Pic* loadPicture(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		perror("Unable to read file");
		return NULL;
	}

	// read PPM header
	char format[3];
	fscanf(file, "%s", format);
	if (strcmp(format, "P3") != 0) {
		printf("Invalid file format");
		fclose(file);
		return NULL;
	}
	int width, height;
	fscanf(file, "%d %d", &width, &height);
	int max_color;
	fscanf(file, "%d", &max_color);

	Pic* pic = createPicture(width, height);

	// read RGB components
	for (int y=0; y<height; ++y) {
		for (int x=0; x<width; ++x) {
			fscanf(
				file,
				"%hhu %hhu %hhu ",
				&pic->pixels[y][x].r,
				&pic->pixels[y][x].g,
				&pic->pixels[y][x].b
			);
		}
	}

	fclose(file);
	return pic;
}

int savePicture(const char* filename, Pic* pic) {
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		perror("Unable to write file");
		return 1;
	}

	// write PPM header
	fprintf(file, "P3\n");
	fprintf(file, "%d %d\n", pic->sizeX, pic->sizeY);
	fprintf(file, "255\n");

	// write RGB components
	for (int y=0; y<pic->sizeY; ++y) {
		for (int x=0; x<pic->sizeX; ++x) {
			fprintf(
				file,
				"%d %d %d  ",
				pic->pixels[y][x].r,
				pic->pixels[y][x].g,
				pic->pixels[y][x].b
			);
		}
		fprintf(file, "\n");
	}

	fclose(file);
	return 0;
}

int transformRed(Pic* pic) {
	for (int y=0; y<pic->sizeY; ++y) {
		for (int x=0; x<pic->sizeX; ++x) {
			pic->pixels[y][x].g = 0;
			pic->pixels[y][x].b = 0;
		}
	}
	return 0;
}

int transformGreen(Pic* pic) {
	for (int y=0; y<pic->sizeY; ++y) {
		for (int x=0; x<pic->sizeX; ++x) {
			pic->pixels[y][x].r = 0;
			pic->pixels[y][x].b = 0;
		}
	}
	return 0;
}

int transformBlue(Pic* pic) {
	for (int y=0; y<pic->sizeY; ++y) {
		for (int x=0; x<pic->sizeX; ++x) {
			pic->pixels[y][x].r = 0;
			pic->pixels[y][x].g = 0;
		}
	}
	return 0;
}

int transformGrayscaleAvg(Pic* pic) {
	for (int y=0; y<pic->sizeY; ++y) {
		for (int x=0; x<pic->sizeX; ++x) {
			unsigned char avg = (
				pic->pixels[y][x].r +
				pic->pixels[y][x].g +
				pic->pixels[y][x].b
			) / 3;
			pic->pixels[y][x].r = avg;
			pic->pixels[y][x].g = avg;
			pic->pixels[y][x].b = avg;
		}
	}
	return 0;
}

int transformGrayscaleMax(Pic* pic) {
	for (int y=0; y<pic->sizeY; ++y) {
		for (int x=0; x<pic->sizeX; ++x) {
			unsigned char max =
				fmax(
					fmax(pic->pixels[y][x].r, pic->pixels[y][x].g),
					pic->pixels[y][x].b
				);
			pic->pixels[y][x].r = max;
			pic->pixels[y][x].g = max;
			pic->pixels[y][x].b = max;
		}
	}
	return 0;
}

int transformSepia(Pic* pic) {
	for (int y=0; y<pic->sizeY; ++y) {
		for (int x=0; x<pic->sizeX; ++x) {
			unsigned char originalR = pic->pixels[y][x].r;
			unsigned char originalG = pic->pixels[y][x].g;
			unsigned char originalB = pic->pixels[y][x].b;

			unsigned char newR =
				0.393*originalR +
				0.769*originalG +
				0.189*originalB;
			unsigned char newG =
				0.349*originalR +
				0.686*originalG +
				0.168*originalB;
			unsigned char newB =
				0.272*originalR +
				0.534*originalG +
				0.131*originalB;

			pic->pixels[y][x].r = (newR > 255) ? 255 : newR;
			pic->pixels[y][x].g = (newG > 255) ? 255 : newG;
			pic->pixels[y][x].b = (newR > 255) ? 255 : newB;
		}
	}
	return 0;
}
