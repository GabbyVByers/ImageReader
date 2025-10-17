
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <iomanip>
#include <fstream>

std::string short_to_hex_string(unsigned short value) {
	std::ostringstream oss;
	oss << std::uppercase << std::hex << std::setw(4) << std::setfill('0') << value;
	return oss.str();
}

unsigned short build_pixel(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	unsigned short color = 0;
	color |= (((unsigned short)r & 0x00F0) >> 4) << 12;
	color |= (((unsigned short)g & 0x00F0) >> 4) << 8;
	color |= (((unsigned short)b & 0x00F0) >> 4) << 4;
	color |= (((unsigned short)a & 0x00F0) >> 4);
	return color;
}

std::string uint_to_hex_string(unsigned int color) {
	return "";
}

int main() {

	int width, height, channels;
	unsigned char* data = stbi_load("image.png", &width, &height, &channels, 0);
	assert(channels == 4);

	std::vector<std::vector<unsigned short>> image;

	for (int y = 0; y < height; y++) {
		unsigned char* pixel_row = &data[(width * channels * y)];
		std::vector<unsigned short> image_row;
		for (int x = 0; x < width; x++) {
			unsigned char* pixel = &pixel_row[(channels * x)];
			unsigned char r = pixel[0];
			unsigned char g = pixel[1];
			unsigned char b = pixel[2];
			unsigned char a = pixel[3];
			unsigned short true_pixel = build_pixel(r, g, b, a);
			image_row.push_back(true_pixel);
		}
		image.push_back(image_row);
	}

	std::ofstream output_hex("video_memory.hex");
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			output_hex << (short_to_hex_string(image[x][y]) + "\n");
		}
	}
	output_hex.close();

	return 0;
}

