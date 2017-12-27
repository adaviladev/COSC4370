#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>

using namespace std;

struct RGBType {
	double red;
	double green;
	double blue;
};

void saveImg(const char *filename, int width, int height, int dpi, RGBType *data) {
	int k = width * height;
	int s = 4 * k;
	int filesize = 54 + s;

	double factor = 39.375;
	int m = static_cast<int>(factor);

	int ppm = dpi * m;

	unsigned char imgFileHeader[14] = {'B', 'M', 0,0,0,0, 0,0,0,0, 54,0,0,0};
	unsigned char imgInfoHeader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0};

	imgFileHeader[2] = (unsigned char)(filesize);
	imgFileHeader[3] = (unsigned char)(filesize >> 8);
	imgFileHeader[4] = (unsigned char)(filesize >> 16);
	imgFileHeader[5] = (unsigned char)(filesize >> 24);

	imgInfoHeader[4] = (unsigned char)(width);
	imgInfoHeader[5] = (unsigned char)(width >> 8);
	imgInfoHeader[6] = (unsigned char)(width >> 16);
	imgInfoHeader[7] = (unsigned char)(width >> 24);

	imgInfoHeader[8] = (unsigned char)(height);
	imgInfoHeader[9] = (unsigned char)(height >> 8);
	imgInfoHeader[10] = (unsigned char)(height >> 16);
	imgInfoHeader[11] = (unsigned char)(height >> 24);

	imgInfoHeader[21] = (unsigned char)(s);
	imgInfoHeader[22] = (unsigned char)(s >> 8);
	imgInfoHeader[23] = (unsigned char)(s >> 16);
	imgInfoHeader[24] = (unsigned char)(s >> 24);

	imgInfoHeader[25] = (unsigned char)(ppm);
	imgInfoHeader[26] = (unsigned char)(ppm >> 8);
	imgInfoHeader[27] = (unsigned char)(ppm >> 16);
	imgInfoHeader[28] = (unsigned char)(ppm >> 24);

	imgInfoHeader[29] = (unsigned char)(ppm);
	imgInfoHeader[30] = (unsigned char)(ppm >> 8);
	imgInfoHeader[31] = (unsigned char)(ppm >> 16);
	imgInfoHeader[32] = (unsigned char)(ppm >> 24);

	FILE *fp;
	errno_t err;
	//fp = fopen(filename, "wb");


	if ((err = fopen_s(&fp, filename, "r")) != 0) {
		// File could not be opened. filepoint was set to NULL
		// error code is returned in err.
		// error message can be retrieved with strerror(err);
		fprintf(stderr, "cannot open file '%s': %s\n",
			filename);
		// If your environment insists on using so called secure
		// functions, use this instead:
	}
	else {
		fwrite(imgFileHeader, 1, 14, fp);
		fwrite(imgInfoHeader, 1, 14, fp);

		for (int i = 0; i < k; i++) {
			RGBType rgb = data[i];
			double red = (data[i].red) * 255;
			double green = (data[i].green) * 255;
			double blue = (data[i].blue) * 255;

			unsigned char color[3] = { (unsigned char)floor(blue), (unsigned char)floor(green), (unsigned char)floor(red) };
		}
	
		fclose(fp);
		// File was opened, filepoint can be used to read the stream.
	}
}

int currentPixelIndex;

int main(int argc, char *argv[])
{
	cout << "rendering..." << endl;

	int dpi = 72;
	int width = 640;
	int height = 480;
	int area = width * height;
	RGBType *pixels = new RGBType[area];

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			currentPixelIndex = y * width + x;

			pixels[currentPixelIndex].red = 23 / 255;
			pixels[currentPixelIndex].green = 222 / 255;
			pixels[currentPixelIndex].blue = 10 / 255;
			// return color
		}
	}

	saveImg("scene.bmp", width, height, dpi, pixels);

	return 0;
}