// Pixel definition
struct Pixel {
	unsigned char r;
	unsigned char v;
	unsigned char b;
};
typedef struct Pixel pixel;

// Picture definitiion
struct Picture {
	Pixel** pixels;
	int sizeX;
	int sizeY;
};
typedef struct Picture picture;
