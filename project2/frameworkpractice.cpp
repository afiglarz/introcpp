// Practice project getting used to the biomeval framework
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <be_image_image.h>

int main( int argc, char** argv ) 
{
	if (argc != 2) {
		std::cerr << "Must Provide an image or a Directory\n";
		return -1;
	}

	//BiometricEvaluation::Image::Image::Image img{};

	std::string filename = argv[1];
	std::cout << filename << "\n";

	//const auto data = filename.getData();

	return 0;
}