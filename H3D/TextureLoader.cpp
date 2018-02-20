#include "FileSystem.hpp"
#include "FileDataStructures.hpp"
#include "Utilities.hpp"
#include "Vector.hpp"
#include "Texture.hpp"
#include "Color.hpp"

#include "externals.h"
#include STR(GLEW_INCLUDE/gl/glew.h)
/////////////////////////////////////////////////////////////////
// Loading individual formats
/////////////////////////////////////////////////////////////////
bool h3d::Texture::loadBMP(char Path[],h3d::Texture& ref)
{
	// Opening filestream
	h3d::FileHandle filehandle;
	filehandle.open(Path);
	if (FALSE == filehandle.isOpen()) {
		if (h3d::DebugMode) h3d::Log::error("Unable to load BMP %s",Path);
		return false;
	}

	// Temporarly variables
	h3d::FileType::BMP::Header t_header;
	h3d::FileType::BMP::Body   t_body;

	// Reading 
	// Header (12 bytes)
	h3d::setObjectFromFileHandle(t_header, filehandle);
	if (t_header.bfType != 19778) {
		if (h3d::DebugMode) {
			h3d::Log::error("%s is corrupted!", Path);
		}
		return false;
	}

	// Informationblock (40 bytes+t_bfOffBits/8)
	h3d::setObjectFromFileHandle(t_body, filehandle);

	// Set format intel
	ref.m_measurements = h3d::Vec2<int>(t_body.biWidth, abs(t_body.biHeight));

	// Picturedatablock
	unsigned long imageSize = t_body.biWidth*t_body.biHeight*t_body.biBitCount / 8;
	ref.m_buffer = new unsigned char[imageSize];
	h3d::setObjectFromFileHandle(ref.m_buffer, filehandle);

	return true;
}
/////////////////////////////////////////////////////////////////
bool h3d::Texture::loadPNG(char Path[],h3d::Texture& ref)
{
	// Open File
	h3d::FileHandle filehandle;
	filehandle.open(Path);
	if (FALSE == filehandle.isOpen()) {
		if (h3d::DebugMode) h3d::Log::error("Unable to open %s",Path);
		return false;
	}
	


	// Return successfully
	return true;
}
/////////////////////////////////////////////////////////////////
bool h3d::Texture::loadKTX(char Path[],h3d::Texture& ref)
{
	// Opening unbuffered filestream
	std::ifstream file_stream;
	file_stream.rdbuf()->pubsetbuf(0, 0);
	file_stream.open(Path, std::ios::binary);
	if (file_stream.bad()) {
		if (h3d::DebugMode) {
			h3d::Log::error("Unable to open %s", Path);
		}
		return false;
	}
	// Temporarly variables
	h3d::FileType::KTX::Header t_header;

	// Reading
	file_stream.read((char*)&t_header, sizeof(t_header));

	char identifier[12] = { '«', 'K', 'T', 'X', ' ',
						   '1', '1', '»', '\r', '\n',
						   '\x1A', '\n' };

	if (memcmp(t_header.identifier, identifier, 12)) {
		h3d::Log::error("File %s not a KTX file !",Path);
		return false;
	}



	for (int i = 0; i < t_header.bytesOfKeyValueData; i++)
	{
		uint32_t keyAndValueByteSize;
		char *keyAndValue = new char[keyAndValueByteSize];
		char *valuePadding = new char[3 - ((keyAndValueByteSize + 3) % 4)];
	}


		for each mipmap_level in numberOfMipmapLevels*
			UInt32 imageSize;
	for each array_element in numberOfArrayElements*
		for each face in numberOfFaces
			for each z_slice in pixelDepth*
				for each row or row_of_blocks in pixelHeight*
					for each pixel or block_of_pixels in pixelWidth
						Byte data[format - specific - number - of - bytes] * *
						end
						end
						end
						Byte cubePadding[0 - 3]
						end
						end
						Byte mipPadding[3 - ((imageSize + 3) % 4)]
						end

	// Return
	file_stream.close();
	return true;
}
/////////////////////////////////////////////////////////////////
bool h3d::Texture::loadTGA(char Path[],h3d::Texture& ref)
{
	h3d::FileHandle filehandle;
	filehandle.open(Path);
	if (FALSE == filehandle.isOpen()) {
		if (h3d::DebugMode) h3d::Log::error("Unable to load TGA %s", Path);
		return false;
	}

	// Temporary Variables
	h3d::FileType::TGA::Header t_header;
	h3d::Color<unsigned char> *pixels;
	size_t skipover;

	// Read Header (18 bytes)
	filehandle.read((char*)&t_header, sizeof(t_header));
	
	size_t pixel_count = t_header.width*t_header.height;
	pixels = new h3d::Color<unsigned char > [pixel_count];
	memset(pixels, 0, pixel_count * sizeof(h3d::Vec3<unsigned char>));

	// Check for valid format types
	if (t_header.datatypecode = 2 && t_header.datatypecode != 10) {
		h3d::Log::error("Can only handle image type 2 and 10");
		return false;
	}
	if (t_header.bitsperpixel != 16 &&
		t_header.bitsperpixel != 24 && t_header.bitsperpixel != 32) {
		h3d::Log::error("Can only handle pixel depths of 16, 24, and 32");
		return false;
	}
	if (t_header.colormaptype != 0 && t_header.colormaptype != 1) {
		h3d::Log::error("Can only handle colour map types of 0 and 1");
		return false;
	}

	// Skip
	skipover += t_header.IDlength;
	skipover += t_header.colormaptype * t_header.colormaplength;
	
	filehandle.setIterPos(filehandle.getIterPos() + skipover);

	// Reading the imade
	size_t bytes2read = t_header.bitsperpixel / 8;
	size_t n=0;
	h3d::Color<unsigned char> p;
	int i = 0, j = 0;
	/*
	while (n < t_header.width * t_header.height) {
		// Uncompressed
		if (t_header.datatypecode == 2) {
			if (filehandle.read((char*)&p, bytes2read) != bytes2read) {
				if (h3d::DebugMode)
					h3d::Log::error("TGA Error #1");
				return false;
			}
			MergeBytes(&(pixels[n]), p, bytes2read);
			n++;
		}
		// Compressed
		else if (t_header.datatypecode == 10) {
			if (filehandle.read((char*)&p, bytes2read+1) != bytes2read + 1) {
				if (h3d::DebugMode)
					h3d::Log::error("TGA Error #2");
				return false;
			}
			j = p[0] & 0x7f;
			MergeBytes(&(pixels[n]), &(p[1]), bytes2read);
			n++;
			// RLE Chunk
			if (p[0] & 0x80) {
				for (i = 0; i<j; i++) {
					MergeBytes(&(pixels[n]), &(p[1]), bytes2read);
					n++;
				}
			}
			// normal Chunk
			else {
				for (i = 0; i<j; i++) {
					if (filehandle.read((char*)&p, bytes2read) != bytes2read) {
						if(h3d::DebugMode)
							h3d::Log::error("TGA Error #3");
						return false;
					}
					MergeBytes(&(pixels[n]), p, bytes2read);
					n++;
				}
			}
		}
		*/
	// Close and return
	if (h3d::DebugMode)
		h3d::Log::info("Finished loading %s", Path);
	filehandle.close();
	return true;
}