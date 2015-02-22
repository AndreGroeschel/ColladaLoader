/*
 * XMLNode.h
 *
 *  Created on: 26.03.2009
 *      Author: mart
 */

#ifndef XMLNODE_H_
#define XMLNODE_H_

#include "../prerequisites.h"
#include "XMLAttribute.h"

class XMLNode
{
public:
	XMLNode();
	virtual ~XMLNode();

	XMLNode* addChild(XMLNode* childNode);
	bool removeChild(XMLNode* childNode);
	XMLNode* getFirstChild();
	XMLNode* getNextChild();

	void addAttribute(XMLAttribute* attribute);
	bool removeAttribute(XMLAttribute* attribute);
	XMLAttribute* getFirstAttribute();
	XMLAttribute* getNextAttribute();

	void setParent(XMLNode* parent);
	XMLNode* getParent() const;

	void setName(const char* name);
	void setContent(const char* content);

	const char* getName() const;
	const char* getContent() const;


private:
	const char* name_;
	const char* content_;

	XMLNode* parent_;

	std::vector<XMLNode*> children_;
	std::vector<XMLNode*>::iterator childIterator_;

	std::vector<XMLAttribute*>::iterator attributeIterator_;
	std::vector<XMLAttribute*> attributes_;

};

#endif /* XMLNODE_H_ */
