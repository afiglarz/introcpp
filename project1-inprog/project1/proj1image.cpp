#include <ctype.h>
#include <unistd.h>

#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <vector>
#include <sstream>

#include "proj1header.h"

class Image {
  uint16_t width;
  uint16_t height;
  uint16_t dpi;
  uint8_t depth;
  
public:
  Image(
	uint16_t w,
	uint16_t h,
	uint16_t d,
	uint8_t dep ):
    width{w},
    height{h},
    dpi{d},
    depth{dep}
  {
  }
  
  std::string
  toString ()
    const
  {
    std::string ret =
      std::to_string(width) + "x" +
      std::to_string(height) +", " +
      std::to_string(dpi) + " PPI, " +
      std::to_string(depth) + " BPC";
    
    return ret;
  };
  
  uint16_t
  getWidth()
    const
  {
    return this->width;
  };
  
  uint16_t
  getHeight()
    const
  {
    return this->height;
  };
  
  uint16_t
  getDPI()
    const
  {
    return this->dpi;
  };
  
  uint8_t
  getDepth()
    const
  {
    return this->depth;
  };
  
  void
  setWidth(uint16_t val) {
    this->width = val;
  };
  
  void
  setHeight(uint16_t val) {
    this->height = val;
  };
  
  void
  setDPI(uint16_t val) {
    this->dpi = val;
  };
  
  void
  setDepth(uint8_t val) {
    this->depth = val;
  };
};
