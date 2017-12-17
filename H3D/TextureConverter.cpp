#include "Texture.hpp"
#include "FileDataStructures.hpp"
#include "FileSystem.hpp"
#include "Utilities.hpp"

/////////////////////////////////////////////////////////////////
// Texture converter impls
/////////////////////////////////////////////////////////////////
bool h3d::converter::BMPToKTX(char input[], char output[])
{
	FileHandle fh;
	if (!fh.open(input),true) {
		if(h3d::DebugMode)
		h3d::Log::error("BMPToKTX: Unable to open %s", input);
		return false;
	}

	h3d::FileType::BMP::Header *bmpHeader = nullptr;
	h3d::FileType::BMP::Body   *bmpBody = nullptr;

	bmpHeader = fh.getMappingPtr<h3d::FileType::BMP::Header*>();
	bmpBody = fh.getMappingPtr<h3d::FileType::BMP::Body*>(sizeof(bmpHeader));

	if (bmpHeader->bfType != 19778) {
		if (h3d::DebugMode)
		h3d::Log::error("%s isnt a BMP File", input);
		return false;
	}

	h3d::Vec2<int> m_texSize(bmpBody->biWidth,bmpBody->biHeight);

	FileHandle fh_out;
	if (!fh.open(output, true)) {
		if(h3d::DebugMode)
		Log::error("Cant open Output file %s",output);
		return false;
	}





	fh_out.close();
	fh.close();
	return true;
}
/////////////////////////////////////////////////////////////////
bool h3d::converter::PNGToKTX(char input[], char output[])
{
	FileHandle fh;
	if (!fh.open(input)) {
		h3d::Log::error("PNGToKTX: Unable to open %s", input);
		return false;
	}

	fh.close();
	return true;
}
/////////////////////////////////////////////////////////////////
bool h3d::converter::TGAToKTX(char input[], char output[])
{
	FileHandle fh;
	if (!fh.open(input)) {
		h3d::Log::error("TGAToKTX: Unable to open %s", input);
		return false;
	}

	fh.close();
	return true;
}
/////////////////////////////////////////////////////////////////