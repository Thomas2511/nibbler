#include "BMPLoader.hpp"

const char *         BMPImage::BMPLoaderFileOpenException::what() const throw()
{
    return ("File open error");
}

const char *         BMPImage::BMPLoaderFileReadException::what() const throw()
{
    return ("File read error");
}

const char *         BMPImage::BMPLoaderHeaderFormatException::what() const throw()
{
    return ("BMP file header format error");
}

const char *         BMPImage::BMPLoaderMallocException::what() const throw()
{
    return ("BMP loader malloc error");
}

BMPImage::BMPImage(void)
{
    return ;
}

BMPImage::BMPImage(BMPImage const & src)
{
    *this = src;
    return ;
}

BMPImage::~BMPImage(void)
{
    delete[] this->_data;
    return ;
}

BMPImage        &BMPImage::operator=(BMPImage const &rhs)
{
    this->_data = rhs._data;
    this->_width = rhs._width;
    this->_height = rhs._height;
    this->_image_size = rhs._image_size;
    return *this;
}

void             BMPImage::loadBMP(const char *filename)
{
    std::ifstream   in(filename, std::ios::binary);
    uint8_t         *header = new uint8_t[54];

    if (!in)
        throw BMPLoaderFileOpenException();
    in.read(reinterpret_cast<char*>(header), 54);
    if (header[0] != 'B' || header[1] != 'M')
        throw BMPLoaderHeaderFormatException();
	this->_image_size = *(reinterpret_cast<int*>(&(header[0x22])));
	this->_width = *(reinterpret_cast<int*>(&(header[0x12])));
	this->_height = *(reinterpret_cast<int*>(&(header[0x16])));
    if (this->_image_size == 0)
        this->_image_size = this->_width * this->_height * 3;
    this->_data = new uint8_t[this->_image_size];
    in.read(reinterpret_cast<char*>(this->_data), this->_image_size);
    in.close();
}

unsigned int    BMPImage::getWidth(void)
{
    return this->_width;
}

unsigned int    BMPImage::getHeight(void)
{
    return this->_height;
}

unsigned char   *BMPImage::getData(void)
{
    return this->_data;
}
