#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include <string>
#include <vector>
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace xml {
		class Value {
			union v
			{
				inline v() {}
				inline ~v(){}
				int i; float f; std::string s;
			};
			v m_union;
		public:
			enum class Type {
				_int,_float,_string
			};

			Type type;

			inline Value() {}
			inline ~Value() {}
			inline Value(const Value& val) {
				*this = val;
			}

			inline Value& operator=(const Value& val) {
				memcpy(this, &val, sizeof(val));
				return *this;
			}

			inline Value& operator=(int i) {
				type = Type::_int; m_union.i = i;
			}
			inline Value& operator=(float f) {
				type = Type::_float; m_union.f = f;
			}
			inline Value& operator=(std::string s) {
				type = Type::_string; m_union.s = s;
			}

			template<typename T> T& get() {
				switch (type) {
				case Type::_int: return m_union.i;
				case Type::_float: return m_union.f;
				case Type::_string: return m_union.s;
				}
			}
		};

		struct Attribute {
			std::string name;
			Value       value;
		};

		class Node
		{
			enum class ValueType {
				_int,_float,_string
			};
			
			std::vector<Attribute> m_attributes;
			std::vector<Value>     m_values;
			std::vector<Node>	   m_childs;
			std::string            m_name;

		public:
			H3D_API Node();
			H3D_API Node(const Node& node);
			H3D_API ~Node();

			void H3D_API appendChild(Node &&node);
			
			H3D_API const std::string&  getName();

			H3D_API std::vector<Node>&  getChildVec();
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

			template<typename T> T& getValue(char path[]) const;
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