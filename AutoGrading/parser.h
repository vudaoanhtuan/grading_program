#ifndef _PARSER_H
#define _PARSER_H
#include <vector>
#include <boost\filesystem.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <fstream>

using namespace std;
using namespace boost::filesystem;
using boost::property_tree::ptree;

typedef vector<path> ListFile;
struct ProjectFile {
	ListFile header;
	ListFile source;
};

ProjectFile parseProject(string pathxml) {
	ProjectFile res;
	std::ifstream file(pathxml);

	ptree pt;
	read_xml(file, pt);

	ptree tree = pt.get_child("project");

	BOOST_FOREACH(ptree::value_type const& v, tree.get_child("header")) {
		if (v.first == "file") {
			string str = v.second.data();
			path f(str);
			res.header.push_back(f);
		}
	}

	BOOST_FOREACH(ptree::value_type const& v, tree.get_child("source")) {
		if (v.first == "file") {
			string str = v.second.data();
			path f(str);
			res.source.push_back(f);
		}
	}



	return res;
}


#endif