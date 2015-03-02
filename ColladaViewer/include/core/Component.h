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

#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <boost/enable_shared_from_this.hpp>
#include "prerequisites.h"

namespace ColladaLoader
{
/**
* The @c Component class provides the base for extending behavior of nodes
*/
class Component : public boost::enable_shared_from_this<Component>
{
public:
	Component(Node* ownerNode, ParamListPtr parameters);
	virtual ~Component();

	virtual const bool initialise(void) = 0;
	void setInitialised(const bool& isInitialised);
	const bool isInitialised(void);

	void setOwnerNode(Node* entity);
	Node* getOwnerNode(void);

	void setType(const std::string& type);
	const std::string& getType();

protected:
    Node* ownerNode_;
    ParamListPtr parameters_;
    bool initialised_;

    std::string type_;
};
}

#endif /* COMPONENT_H_ */
