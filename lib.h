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

int saveAsFile(const Pic* pic, const char* filename);
