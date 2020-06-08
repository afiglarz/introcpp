// Practice project getting used to the biomeval framework

#include <dirent.h>
#include <sys/types.h>

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// Include wherever you use~
#include <be_io_utility.h>
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

	std::shared_ptr<BE::Image::Image> img{};

	try {
		img = BE::Image::Image::openImage(filename);
	} catch (const BE::Error::Exception &e) {
		throw BE::Error::ObjectDoesNotExist("Could Not Open file: " + filename);
	}
	
	// Gets Identifier/Filename
	std::string id = img->getIdentifier();
	// Get Compression Algorithm from image
	BE::Image::CompressionAlgorithm compalg = img->getCompressionAlgorithm();
	// Gets Dimensions
	BE::Image::Size dims = img->getDimensions();
	// Get Resolution of Image 
	BE::Image::Resolution res = img->getResolution();
	// Get Data of Image -- Not Raw -- Is encoded -- used to get size rn 
	BE::Memory::uint8Array data = img->getData();
	// Get Colordepth
	uint32_t colordepth = img->getColorDepth();
	// Get bitdepth
	uint16_t bitdepth = img->getBitDepth();
	// Determines if it has an alpha channel
	bool hasalpha = img->hasAlphaChannel();
	// Works: No Seg Faults -- Isn't needed rn
	// BE::Memory::uint8Array rawdata = img->getRawData(false);

	// Works: No Seg Faults -- Isn't needed rn
	// BE::Memory::uint8Array rawgrayscale = img->getRawGrayscaleData(1);

	// Prints Filename
	output = output + "ID/Filename: " + id + "\n";
	// Prints Compression Algorithm

	auto compalg_cast = static_cast<std::underlying_type
	<BE::Image::CompressionAlgorithm>::type>(compalg);

	std::string compalg_castclass{};
	// Could Greg Explain what these are - Facsimile, None, NetPBM?
	if (compalg_cast == 0) {
		compalg_castclass = "None";
	} else if (compalg_cast == 1) {
		compalg_castclass = "Facsimile";
	} else if (compalg_cast == 2) {
		compalg_castclass = "WSQ20";
	} else if (compalg_cast == 3) {
		compalg_castclass = "JPEGB";
	} else if (compalg_cast == 4) {
		compalg_castclass = "JPEGL";
	} else if (compalg_cast == 5) {
		compalg_castclass = "JP2";
	} else if (compalg_cast == 6) {
		compalg_castclass = "JP2L";
	} else if (compalg_cast == 7) {
		compalg_castclass = "PNG";
	} else if (compalg_cast == 8) {
		compalg_castclass = "NetPBM";
	} else if (compalg_cast == 9) {
		compalg_castclass = "BMP";
	} else if (compalg_cast == 10) {
		compalg_castclass = "TIFF";
	}

	output = output + "Compression Algorithm: " + compalg_castclass + "\n";
	// Pint out Dimensions of Image
	output = output + "Dimensions: " + to_string(dims) + "\n";
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

	if (!BE::IO::Utility::pathIsDirectory(filename)) {
		// In this case, it is a file and not a directory
		try {
			std::string output = generateInfo(filename);
			std::cout << output << "\n";
		} catch (BE::Error::ObjectDoesNotExist &e) {
			std::cerr << e.what() << "\n" << "\n";
			return EXIT_FAILURE;
		}	

	} else {
		// Its a directory
		// Removes additional slashes for directories
		auto slash_pos = filename.find("/");
		filename.erase(slash_pos);

		DIR *dr;
		struct dirent *en;
		dr = opendir(filename.c_str());

		if (dr) {
			while ((en = readdir(dr)) != NULL) {
				if (strcmp(en->d_name, ".") != 0 && 
					strcmp(en->d_name, "..") != 0) {
					
					try {
						std::string path = filename + '/' + en->d_name;
						std::string output = generateInfo(path);
						std::cout << output << "\n";

					} catch (BE::Error::ObjectDoesNotExist &e) {
						std::cerr << e.what() << "\n" << "\n";
					}
				}
			}
		closedir(dr);
		}
			
	}
	return 0;
}

		// Ask Greg for clarification on what this is again.
		// Gets Status Callback
		// BE::Image::Image::statusCallback_t status = 
		// (*img).getStatusCallback();

