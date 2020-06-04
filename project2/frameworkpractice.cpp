// Practice project getting used to the biomeval framework
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "frameworkpractice.h"

//namespace BE = BiometricEvaluation;

std::shared_ptr<BiometricEvaluation::Image::Image>
myOpenImage(
	std::string s)
	{	
		return BiometricEvaluation::Image::Image::openImage(s);	
	}



int main( int argc, char** argv ) 
{
	if (argc != 2) {
		std::cerr << "Must Provide an image or a Directory\n";
		return -1;
	}
	
	// Get Filename
	std::string filename = argv[1];

	// Open the Image (Using function I wrote that just calls openImage())
	auto img = myOpenImage(filename).get();

	// Get Compression Algorithm from image
	BiometricEvaluation::Image::CompressionAlgorithm compalg = 
	(*img).getCompressionAlgorithm();

	// Get Resolution of Image 
	BiometricEvaluation::Image::Resolution res = 
	(*img).getResolution();

	// Get Data of Image ------- Figure out how to express this ------------
	BiometricEvaluation::Memory::uint8Array data = 
	(*img).getData();

	// Get Dimensions of data
	BiometricEvaluation::Image::Size dims = 
	(*img).getDimensions();

	// Print out Filename
	std::cout << "Filename: " << filename << "\n";

	// Print out Compression Algorithm - have to cast it because it is an enum
	std::cout << "Compression Algorithm: " << 
	static_cast<std::underlying_type
	<BiometricEvaluation::Image::CompressionAlgorithm>::type>(compalg) << "\n";

	// Print out Resolution of Image
	std::cout << "Resolution of Image: " << res << "\n";

	// Print out Dimensions of Image
	std::cout << "Dimensions of Image: " << dims << "\n";

	return 0;
}