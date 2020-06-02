#ifndef PROJ1HEADER_H_
#define PROJ1HEADER_H_

namespace myImage {

  class Image {
  public:
 
	Image(uint16_t width_, uint16_t height_, uint16_t dpi_, uint8_t depth_);

	std::string toString () const;

	uint16_t getHeight() const;
	uint16_t getWidth() const;
	uint16_t getDPI() const;
	uint8_t getDepth() const;
	void setHeight(const uint16_t val);
	void setWidth(const uint16_t val);
	void setDPI(const uint16_t val);
	void setDepth(const uint8_t val);

	bool equals(Image img);

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
