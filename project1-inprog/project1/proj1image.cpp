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
myImage::Image::toString ()
  const
{
  std::string ret =
    std::to_string(width) + "x" +
    std::to_string(height) +", " +
    std::to_string(dpi) + " PPI, " +
    std::to_string(depth) + " BPC";
    
  return ret;
}
  
uint16_t
myImage::Image::getWidth()
  const
{
  return this->width;
}
  
uint16_t
myImage::Image::getHeight()
  const
{
  return this->height;
}
  
uint16_t
myImage::Image::getDPI()
  const
{
  return this->dpi;
}
  
uint8_t
myImage::Image::getDepth()
  const
{
  return this->depth;
}
  
void
myImage::Image::setWidth(uint16_t val)
{
  this->width = val;
}
  
void
myImage::Image::setHeight(uint16_t val)
{
  this->height = val;
}
  
void
myImage::Image::setDPI(uint16_t val)
{
  this->dpi = val;
}
  
void
myImage::Image::setDepth(uint8_t val)
{
  this->depth = val;
}

