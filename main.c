#include <stdio.h>
#include <stdlib.h>

#include "lib.h"

int main(int argc, char** argv) {
	Pic rdm = loadAsPic("random.ppm");
	transformSepia(&rdm);
	saveAsFile(&rdm, "random.transform.sepia.ppm");

	freePicture(&rdm);

	return 0;
}
