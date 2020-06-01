#include <ctype.h>
#include <unistd.h>

#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <vector>
#include <sstream>
#include <fstream>

#include "proj1header.h"

using namespace myImage;
  
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
  
Image
myImage::imgcase(
		 const std::string &optarg )
{
  std::vector<std::string> parsedflags = myImage::split(optarg, ',');
  
  myImage::Image img{0,0,0,0};
    
  try {
    const auto tmp = std::stoul(parsedflags.at(0));
    uint16_t w = static_cast<uint16_t>(tmp);
    img.setWidth(w);
      
  } catch (const std::out_of_range &) {
    // The first one does not get hit, but the next three do - why?
    //std::cout << "Out of Range\n";
  }
    
  try {
    const auto tmp = std::stoul(parsedflags.at(1));
    uint16_t h = static_cast<uint16_t>(tmp);
    img.setHeight(h);
      
  } catch (const std::out_of_range &) {
    //std::cout << "Out of Range\n";
  }
    
  try {
    const auto tmp = std::stoul(parsedflags.at(2));
    uint16_t dpi = static_cast<uint16_t>(tmp);
    img.setDPI(dpi);
      
  } catch (const std::out_of_range &) {
    //std::cout << "Out of Range\n";
  }
    
  try {
    const auto tmp = std::stoul(parsedflags.at(3));
    uint8_t dep = static_cast<uint8_t>(tmp);
    img.setDepth(dep);
      
  } catch (const std::out_of_range &) {
    // std::cout << "Out of Range\n";
  }
    
  return img; 
}

uint16_t
myImage::intcase(
		 const std::string &optarg )
{
  const auto tmp = std::stoul(optarg);

  if (tmp > UINT16_MAX) {
    // error
    std::cout << "Value is over UINT16_MAX - Converting to '0'\n";
    return 0;
  }

  uint16_t convert = static_cast<uint16_t>(tmp);
  return convert;
}

int main( int argc, char **argv )
{

  //Get File Extension of File: 
  const std::string filename = argv[1];
  const std::size_t found = filename.find_last_of(".");
  const std::string fileExt = filename.substr(found+1);  
  //std::cout << fileExt + "\n";

  //Reading in File:

  // std::ifstream myfile(filename, std::ios::in | std::ios::binary);

  //char buffer[8];
    
  //myfile.read(buffer, 8);

  //std::cout << std::hex << buffer;
  //printf("%02hhx", buffer);

  //std::cout << "\n";

  // myfile.close();
    
  std::vector<uint16_t> intvector{};
  std::vector<std::string> strvector{};
  std::vector<myImage::Image> imgvector{};

  bool writetofile = false;
  std::string savepath{};
  
  static const char options[] {"x:s:i:o:"};
  int c{};
  
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
	imgvector.push_back(myImage::imgcase(optarg));
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
