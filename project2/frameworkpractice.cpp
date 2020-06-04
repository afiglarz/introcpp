// Practice project getting used to the biomeval framework
#include <dirent.h>
#include <sys/types.h>

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "frameworkpractice.h"

//namespace BE = BiometricEvaluation;

// Write a summary method that prints general image information?

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
	size_t ifdir = filename.find("/");

	if (ifdir == std::string::npos) {
		// its a file and not a dir:
	
		// Stuff that seems to work //

		// Open the Image (Using function I wrote that just calls openImage())
		auto img = myOpenImage(filename).get();

		// Get Compression Algorithm from image
		BiometricEvaluation::Image::CompressionAlgorithm compalg = 
		(*img).getCompressionAlgorithm();

		// Get Resolution of Image 
		BiometricEvaluation::Image::Resolution res = 
		(*img).getResolution();

		// Get Data of Image -- Not Raw -- Is encoded
		BiometricEvaluation::Memory::uint8Array data = 
		(*img).getData();

		// Get Colordepth
		uint32_t colordepth = (*img).getColorDepth();

		// Get bitdepth
		uint16_t bitdepth = (*img).getBitDepth();

		// Determines if it has an alpha channel
		bool hasalpha = (*img).hasAlphaChannel();

		// Gets Identifier/Filename
		std::string id = (*img).getIdentifier();

		// Stuff that seems to not work //

		// Executing this results in a calling a pure virtural function error - or 
		// segfaults - depending on true or false
		// BiometricEvaluation::Memory::uint8Array rawdata = 
		// (*img).getRawData(false);

		// Segfaults
		// BiometricEvaluation::Memory::uint8Array rawgrayscale =
		// (*img).getRawGrayscaleData(1);

		// This says its protected: - but you can just do .getData().size()?
		// uint64_t datasize = (*img).getDataSize();
	
		// For some reason returns a memory address
		// Get Dimensions of Image
		// BiometricEvaluation::Image::Size dims = 
		// (*img).getDimensions();

		// Gets Status Callback - Also returns a memory address - how to parse?
		// BiometricEvaluation::Image::Image::statusCallback_t status = 
		// (*img).getStatusCallback();

		// Print out Compression Algorithm - have to cast it because it is an enum
	
		// Print out Image Identifier
		std::cout << "ID/Filename: " << id << "\n";

		std::cout << "Compression Algorithm: " << 
		static_cast<std::underlying_type
		<BiometricEvaluation::Image::CompressionAlgorithm>::type>(compalg) 
		<< "\n";

		// Print out Resolution of Image
		std::cout << "Resolution of Image: " << res << "\n";

		// Print out ColorDepth of Image
		std::cout << "Color Depth of Image: " << colordepth << "\n";

		// Print out BitDepth of Image
		std::cout << "Bit Depth of Image: " << bitdepth << "\n";

		// Print out Data Size of Image
		std::cout << "Data Size of Image: " << data.size() << "\n";

		// Print out Whether it has an alpha channel
		std::cout << "Alpha Channel: " << hasalpha << "\n";
	
	} else {
		// Its a Directory
		DIR *dr;
		struct dirent *en;
		dr = opendir(filename.c_str());

		if (dr) {
			while ((en = readdir(dr)) != NULL) {
				try {

					std::string path = filename + en->d_name;

					auto img = myOpenImage(path).get();

					BiometricEvaluation::Image::CompressionAlgorithm compalg = 
					(*img).getCompressionAlgorithm();

					// Get Resolution of Image 
					BiometricEvaluation::Image::Resolution res = 
					(*img).getResolution();

					// Get Data of Image -- Not Raw -- Is encoded
					BiometricEvaluation::Memory::uint8Array data = 
					(*img).getData();

					// Get Colordepth
					uint32_t colordepth = (*img).getColorDepth();

					// Get bitdepth
					uint16_t bitdepth = (*img).getBitDepth();

					// Determines if it has an alpha channel
					bool hasalpha = (*img).hasAlphaChannel();

					// Gets Identifier/Filename
					std::string id = (*img).getIdentifier();

					// Print out Image Identifier
					std::cout << "ID/Filename: " << id << "\n";

					std::cout << "Compression Algorithm: " << 
					static_cast<std::underlying_type
					<BiometricEvaluation::Image::CompressionAlgorithm>::type>
					(compalg) << "\n";

					// Print out Resolution of Image
					std::cout << "Resolution of Image: " << res << "\n";

					// Print out ColorDepth of Image
					std::cout << "Color Depth of Image: " << colordepth << "\n";

					// Print out BitDepth of Image
					std::cout << "Bit Depth of Image: " << bitdepth << "\n";

					// Print out Data Size of Image
					std::cout << "Data Size of Image: " << data.size() << "\n";

					// Print out Whether it has an alpha channel
					std::cout << "Alpha Channel: " << hasalpha << "\n";

					std::cout << "\n";

				} catch (BiometricEvaluation::Error::StrategyError& e) {
					std::cerr << e.what() << "\n" << "\n";

				}

			}
			closedir(dr);
		}

	}

	return 0;
}