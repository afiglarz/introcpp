#include <ctype.h>
#include <unistd.h>

#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <vector>
#include <sstream>

#include "proj1header.h"

using namespace myImage;

std::string
Image::toString ()
  const
{
  std::string ret =
    std::to_string(width) + "x" +
    std::to_string(height) +", " +
    std::to_string(dpi) + " PPI, " +
    std::to_string(depth) + " BPC";
    
  return ret;
}
  
std::vector<std::string> split(const std::string &s, char delimiter)
    
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
imgcase(
	const std::string &optarg )
{
  std::vector<std::string> parsedflags = myImage::split(optarg, ',');

  Image img{0,0,0,0};
    
  try {
    const auto tmp = std::stoul(parsedflags.at(0));
    uint16_t w = static_cast<uint16_t>(tmp);
    img.setWidth(w);
      
  } catch (const std::out_of_range &) {
    std::cout << "Out of Range\n";
  }
    
  try {
    const auto tmp = std::stoul(parsedflags.at(1));
    uint16_t h = static_cast<uint16_t>(tmp);
    img.setHeight(h);
      
  } catch (const std::out_of_range &) {
    std::cout << "Out of Range\n";
  }
    
  try {
    const auto tmp = std::stoul(parsedflags.at(2));
    uint16_t dpi = static_cast<uint16_t>(tmp);
    img.setDPI(dpi);
      
  } catch (const std::out_of_range &) {
    std::cout << "Out of Range\n";
  }
    
  try {
    const auto tmp = std::stoul(parsedflags.at(3));
    uint8_t dep = static_cast<uint8_t>(tmp);
    img.setDepth(dep);
      
  } catch (const std::out_of_range &) {
    std::cout << "Out of Range\n";
  }
    
  return img; 
}

uint16_t
intcase(
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
  std::vector<uint16_t> intvector{};
  std::vector<std::string> strvector{};
  std::vector<myImage::Image> imgvector{};
  
  static const char options[] {"x:s:i:"};
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
	imgvector.push_back(myImage::imgcase(std::string(optarg)));
	break;
      case '?':
	std::cout <<
	  "Please only use the '-x, -s or -i' flags \n";
	return 1;
      }

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

  return 0;
}
