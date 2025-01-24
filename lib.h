// Pixel definition
struct Pixel {
	unsigned char r;
	unsigned char g;
	unsigned char b;
};
typedef struct Pixel Px;

// Picture definitiion
struct Picture {
	Px** pixels;
	int sizeX;
	int sizeY;
};
typedef struct Picture Pic;

Pic loadAsPic(const char* filename);
int saveAsFile(const Pic* pic, const char* filename);
int transformRed(const Pic* pic);
int transformGreen(const Pic* pic);
int transformBlue(const Pic* pic);
int transformGrayscale(const Pic* pic);
int transformGrayscaleAlt(const Pic* pic);
int transformSepia(const Pic* pic);
