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
	
	std::string filename = argv[1];
	std::cout << filename << "\n";

	auto img = myOpenImage(filename);

	return 0;
}