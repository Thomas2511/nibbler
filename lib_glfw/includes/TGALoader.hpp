
#ifndef TGALOADER_HPP
# define TGALOADER_HPP

# include <string>
# include <vector>

class Image
{
	public:
        class TGAFileException : public std::exception {};
        class TGAFileOpenException : public TGAFileException
        {
            public:
                virtual const char *    what() const throw();
        };
        class TGAFileInvalidHeaderException : public TGAFileException
        {
            public:
                virtual const char *    what() const throw();
        };
		Image(void);
        Image(Image const & src);
        ~Image(void);

        Image               &operator=(Image const & rhs);

		int                 getWidth(void) const;
		int                 getHeight (void) const;
		const unsigned char *getPixel(int x, int y) const;
		//! Returns the raw array, as needed when uploading the image to OpenGL.
		/*! Upload the image to OpenGL like this:
		  IMAGE Image;
		  gluBuild2DMipmaps (GL_TEXTURE_2D, 4, Image.getWidth (), Image.getHeight (), GL_BGRA, GL_UNSIGNED_BYTE, Image.getDataForOpenGL  ());
		  */
		const unsigned char *getDataForOpenGL (void) const;
		void				loadTGA(std::string filename);

	private:
		void                _loadUncompressedTGA (FILE* pFile);
		void                _loadCompressedTGA(FILE* pFile);

        std::vector<unsigned char>      _Pixels;
		int                 _imageWidth;
		int                 _imageHeight;
		int                 _bytesPerPixel;
};

#endif
