#include "StringUtilites.h"

std::string RemoveExtraBlanks(const std::string& input)
{
	std::string result;
	result.reserve(input.length());

	bool inSpace = false;
	bool hasContent = false;

	for (char c : input)
	{
		if (std::isspace(static_cast<unsigned char>(c)))
		{
			if (inSpace && hasContent)
			{				
				continue;
			}
			if (hasContent)
			{				
				result += ' ';
				inSpace = true;
			}			
		}
		else
		{
			result += c;
			inSpace = false;
			hasContent = true;
		}
	}
	
	if (!result.empty() && result.back() == ' ')
	{
		result.pop_back();
	}

	return result;
}
