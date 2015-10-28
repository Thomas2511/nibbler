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
        char            *getData(void);

    private:
        char            _header[54];
        char            *_data;
        unsigned int    _data_pos;
        unsigned int    _width;
        unsigned int    _height;
        unsigned int    _image_size;
};

#endif
