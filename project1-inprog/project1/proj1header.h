#ifndef PROJ1HEADER_H_
#define PROJ1HEADER_H_

namespace myImage {

  class Image {
  public:
 
    Image(uint16_t w, uint16_t h, uint16_t d, uint8_t dep);

    std::string toString () const;

    uint16_t getHeight() const;
    uint16_t getWidth() const;
    uint16_t getDPI() const;
    uint8_t getDepth() const;
    void setHeight(uint16_t val);
    void setWidth(uint16_t val);
    void setDPI(uint16_t val);
    void setDepth(uint8_t val);

  private:
    uint16_t width;
    uint16_t height;
    uint16_t dpi;
    uint8_t depth;
  };
  
  std::vector<std::string> split(const std::string &s, char delimiter);
  Image imgcase(const std::string &optarg);
  uint16_t intcase(const std::string &optarg);

}
#endif
