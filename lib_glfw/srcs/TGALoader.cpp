
#include <cstdio>
#include "TGALoader.hpp"

const char *        Image::TGAFileOpenException::what() const throw()
{
    return ("File could not be opened");
}

const char *        Image::TGAFileInvalidHeaderException::what() const throw()
{
    return ("TGA file header is not formated correctly");
}

Image::Image(void) : _imageWidth(0), _imageHeight(0), _bytesPerPixel(0)
{
    return ;
}

Image::Image(Image const & src)
{
    *this = src;
    return ;
}

Image::~Image(void)
{
    return ;
}

Image           &Image::operator=(Image const & rhs)
{
    this->_imageWidth = rhs._imageWidth;
    this->_imageHeight = rhs._imageHeight;
    this->_bytesPerPixel = rhs._bytesPerPixel;
    return *this;
}

int             Image::getWidth(void) const
{
    return this->_imageWidth;
}

int             Image::getHeight(void) const
{
    return this->_imageHeight;
}

const unsigned char *Image::getPixel(int x, int y) const
{
    return (&_Pixels[(y * _imageWidth + x) *4]);
}

const unsigned char *Image::getDataForOpenGL(void) const
{
    return (&_Pixels[0]);
}

void            Image::loadTGA(std::string filename)
{
    FILE                *pFile;
    unsigned char       ucHeader[18];
    unsigned char       temp;

    if (!(pFile = fopen(filename.c_str(), "rb")))
        throw TGAFileOpenException();
    // Read the header of the TGA, compare it with the known headers for compressed and uncompressed TGAs
    fread (ucHeader, sizeof(unsigned char) * 18, 1, pFile);
    while (ucHeader[0]-- > 0)
        fread (&temp, sizeof(unsigned char), 1, pFile);
    _imageWidth = ucHeader[13] * 256 + ucHeader[12];
    _imageHeight = ucHeader[15] * 256 + ucHeader[14];
    _bytesPerPixel = ucHeader[16] / 8;
    if ((_imageWidth <= 0) || (_imageHeight <= 0) || ((_bytesPerPixel != 1) && (_bytesPerPixel != 3) && (_bytesPerPixel != 4)))
    {
        fclose (pFile);
        throw TGAFileInvalidHeaderException();
    }
    // allocate the image-buffer
    _Pixels.resize(_imageWidth * _imageHeight * 4);
    // call the appropriate loader-routine
    if (ucHeader[2] == 2)
        _loadUncompressedTGA(pFile);
    else
    {
        if (ucHeader[2] == 10)
            _loadCompressedTGA(pFile);
        else
        {
            fclose(pFile);
            throw TGAFileInvalidHeaderException();
        }
    }
    fclose(pFile);
    return ;
}

void            Image::_loadUncompressedTGA(FILE *pFile)
{
    unsigned char       ucBuffer[4] = {255, 255, 255, 255};
    unsigned char       *pIntPointer;
    unsigned char       *pIntBuffer;
    const int           iPixelCount	= _imageWidth * _imageHeight;

    pIntPointer = &_Pixels[0];
    pIntBuffer = &ucBuffer[0];
    for (int i = 0; i < iPixelCount; ++i)
    {
        fread (ucBuffer, sizeof(unsigned char) * _bytesPerPixel, 1, pFile);
        // if this is an 8-Bit TGA only, store the one channel in all four channels
        // if it is a 24-Bit TGA (3 channels), the fourth channel stays at 255 all the time, since the 4th value in ucBuffer is never overwritten
        if (_bytesPerPixel == 1)
        {
            ucBuffer[1] = ucBuffer[0];
            ucBuffer[2] = ucBuffer[0];
            ucBuffer[3] = ucBuffer[0];
        }
        // copy all four values in one operation
        (*pIntPointer) = (*pIntBuffer);
        pIntPointer++;
    }
}

void            Image::_loadCompressedTGA(FILE *pFile)
{
    int                 iCurrentPixel;
    int                 iCurrentByte;
    unsigned char       ucBuffer[4] = {255, 255, 255, 255};
    const int           iPixelCount	= _imageWidth * _imageHeight;
    unsigned char       *pIntPointer;
    unsigned char       *pIntBuffer;
    unsigned char       ucChunkHeader;
    unsigned char       i;

    iCurrentPixel = 0;
    iCurrentByte = 0;
    pIntPointer = &_Pixels[0];
    pIntBuffer = &ucBuffer[0];
    ucChunkHeader = 0;
    while (iCurrentPixel <= iPixelCount)
    {
        fread (&ucChunkHeader, sizeof(unsigned char), 1, pFile);
        if (ucChunkHeader < 128)
        {
            // If the header is < 128, it means it is the number of RAW color packets minus 1
            // that follow the header
            // add 1 to get number of following color values
            ucChunkHeader++;	
            // Read RAW color values
            for (i = 0; i < ucChunkHeader; i++)	
            {
                fread (&ucBuffer[0], _bytesPerPixel, 1, pFile);
                // if this is an 8-Bit TGA only, store the one channel in all four channels
                // if it is a 24-Bit TGA (3 channels), the fourth channel stays at 255 all the time, since the 4th value in ucBuffer is never overwritten
                if (_bytesPerPixel == 1)
                {
                    ucBuffer[1] = ucBuffer[0];
                    ucBuffer[2] = ucBuffer[0];
                    ucBuffer[3] = ucBuffer[0];
                }
                // copy all four values in one operation
                (*pIntPointer) = (*pIntBuffer);
                pIntPointer++;
                iCurrentPixel++;
            }
        }
        else // chunkheader > 128 RLE data, next color reapeated (chunkheader - 127) times
        {
            ucChunkHeader -= 127;	// Subteact 127 to get rid of the ID bit
            // read the current color
            fread (&ucBuffer[0], _bytesPerPixel, 1, pFile);
            // if this is an 8-Bit TGA only, store the one channel in all four channels
            // if it is a 24-Bit TGA (3 channels), the fourth channel stays at 255 all the time, since the 4th value in ucBuffer is never overwritten
            if (_bytesPerPixel == 1)
            {
                ucBuffer[1] = ucBuffer[0];
                ucBuffer[2] = ucBuffer[0];
                ucBuffer[3] = ucBuffer[0];
            }
            // copy the color into the image data as many times as dictated 
            for (i = 0; i < ucChunkHeader; i++)
            {
                (*pIntPointer) = (*pIntBuffer);
                pIntPointer++;
                iCurrentPixel++;
            }
        }
    }
}
