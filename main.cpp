
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

int main() {

	int width, height, channels;
	unsigned char* data = stbi_load("image.png", &width, &height, &channels, 0);

	std::cout << "Hello World\n";
	return 0;
}

