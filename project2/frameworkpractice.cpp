// Practice project getting used to the biomeval framework

// Current Issues:
// - If you give it a directory, make sure you give the ending "/" character,
// - the current implementation checks for that to recognize a directory.

#include <dirent.h>
#include <sys/types.h>

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "frameworkpractice.h"

namespace BE = BiometricEvaluation;

// Function that generates all the information to a string that you can
// then print to stdout
std::string 
generateInfo(
	std::string filename) 
{
	namespace BE = BiometricEvaluation;
	
	std::string output{};

	auto img = BE::Image::Image::openImage(filename).get();
	
	// Get Compression Algorithm from image
	BE::Image::CompressionAlgorithm compalg = 
	(*img).getCompressionAlgorithm();

	// Get Resolution of Image 
	BE::Image::Resolution res = (*img).getResolution();

	// Get Data of Image -- Not Raw -- Is encoded
	BE::Memory::uint8Array data = (*img).getData();

	// Get Colordepth
	uint32_t colordepth = (*img).getColorDepth();

	// Get bitdepth
	uint16_t bitdepth = (*img).getBitDepth();

	// Determines if it has an alpha channel
	bool hasalpha = (*img).hasAlphaChannel();

	// Gets Identifier/Filename - Sometimes messes up the name of file?
	std::string id = (*img).getIdentifier();

	// Adds Filename
	output = output + "ID/Filename: " + id + "\n";

	// Adds Compression Algorithm
	output = output + "Compression Algorithm: " +
	std::to_string(static_cast<std::underlying_type
	<BE::Image::CompressionAlgorithm>::type>(compalg)) + "\n";

	// Print out Resolution of Image
	output = output + "Resolution of Image: " + to_string(res) + "\n";

	// Print out ColorDepth of Image
	output = output + "Color Depth of Image: " + std::to_string(colordepth) 
	+ "\n";

	// Print out BitDepth of Image
	output = output + "Bit Depth of Image: " + std::to_string(bitdepth) + "\n";

	// Print out Data Size of Image
	output = output + "Data Size of Image: " + std::to_string(data.size()) 
	+ "\n";

	// Print out Whether it has an alpha channel
	output = output + "Alpha Channel: " + std::to_string(hasalpha) + "\n";

	return output;
}

int main( int argc, char** argv ) 
{
	if (argc != 2) {
		std::cerr << "Must Provide an image or a Directory\n";
		return -1;
	}
	
	// Get Filename
	std::string filename = argv[1];
	size_t ifdir = filename.find("/");

	if (ifdir == std::string::npos) {
		// its a file and not a dir:
		std::string output = generateInfo(filename);
		std::cout << output << "\n";	
	} else {
		// Its a Directory
		DIR *dr;
		struct dirent *en;
		dr = opendir(filename.c_str());

		if (dr) {
			while ((en = readdir(dr)) != NULL) {
				try {
					std::string path = filename + en->d_name;
					std::string output = generateInfo(path);

					std::cout << output << "\n";

				} catch (BE::Error::StrategyError& e) {
					std::cerr << e.what() << "\n" << "\n";
				}
			}
			closedir(dr);
		}
	}
	return 0;
}
		
		// Stuff That doesn't seem to work:

		// Executing this results in a calling a pure virtural function error - 
		// or segfaults - depending on true or false
		// BE::Memory::uint8Array rawdata = 
		// (*img).getRawData(false);

		// Segfaults
		// BE::Memory::uint8Array rawgrayscale =
		// (*img).getRawGrayscaleData(1);

		// This says its protected: - but you can just do .getData().size()?
		// uint64_t datasize = (*img).getDataSize();
	
		// For some reason returns a memory address
		// Get Dimensions of Image
		// BE::Image::Size dims = 
		// (*img).getDimensions();

		// Gets Status Callback - Also returns a memory address - how to parse?
		// BE::Image::Image::statusCallback_t status = 
		// (*img).getStatusCallback();

