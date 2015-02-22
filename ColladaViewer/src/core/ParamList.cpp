/*
The MIT License (MIT)

Copyright (c) 2010 Andre Groeschel

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "core/ParamList.h"

namespace ColladaLoader
{

ParamList::ParamList()
{
}

ParamList::~ParamList()
{
	parameterMap_.clear();
}

void ParamList::addParameter(const std::string& paramName, boost::any value)
{
	parameterMap_[paramName] = value;
}

boost::any ParamList::getValue(const std::string& paramName)
{
	if (parameterMap_.end() != parameterMap_.find(paramName))
	{
		return parameterMap_[paramName];
	}
	else
	{
		return boost::any();
	}
}

void ParamList::deleteParameter(const std::string& paramName)
{
	if (parameterMap_.end() != parameterMap_.find(paramName))
	{
		parameterMap_.erase(paramName);
	}
	else
	{
		std::stringstream str;
		str << "Cannot delete Parameter " << paramName
		<< " because it does not exist";
		ERROR(str.str());
	}
}

const bool ParamList::hasParameter(const std::string& paramName)
{
	if (parameterMap_.end() != parameterMap_.find(paramName))
		return true;
	else
		return false;
}

}
