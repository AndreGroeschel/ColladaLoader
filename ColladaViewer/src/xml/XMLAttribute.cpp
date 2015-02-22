/*
 * XMLAttribute.cpp
 *
 *  Created on: 26.03.2009
 *      Author: mart
 */

#include "../include/xml/XMLAttribute.h"

XMLAttribute::XMLAttribute(const char* name, const char* value)
{
	setName(name);
	setValue(value);
}

XMLAttribute::~XMLAttribute()
{
	// TODO Auto-generated destructor stub
}

void XMLAttribute::setName(const char* name)
{
	name_ = name;
}

void XMLAttribute::setValue(const char* value)
{
	value_ = value;
}

const char* XMLAttribute::getName()
{
	return name_;
}

const char* XMLAttribute::getValue()
{
	return value_;
}
