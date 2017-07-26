#include <FDCore.h>

#define _CRT_SECURE_NO_WARNINGS

#include <stdexcept>

#include <algorithm>
#include <cctype>



#include <regex>


char *FDCore::readFile(FILE *file)
{
		if (!file)
			throw std::invalid_argument("The file descriptor is not set");
	
		char *output = nullptr;
		int count = 0;
	
	
		fseek(file, 0, SEEK_END);
		count = ftell(file);
		rewind(file);
	
		if(!count)
			throw std::invalid_argument("The file is empty");
	
		output = new char[count + 1]();
		fread(output, sizeof(char), count, file);
	
		return output;
}

std::string & FDCore::ltrim(std::string & s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}


std::string & FDCore::rtrim(std::string & s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

std::string& FDCore::uniformSpaces(std::string& s)
{
	std::regex re("(\\s+)");
	s = std::regex_replace(s, re, " ");
	return s;
}

std::ostream & FDCore::cleanStream(std::istream & in, std::ostream & out)
{
	std::string line;
	if (std::getline(in, line))
	{
		prepareString(line);
		out << line;

		while (std::getline(in, line))
		{
			prepareString(line);
			out << std::endl << line;
		}
	}

	return out;
}

uint32_t FDCore::fnv_32a_str(char *str, uint32_t hval)
{
	unsigned char *s = reinterpret_cast<unsigned char *>(str);
	while (*s)
	{
		hval ^= static_cast<uint32_t>(*s);
		s++;

		hval *= fnv32_prime();
	}

	return hval;
}