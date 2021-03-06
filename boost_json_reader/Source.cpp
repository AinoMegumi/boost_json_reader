#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/optional.hpp>
#include <codecvt>
#include <stdexcept>
#include <type_traits>

std::string data(boost::property_tree::ptree& pt, const char* directory) {
	return pt.get_optional<std::string>(directory).get();
}

static std::wstring get_text_from_json(boost::property_tree::ptree& p, std::string tag) {
	auto target = p.get_optional<std::string>(tag);
	if (!target) throw std::runtime_error("json reading failed");
	static_assert(sizeof(wchar_t) == 2, "In function 'read json data' : Please check usage of 'std::codecvt_utf8_utf16'");
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert;
	auto str = convert.from_bytes(target.get());
	return str;
}

static int get_int_from_json(boost::property_tree::ptree& p, std::string tag) {
	auto target = p.get_optional<int>(tag);
	if (!target) throw std::runtime_error("json reading failed");
	return target.get();
}

int main(void) {
	boost::property_tree::ptree pt;
	try {
		read_json("test.json", pt);
		auto p = pt.get_child("Data");
		std::cout << data(p, "str") << std::endl << std::endl;
		std::wcout.imbue(std::locale(""));
		for (auto& child : p.get_child("info")) {
			std::wcout
				<< "id: " << get_int_from_json(child.second, "id") << std::endl
				<< "name:" << get_text_from_json(child.second, "name") << std::endl << std::endl;
		}
		return 0;
	}
	catch (std::exception &er) {
		std::cout << er.what() << std::endl;
		return -1;
	}
}