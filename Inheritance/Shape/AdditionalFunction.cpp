#include "AdditionalFunction.h"

uint32_t FromStringToUint32(const std::string& outlineColor)
{
	std::istringstream reader(outlineColor);
	uint32_t color = 0;

	reader >> std::hex >> color;

	return color;
}
