/* Single pixel definition using three unsigned chars (each ranging from
 * 0 to 255) for the Red, Green, and Blue components of the color.
 */
struct Pixel {
	unsigned char r;
	unsigned char g;
	unsigned char b;
};
typedef struct Pixel Px;

/* Picture definition as a 2D array of pixels (Px** pixels), with sizeX
 * and sizeY representing the width and height of the image, respectively.
 */
struct Picture {
	Px** pixels;
	int sizeX;
	int sizeY;
};
typedef struct Picture Pic;

Pic* createPicture(int width, int height);
int freePicture(Pic* pic);
Pic* loadPicture(const char* filename);
int savePicture(const char* filename, Pic* pic);
int transformRed(Pic* pic);
int transformGreen(Pic* pic);
int transformBlue(Pic* pic);
int transformGrayscaleAvg(Pic* pic);
int transformGrayscaleMax(Pic* pic);
int transformSepia(Pic* pic);
int transformBlur(Pic *pic);
