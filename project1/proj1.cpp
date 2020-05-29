#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>
#include <vector>
#include <sstream>

namespace myImage
{
  class Image
  {
  private:
    uint16_t width;
    uint16_t height;
    uint16_t dpi;
    uint8_t depth;
    
  public:
    Image( uint16_t w, uint16_t h, uint16_t d, uint8_t dep )
    {
      width = w;
      height = h;
      dpi = d;
      depth = dep;
    }
    
    std::string toString ()
    {
      std::string ret =
	std::to_string(width) + "x" + std::to_string(height)
	+ ", " + std::to_string(dpi) + " PPI, " +
	std::to_string(depth) + " BPC";
      
      return ret;
    };
  };
  
  std::vector<std::string> split( std::string s, char delimiter )
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
  
  Image imgcase( std::string optarg )
  {
    std::vector<std::string> parsedflags = split(optarg, ',');
    
    Image img = {uint16_t (std::stoi(parsedflags[0], nullptr, 10)),
		 uint16_t (std::stoi(parsedflags[1], nullptr, 10)),
		 uint16_t (std::stoi(parsedflags[2], nullptr, 10)),
		 uint8_t (std::stoi(parsedflags[3], nullptr, 10)),
    };
    
    return img; 
  }
}

int main( int argc, char **argv )
{
  std::vector<std::string> intvector{1};
  std::vector<std::string> strvector{1};
  std::vector<myImage::Image> imgvector;
  
  static const char options[] {"x:s:i:"};
  int c{};
  
  while ((c = getopt(argc, argv, options)) != -1) 
    switch (c)
      {
      case 'x':
	intvector.push_back(optarg);
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

  std::cout << "Integers: ";
  for ( auto i : intvector )
    {
      std::cout << i + "\n";
    }
  
  std::cout << "Strings: ";
  for ( auto i : strvector )
    {
      std::cout << i + "\n";
    }  

  std::cout << "Images: \n";
  for ( auto i : imgvector )
    {
      std::cout << i.toString() + "\n";
    }

  return 0;
}
