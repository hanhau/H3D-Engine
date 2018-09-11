#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include <stdint.h>
#include <map>
namespace h3d {
/////////////////////////////////////////////////////////////////
//	FileDataStructures
/////////////////////////////////////////////////////////////////
	namespace FileType {
		/////////////////////////////////////////////////////////
		//	AUDIO FILE TYPES
		/////////////////////////////////////////////////////////
		// WAV File Format Structures ///////////////////////////
		namespace WAV {
			#pragma pack(push,WAV_HEADER,1)
			struct Header {
				char     chunkID[4];
				uint32_t ChunkSize;
				char     riffType[4];
			};
			#pragma pack(pop,WAV_HEADER)
			#pragma pack(push,WAV_FORMAT,1)
			struct Format {
				char subChunkID[4];
				long subChunkSize;
				short audioFormat;
				short numChannels;
				long sampleRate;
				long byteRate;
				short blockAlign;
				short bitsPerSample;
			};
			#pragma pack(pop,WAV_FORMAT)
			#pragma pack(push,WAV_DATA,1)
			struct Data {
				char subChunkID[4];
				long subChunk2Size;
			};
			#pragma pack(pop,WAV_DATA)
		}
		// OFF File Format Structures ///////////////////////////
		namespace OGG {
			#pragma pack(push,OGG_HEADER,1)
			struct Header {

			};
			#pragma pack(pop,OGG_HEADER)
		}
		/////////////////////////////////////////////////////////
		//	IMAGE FILE TYPES
		/////////////////////////////////////////////////////////
		// BMP File Format Structures ///////////////////////////
		namespace BMP {
			#pragma pack(push,BMP_HEADER,1)
			struct Header {
				uint16_t bfType;       // must "BM"
				uint32_t bfsize;       // 
				uint32_t bfReserved;   //
				uint32_t bfOffBits;    //
			};
			#pragma pack(pop,BMP_HEADER)
			#pragma pack(push,BMP_BODY,1)
			struct Body {
				uint32_t biSize;          // complete size in bytes
				int32_t  biWidth;         // x size
				int32_t  biHeight;        // y size
				uint16_t biPlanes;        // layers
				uint16_t biBitCount;      // bits per pixel
				uint32_t biCompression;   // compression type
				uint32_t biSizeImage;     // pixel count
				int32_t  biXPelsPerMeter; // dpi x
				int32_t  biYPelsPerMeter; // dpi y
				int32_t  biClrUsed;       // 0
				uint32_t biClrImportant;  // 0
			};
			#pragma pack(pop,BMP_BODY)
		}
		// PNG File Format Structures ///////////////////////////
		namespace PNG {
			struct Signature {
				uint8_t signature[8];
			};
			struct ChunkBase {
				uint8_t chunkType[4];
				uint32_t dataSize;
				uint32_t crc32Sum;
			};
			#pragma pack(push,PNG_HEADER,1)
			struct Header : ChunkBase {
				
			};
			#pragma pack(pop,PNG_HEADER)
			#pragma pack(push,PNG_END,1)
			struct End : ChunkBase {

			};
			#pragma pack(pop,PNG_END)
		}
		// KTX File Format Structures ///////////////////////////
		namespace KTX {
			#pragma pack(push,KTX_HEADER,1)
			struct Header {
				char     identifier[12];
				uint32_t endianness;
				uint32_t glType;
				uint32_t glTypeSize;
				uint32_t glFormat;
				uint32_t glInternalFormat;
				uint32_t glBaseInternalFormat;
				uint32_t pixelWith;
				uint32_t pixelHeight;
				uint32_t pixelDepth;
				uint32_t numberofArrayElements;
				uint32_t numberOfFaces;
				uint32_t numberOfMipmapLevels;
				uint32_t bytesOfKeyValueData;
			};
			#pragma pack(pop,KTX_HEADER)
		}
		// TGA File Format Structures ///////////////////////////
		namespace TGA {
			#pragma pack(push,TGA_HEADER,1)
			struct Header {
				int8_t IDlength;
				int8_t colormaptype;
				int8_t datatypecode;
				int16_t colormaporigin;
				int16_t colormaplength;
				int8_t colormapdepth;
				int16_t x_origin;
				int16_t y_origin;
				int16_t width;
				int16_t height;
				int8_t bitsperpixel;
				int8_t imagedescriptor;
			};
			#pragma pack(pop,TGA_HEADER)
			#pragma pack(push,TGA_HEADER_EXTENSION,1)
			struct HeaderExtension {

			};
			#pragma pack(pop,TGA_HEADER_EXTENSION)
			#pragma pack(push,TGA_FOOT,1)
			struct Foot {

			};
			#pragma pack(pop,TGA_FOOT)
		}
		/////////////////////////////////////////////////////////
		// ContainerFile
		namespace CH3D {
			#pragma pack(push,CONTAINERFILE_HEADER,1)
			struct Header
			{
				char formatStr[6];  // Must be "h3dcon"
				uint32_t itemCount; // Items in Container
			};
			#pragma pack(pop,CONTAINERFILE_HEADER)
			#pragma pack(push,CONTAINERFILE_ITEMLISTING,1)
			struct ItemListing
			{
				int32_t     filenameLength;
				std::string filename; 
				int64_t    filesize; 
				int64_t    begin,    
						   end;      
			};
			#pragma pack(pop,CONTAINERFILE_ITEMLISTING)
			#pragma pack (push,CONTAINERFILE_ITEMDICTIONARY,1)
			struct ItemDictionary
			{
				std::map<int, ItemListing> map;
			};
			#pragma pack(pop,CONTAINERFILE_ITEMDICTIONARY)
		}
		/////////////////////////////////////////////////////////
		// H3D Model Format
		namespace MH3D {
#pragma pack(push,MH3D_HEADER,1)
			struct Header {
				char		format[6];	// "mh3d_?"
				uint64_t	size;		// total file size
				char		type;		// 1 static or 2 animated
			};
#pragma pack(pop,MH3D_HEADER)
#pragma pack(push,MH3D_BOUNDING_BOX,1)
			struct BoundingBox {
				float x_start;
				float x_end;
				float y_start;
				float y_end;
				float z_start;
				float z_end;
			};
#pragma pack(pop,MH3D_BOUNDING_BOX)
#pragma pack(push,MH3D_INFORMATION,1)
			struct Information {
				int32_t numMesh;		
				int32_t numMaterial;
				int32_t numVertices;
				int32_t numAnimations;
				int8_t hasSpecularMap;
				int8_t hasNormalMap;
				int8_t hasDiffuseMap;
				int8_t hasDisplacementMap;
			};
#pragma pack(pop,MH3D_INFORMATION)
#pragma pack(push,MH3D_MATERIAL_INFO,1)
			struct MaterialInfo {
				union {uint64_t v[4];}m_uid; // 256 bit uid
				int8_t numLayers;
				int8_t layerSpecular;
				int8_t layerNormal;
				int8_t layerDiffuse;
				int8_t layerDisplacement;
				int32_t width;
				int32_t height;
				int8_t numBitsPP;
				int8_t hasAlpha;
				int64_t sizeBytes;
				int64_t offsetContent;
			};
#pragma pack(pop,MH3D_MATERIAL_INFO)
#pragma pack(push,MH3D_MODEL_DATA,1)
			struct ModelData {

			};
#pragma pack(pop,MH3D_MODEL_DATA)
#pragma pack(push,MH3D_ANIMATION_DATA,1)
			struct AnimationData {

			};
#pragma pack(pop,MH3D_ANIMATION_DATA)
		}
	}
/////////////////////////////////////////////////////////////////
}