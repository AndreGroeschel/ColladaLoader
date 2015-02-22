/*
 * XMLAttribute.h
 *
 *  Created on: 26.03.2009
 *      Author: mart
 */

#ifndef XMLATTRIBUTE_H_
#define XMLATTRIBUTE_H_

#include "../prerequisites.h"

class XMLAttribute
{
public:
	XMLAttribute(const char* name = "", const char* value = "");
	virtual ~XMLAttribute();

	void setName(const char* name);
	void setValue(const char* value);

	const char* getName();
	const char* getValue();

private:
	const char* name_;
	const char* value_;
};

#endif /* XMLATTRIBUTE_H_ */
