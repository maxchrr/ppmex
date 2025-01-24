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

Pic loadAsPic(const char* filename);
int saveAsFile(const Pic* pic, const char* filename);
int transformRed(const Pic* pic);
int transformGreen(const Pic* pic);
int transformBlue(const Pic* pic);
int transformGrayscale(const Pic* pic);
int transformGrayscaleAlt(const Pic* pic);
int transformSepia(const Pic* pic);
