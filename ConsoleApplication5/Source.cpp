#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/optional.hpp>

std::string data(boost::property_tree::ptree& pt, const char* directory) {
	return pt.get_optional<std::string>(directory).get();
}

int main(void) {
	boost::property_tree::ptree pt;
	read_json("test.json", pt);
	std::cout << data(pt, "Data.str") << std::endl << std::endl;

	for (auto& child : pt.get_child("Data.info")) {
		std::cout
			<< "id: " << child.second.get_optional<int>("id").get() << std::endl
			<< "name:" << child.second.get_optional<std::string>("name").get() << std::endl;

	}
	return 0;
}