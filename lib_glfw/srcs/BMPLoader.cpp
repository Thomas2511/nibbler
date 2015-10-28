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
    return ;
}

BMPImage        &BMPImage::operator=(BMPImage const &rhs)
{
    std::memcpy(this->_header, rhs._header, 54);
    this->_data = rhs._data;
    this->_data_pos = rhs._data_pos;
    this->_width = rhs._width;
    this->_height = rhs._height;
    this->_image_size = rhs._image_size;
    return *this;
}

void             BMPImage::loadBMP(const char *filename)
{
    std::ifstream   file;
    file.open(filename);
    if (!file.is_open())
        throw BMPLoaderFileOpenException();
	file.read(this->_header, 54);
    if (!file)
        throw BMPLoaderFileReadException();
	if (this->_header[0] != 'B' && this->_header[1] != 'M')
		throw BMPLoaderHeaderFormatException();
	this->_data_pos = *(reinterpret_cast<int*>(&(this->_header[0x0A])));
	this->_image_size = *(reinterpret_cast<int*>(&(this->_header[0x22])));
	this->_width = *(reinterpret_cast<int*>(&(this->_header[0x12])));
	this->_height = *(reinterpret_cast<int*>(&(this->_header[0x16])));
	if (this->_image_size == 0)
		this->_image_size = this->_width * this->_height * 3;
	if (this->_data_pos == 0)
		this->_data_pos = 54;
	if (!(this->_data = reinterpret_cast<char*>(malloc(this->_image_size))))
		throw BMPLoaderMallocException();
	file.read(this->_data, this->_image_size);
	file.close();
}

unsigned int    BMPImage::getWidth(void)
{
    return this->_width;
}

unsigned int    BMPImage::getHeight(void)
{
    return this->_height;
}

char            *BMPImage::getData(void)
{
    return this->_data;
}
