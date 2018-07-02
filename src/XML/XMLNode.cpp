#include "../../H3D/XML/XML.hpp"

/////////////////////////////////////////////////////////////////
// xml::Node Implementation
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace xml {
		Node::Node(){}
		Node::~Node(){}
		Node::Node(const Node& node) {
			this->m_childs = node.m_childs;
			this->m_name = node.m_name;
			this->m_attributes = node.m_attributes;
			this->m_values = node.m_values;
		}

		void Node::appendChild(Node &&node) {
			m_childs.push_back(std::move(node));
		}

		const std::string& Node::getName() {
			return m_name;
		}

		std::vector<Node>& Node::getChildVec() {
			return m_childs;
		}
		std::vector<Value>& Node::getValueVec() {
			return m_values;
		}
		std::vector<Attribute>& Node::getAttributeVec() {
			return m_attributes;
		}
	}
}
/////////////////////////////////////////////////////////////////