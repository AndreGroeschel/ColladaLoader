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
