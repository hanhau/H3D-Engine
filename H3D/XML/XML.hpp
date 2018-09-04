#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include <string>
#include <vector>
#include <any>
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace xml {
		class Value {
			std::string content;
		public:
		};

		struct Attribute {
			std::string name;
			Value       value;
		};

		class Tree;
		class Node
		{
			friend Tree;
			enum class ValueType {
				_int,_float,_string
			};
			
			std::vector<Attribute> m_attributes;
			std::vector<Value>     m_values;
			std::vector<Node>	   m_childs;
			std::string            m_name;

			void recSearchFromId(std::string id,Node* out);
			void recSearchFromType(std::string type, std::vector<Node*>& outvecs);
		public:
			H3D_API Node();
			H3D_API Node(const Node& node);
			H3D_API ~Node();

			void H3D_API appendChild(Node &&node);
			
			H3D_API const std::string&  getName();

			H3D_API std::vector<Node>&  getChildNodes();
			H3D_API std::vector<Value>& getValueVec();
			H3D_API std::vector<Attribute>& getAttributeVec();
		};

		class Tree
		{
			Node m_baseNode;
		public:
			H3D_API Tree();
			H3D_API ~Tree();

			H3D_API Node& getBaseNode();

			H3D_API Node& getNodeFromId(std::string id);
			std::vector<Node*> H3D_API getNodesFromType(std::string type);
		};

		class File
		{
			Tree m_tree;

		public:
			H3D_API File();
			H3D_API File(char path[]);
			H3D_API ~File();

			bool H3D_API loadFromFile(char path[]);
			bool H3D_API loadFromMemory(void * mem);

			H3D_API Tree& getTree() const;
		};

		bool H3D_API saveTreeToFile(Tree& tree,char path[]);
	}
}
/////////////////////////////////////////////////////////////////