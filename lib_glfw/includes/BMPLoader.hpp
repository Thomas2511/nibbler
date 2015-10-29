#ifndef BMPLOADER_HPP
# define BMPLOADER_HPP

# include <iostream>
# include <fstream>

class BMPImage
{
    class BMPLoaderException : public std::exception {};
    class BMPLoaderFileOpenException : public BMPLoaderException
    {
        public:
            virtual const char *        what() const throw();
    };
    class BMPLoaderFileReadException : public BMPLoaderException
    {
        public:
            virtual const char *        what() const throw();
    };
    class BMPLoaderHeaderFormatException : public BMPLoaderException
    {
        public:
            virtual const char *        what() const throw();
    };
    class BMPLoaderMallocException : public BMPLoaderException
    {
        public:
            virtual const char *        what() const throw();
    };
    public:
    BMPImage(void);
    BMPImage(BMPImage const & src);
    virtual ~BMPImage(void);
    BMPImage &     operator=(BMPImage const & rhs);
    void            loadBMP(const char *filename);
    unsigned int    getWidth(void);
    unsigned int    getHeight(void);
    unsigned char   *getData(void);

    private:
    uint8_t           *_data;
    unsigned int    _width;
    unsigned int    _height;
    unsigned int    _image_size;
};

#endif
