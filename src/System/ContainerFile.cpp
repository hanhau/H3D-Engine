#include "../../H3D/System/ContainerFile.hpp"
#include "../../H3D/System/Utilities.hpp"
/////////////////////////////////////////////////////////////////
// Implementation of ContainerFile Class
/////////////////////////////////////////////////////////////////
h3d::ContainerFile::ContainerFile(){}
h3d::ContainerFile::ContainerFile(std::string path) {}
h3d::ContainerFile::~ContainerFile() {}
/////////////////////////////////////////////////////////////////
bool h3d::ContainerFile::openContainerFile(std::string path) 
{
	// Opening FileHandle
	if (false == m_fh.open(path)) {
		h3d::Log::error("Unable to open %s h3d::ContainerFile.", path.c_str());
		return false;
	}

	// Loading Header
	h3d::FileType::ContainerFile::Header header;
	h3d::setObjectFromFileHandle(header, m_fh);

	// Verifying Header
	if (memcmp(header.formatStr, "h3dcon", 6)) {
		h3d::Log::error("%s invalid h3d::ContainerFile.", path.c_str());
		return false;
	};

	// Get ItemListings
	static Item tempItem;
	static h3d::FileType::ContainerFile::ItemListing tempListing;

	for (int i = 0;i < header.itemCount;i++)
	{
		// Get Listing from file
		h3d::setObjectFromFileHandle(tempListing,m_fh);	
		
		// Add as internal format to map
		memmove(tempItem.filename, tempListing.filename, 48);
		tempItem.begin    = tempListing.begin;
		tempItem.end      = tempListing.end;
		tempItem.filesize = tempListing.filesize;

		//m_items[tempItem.filename] = tempItem;
		//m_items[tempItem.filename].filehandle.open(path);
	}

	// Clean up
	m_fh.close();
	return true;
}
bool h3d::ContainerFile::close() 
{
	for (auto &iter : m_items) {
		iter.second.filehandle.close();
	}
	return true;
}
/////////////////////////////////////////////////////////////////
h3d::FileHandle& h3d::ContainerFile::getFileHandle(char filename[48])
{
	

	return h3d::FileHandle();
}
/////////////////////////////////////////////////////////////////