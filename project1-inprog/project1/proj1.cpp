#include <ctype.h>
#include <unistd.h>

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <sstream>
#include <fstream>

#include "proj1header.h"

using namespace myImage;

// Used to split a string into a Vector of tokens given a delimiter
std::vector<std::string>
myImage::split(
	       const std::string &s,
	       char delimiter) 
{
  std::vector<std::string> tokens;
  std::string token;
  std::stringstream ss(s);

  while (std::getline( ss, token, delimiter ))
    {
      tokens.push_back(token);
    }
  return tokens;
}

// Used to handle the -i flag
Image
myImage::imgcase(
		 const std::string &optarg )
{
  // Splitting the arguments to the image case
  std::vector<std::string> parsedflags = myImage::split(optarg, ',');
  myImage::Image img{0,0,0,0};

  // Making sure 4 arguments were passed to an image
  // Otherwie catch an out_of_range exception and exit
  try {
    const auto tmp = std::stoul(parsedflags.at(0));
    uint16_t w = static_cast<uint16_t>(tmp);
    img.setWidth(w);
  } catch (const std::out_of_range &) {
    std::cout << "Out of Range\n";
    return myImage::Image{0,0,0,0};
  }
    
  try {
    const auto tmp = std::stoul(parsedflags.at(1));
    uint16_t h = static_cast<uint16_t>(tmp);
    img.setHeight(h);
  } catch (const std::out_of_range &) {
    std::cout << "Out of Range\n";
    return myImage::Image{0,0,0,0};
  }
    
  try {
    const auto tmp = std::stoul(parsedflags.at(2));
    uint16_t dpi = static_cast<uint16_t>(tmp);
    img.setDPI(dpi);
  } catch (const std::out_of_range &) {
    std::cout << "Out of Range\n";
    return myImage::Image{0,0,0,0};
  }
    
  try {
    const auto tmp = std::stoul(parsedflags.at(3));
    uint8_t dep = static_cast<uint8_t>(tmp);
    img.setDepth(dep);
  } catch (const std::out_of_range &) {
    std::cout << "Out of Range\n";
    return myImage::Image{0,0,0,0};
  }
  return img; 
}

// Used to handle the -x flag
uint16_t
myImage::intcase(
		 const std::string &optarg )
{
  // Auto automatically determines the type of the variable
  const auto tmp = std::stoul(optarg);

  // Making sure overflow does not happen
  if (tmp > UINT16_MAX) {
    // error
    std::cout << "Error-Value is over UINT16_MAX\n";
    exit(1);
  }
  // Static cast instead of traditional c-style casts
  uint16_t convert = static_cast<uint16_t>(tmp);
  return convert;
}

int main( int argc, char **argv )
{
  // Magic bytes for PNG, JPEG and PDF:
  const unsigned char PNGBytes[8] = {0x89, 0x50, 0x4E, 0x47,
				     0x0D, 0x0A, 0x1A, 0x0A};
  const unsigned char JPEGBytes[2] = {0xFF, 0xD8};
  const unsigned char PDFBytes[4] = {0x25, 0x50, 0x44, 0x46};
			     
  //Get File Extension of File: 
  const std::string filename = argv[1];
  const std::size_t found = filename.find_last_of(".");
  const std::string fileExt = filename.substr(found+1);  
  //std::cout << fileExt + "\n";

  //Reading in File and checking magic bytes for PNG, JPEG and PDF

  std::ifstream myfile(filename, std::ios::in | std::ios::binary);
  myfile.seekg(0, std::ios::beg);
  unsigned char magic[8] = {0}; 
  myfile.read((char*)magic, sizeof(magic));

  if (memcmp(magic, PNGBytes, sizeof(magic)) == 0) {
    std::cout << "File is a PNG\n";
  } else if (memcmp(magic, JPEGBytes, sizeof(magic) / 4) == 0) {
    std::cout << "File is a JPEG\n";
  } else if (memcmp(magic, PDFBytes, sizeof(magic) / 2) == 0) {
    std::cout << "File is a PDF\n";
  } else {
    std::cout << "File is not a PNG, JPG or PDF\n";
  }

  // Vectors holding the flag arguments:
  std::vector<uint16_t> intvector{};
  std::vector<std::string> strvector{};
  std::vector<myImage::Image> imgvector{};

  // If a -o flag is used then these two variables get updated
  bool writetofile = false;
  std::string savepath{};

  // Different flag options:
  static const char options[] {"x:s:i:o:"};
  int c{};

  // Getopt logic:
  while ((c = getopt(argc, argv, options)) != -1) 
    switch (c)
      {
      case 'x':
	intvector.push_back(myImage::intcase(optarg));
	break;
      case 's':
	strvector.push_back(optarg);
	break;
      case 'i':
	if (myImage::imgcase(optarg).equals(myImage::Image{0,0,0,0})) {
	  std::cout << "Not allowed an 'Empty' or incomplete Image.\n";
	  return 0;
	} else {
	  imgvector.push_back(myImage::imgcase(optarg));
	}
	break;
      case 'o':
	writetofile = true;
	savepath = optarg;
	break;
      case '?':
	std::cout <<
	  "Please only use the '-x, -s or -i' flags \n";
	return 1;
      }

  // Writes all output to file specificed with -o
  if (writetofile == true) {
    std::ofstream output;
    output.open(savepath);

    if (!output) {
      std::cout << "Error Creating file\n";
      exit(1);

    } else {

      output << "Integers: \n";
      for ( const auto &i : intvector )
	{
	  output << std::to_string(i) + "\n";
	}

      output << "Strings: \n";
      for ( const auto &i : strvector )
	{
	  output << i + "\n";
	}

      output << "Images: \n";
      for ( const auto &i : imgvector )
	{
	  output << i.toString() + "\n";
	}

      output.close();    
    }
    
  } else {

    // Write all output to stdout
    std::cout << "Integers: \n";
    for ( const auto &i : intvector )
      {
	std::cout << std::to_string(i) + "\n";
      }
  
    std::cout << "Strings: \n";
    for ( const auto &i : strvector )
      {
	std::cout << i + "\n";
      }  

    std::cout << "Images: \n";
    for ( const auto &i : imgvector )
      {
	std::cout << i.toString() + "\n";
      }
  }

  return 0;
  
}
