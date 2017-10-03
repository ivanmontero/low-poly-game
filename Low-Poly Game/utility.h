#pragma once
#include <vector>
#include <sstream>
#include <string>

std::vector<std::string> split(std::string& str, const char& c) {
	std::string buff = "";
	std::vector<std::string> v;
	for (auto n : str) {
		if (n != c) buff += n;
		else if (n == c && buff != "") {
			v.push_back(buff);
			buff = "";
		}
	}
	if (buff != "") v.push_back(buff);
	return v;
}
