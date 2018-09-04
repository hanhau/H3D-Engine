#include "../../H3D/XML/XML.hpp"
////////////////////////////////////////////////////////////////
// XML Tree Implementation
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace xml {
		Tree::Tree() {}
		Tree::~Tree() {}

		Node& Tree::getBaseNode() {
			return m_baseNode;
		}

		Node& Tree::getNodeFromId(std::string id) 
		{
			for (auto& const iter : m_baseNode.getChildNodes()) {
				
			}
			return Node();
		}
		std::vector<Node*> Tree::getNodesFromType(std::string type)
		{
			std::vector<Node*> nodes;

			for (auto &iter : m_baseNode.m_childs)
			{
				if (iter.m_name == type)
					nodes.push_back(&iter);

				iter.recSearchFromType(type, nodes);
			}

			return std::move(nodes);
		}
	}
}
/////////////////////////////////////////////////////////////////