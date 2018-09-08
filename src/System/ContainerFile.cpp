#include "../../H3D/System/ContainerFile.hpp"
#include "../../H3D/System/Utilities.hpp"
/////////////////////////////////////////////////////////////////
// Implementation of ContainerFile Class
/////////////////////////////////////////////////////////////////
h3d::ContainerFile::ContainerFile(){}
h3d::ContainerFile::ContainerFile(std::string path,bool filemapping) {
	m_fh.open(path,filemapping);
}
h3d::ContainerFile::ContainerFile(h3d::FileHandle &filehandle) {
	m_fh = filehandle;
}
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
	h3d::FileType::CH3D::Header header;
	h3d::setObjectFromFileHandle(header, m_fh);

	// Verifying Header
	if (memcmp(header.formatStr, "h3dcon", 6)) {
		h3d::Log::error("%s invalid h3d::ContainerFile.", path.c_str());
		return false;
	};

	// Get ItemListings
	static Item tempItem;
	static h3d::FileType::CH3D::ItemListing tempListing;

	for (unsigned int i = 0;i < header.itemCount;i++)
	{
		// Get Listing from file
		h3d::setObjectFromFileHandle(tempListing,m_fh);	
		
		// Add as internal format to map
		tempItem.filename = tempListing.filename;
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
bool h3d::ContainerFile::openContainerFile(h3d::FileHandle &const filehandle)
{
	return true;
}
bool h3d::ContainerFile::close() 
{
	m_fh.close();
	return true;
}
/////////////////////////////////////////////////////////////////
h3d::MemoryStream& const h3d::ContainerFile::getMemoryStream(std::string filename)
{
	static MemoryStream ms = MemoryStream();
	ms.close();
	if (m_items.find(filename) != m_items.end()) {
		return m_items[filename].m_memoryStream;
	}
	else
		return ms;
}
/////////////////////////////////////////////////////////////////
// Container File Utilities
/////////////////////////////////////////////////////////////////
bool h3d::createContainerFile(std::string output_file,
	std::vector<std::string> input_files)
{
	h3d::Log::info("Creating ContainerFile %s", output_file.c_str());

	// Create Output Filestream
	h3d::FileHandle fh;
	if (!fh.open(output_file)) return false;

	// Setup Header in file
	h3d::FileType::CH3D::Header header;
	strcpy_s(header.formatStr, "h3dcon");
	header.itemCount = input_files.size();

	fh.write((char*)&header, sizeof(header));

	h3d::Log::info("%s will contain %d items.", output_file.c_str(), header.itemCount);

	// Write until done
	static h3d::FileHandle infh;
	static h3d::FileType::CH3D::ItemListing itemlisting;
	static char* buffer;

	for (auto &iter : input_files)
	{
		h3d::Log::info("Copying from %s", iter.c_str());

		// Filestream
		infh.open(iter);
		auto file_length = infh.getFileSize();

		buffer = new char[file_length];
		infh.read(buffer, file_length);
		infh.close();

		itemlisting.filename = iter;
		itemlisting.filesize = file_length;

		fh.write((char*)&itemlisting, sizeof(itemlisting));
		fh.write(buffer, file_length);
	}

	return true;
}
/////////////////////////////////////////////////////////////////