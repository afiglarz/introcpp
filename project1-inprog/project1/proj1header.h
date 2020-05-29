#ifndef PROJ1HEADER_H_
#define PROJ1HEADER_H_

namespace myImage {

  class Image {
  public:
    std::string toString () const;
    Image(uint16_t w, uint16_t h, uint16_t d, uint8_t dep);
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
