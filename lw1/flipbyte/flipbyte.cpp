#include "pch.h"
#include <iostream>
#include <cctype>

bool IsNumber(const std::string& num)
{
	for (unsigned i = 0; i < num.length(); ++i)
	{
		if (!std::isdigit(num[i]))
		{
			return false;
		}
	}
	return true;
}

uint8_t FlipByte(uint8_t byte)
{
	uint8_t invertedBits = 0;
	for (unsigned i = 0; i < 8; ++i)
	{
		invertedBits <<= 1;
		invertedBits |= (byte & 0b00000001);
		byte >>= 1;
	}
	return invertedBits;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Invalid arguments count" << std::endl
				  << "Usage: flipbyte.exe <input byte>" << std::endl;
		return 1;
	}

	const std::string inputData = argv[1];

	if (!IsNumber(inputData))
	{
		std::cerr << "Invalid argument: <input byte> is not a number" << std::endl;
		return 1;
	}

	if ((atoi(inputData.c_str()) < 0) || (atoi(inputData.c_str()) > 255))
	{
		std::cerr << "<input byte> must be 0..255" << std::endl;
		return 1;
	}

	printf("%u\n", FlipByte(static_cast<uint8_t>(atoi(inputData.c_str()))));

	return 0;
}