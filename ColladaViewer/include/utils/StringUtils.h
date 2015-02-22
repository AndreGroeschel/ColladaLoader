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
#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_

#include "prerequisites.h"

namespace ColladaLoader
{

class StringUtils
{
public:
	StringUtils()
	{

	}
	virtual ~StringUtils()
	{

	}

	static bool equals(const std::string& string1, const std::string& string2)
	{
		if (string1.compare(string2) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//TODO: implement this
	/*
	 * /// Convert string to value using it's stream operator
template <typename T>
T parseString(const std::string& valueAsString) {
    std::stringstream str;
    str << valueAsString;
    T result;
    str >> result;
    return result;
}

inline osg::Vec3 parseVec3String(const std::string& valueAsString)
{
    std::stringstream str;
    str << valueAsString;
    osg::Vec3 result;
    str >> result.x() >> result.y() >> result.z();
    return result;
}

inline osg::Matrix parseMatrixString(const std::string& valueAsString)
{
    std::stringstream str;
    str << valueAsString;
    osg::Matrix result;
    str >> result(0,0) >> result(1,0) >> result(2,0) >> result(3,0)
        >> result(0,1) >> result(1,1) >> result(2,1) >> result(3,1)
        >> result(0,2) >> result(1,2) >> result(2,2) >> result(3,2)
        >> result(0,3) >> result(1,3) >> result(2,3) >> result(3,3);
    return result;
}
	 */
};

}

#endif /* STRINGUTILS_H_ */
