#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/optional.hpp>

std::string data(const char* filepath, const char* directory) {
	boost::property_tree::ptree pt;
	read_json(filepath, pt);
	auto value = pt.get_optional<std::string>(directory);
	return value.get();
}

int main(void) {
	std::cout << data("test.json", "Data.str") << std::endl;
	return 0;
}