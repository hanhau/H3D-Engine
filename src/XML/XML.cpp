#include "../../H3D/XML/XML.hpp"

#include "../../H3D/System/FileSystem.hpp"
#include "../../H3D/System/Memorystream.hpp"
#include "../../H3D/System/Utilities.hpp"
/////////////////////////////////////////////////////////////////
// XML Implementation
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace xml {
		File::File(){}
		File::File(char path[]) { loadFromFile(path); }
		File::~File(){}

		bool File::loadFromFile(char path[]) {
			if (h3d::DebugMode)
				Log::info("Loading XML @ %s", path);

			FileHandle fh;
			if (!fh.open(path, true)) {
				Log::error("Error opening %s",path);
				return false;
			}
			
			char * mapping_ptr = fh.getMappingPtr<char*>();
			if (mapping_ptr != nullptr)
				loadFromMemory(mapping_ptr);
			else
			{
				h3d::Log::error("Unable to get Mapping Ptr");
				return false;
			}

			fh.close();
			return true;
		}
		bool File::loadFromMemory(void * mem) {
			if (h3d::DebugMode)
				Log::info("Loading XML from memory @ %d",&mem);
			h3dverify(mem != nullptr);

			int node_lvl = 0; // base node
			bool in_tag = false;
			bool in_attrib_name = false;
			bool in_attrib_value = false;

			std::string_view view = (const char*)mem;
			view.remove_prefix(view.find_first_of('>', 0));
			for (auto& const iter : view)
			{
				if (iter == '<') {
					node_lvl++;
					in_tag = true;
				}
				else if (iter == '>') {
					node_lvl--;
					in_tag = false;
				}
				else if(in_tag)
				{
					
				}
				else 
				{

				}
			}

			return true;
		}

		void writeTree(Node& beg,std::string output) {
			static int depth = 0;
			if (depth > 50 && h3d::DebugMode)
				Log::debug("Possible overflow XML iteration");

			for (int i(0); i < depth;i++) {
				output += "  ";
			}

			output += "\n";

			if (beg.getChildNodes().size() != 0)
				for (auto & iter : beg.getChildNodes()) {
					depth++;
					writeTree(iter,output);
					depth--;
				}
		}

		bool saveTreeToFile(Tree& tree, char path[])
		{
			std::string m_file;

			m_file += "<?xml version=\"1.0\" encoding=\"utf - 8\"?>\n";
			m_file += "<!-- Automatically generated -->\n";
			m_file += "<" + tree.getBaseNode().getName() + ">\n";

			writeTree(tree.getBaseNode(), m_file);

			m_file += "</" + tree.getBaseNode().getName() + ">\n";

			FileHandle fh;
			if(!fh.open(path)) {
				if (h3d::DebugMode)
					h3d::Log::error("Unable to save XML Tree to %s",
									path);
				return false;
			}

			fh.write((char*)m_file.c_str(), m_file.size());
			fh.close();
			
			return true;
		}
	}
}
/////////////////////////////////////////////////////////////////