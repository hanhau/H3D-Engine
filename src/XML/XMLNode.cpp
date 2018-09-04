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

		std::vector<Node>& Node::getChildNodes() {
			return m_childs;
		}
		std::vector<Value>& Node::getValueVec() {
			return m_values;
		}
		std::vector<Attribute>& Node::getAttributeVec() {
			return m_attributes;
		}

		void Node::recSearchFromId(std::string id,Node* out) {
			bool has_id = false;
			h3d::xml::Value id_val;
			for (auto & iter : m_attributes)
				if (iter.name == "id") {
					has_id = true;
					id_val = iter.value;
				}

			//if (has_id && id_val.get<std::string>() == (std::string)"")
			//	out = this;
		}
		void Node::recSearchFromType(std::string type,std::vector<Node*>& outvecs)
		{
			if (this->m_name == type)
				outvecs.push_back(this);

			for (auto& iter : m_childs)
				iter.recSearchFromType(type, outvecs);
		}
	}
}
/////////////////////////////////////////////////////////////////