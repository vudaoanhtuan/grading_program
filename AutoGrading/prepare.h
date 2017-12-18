#ifndef _PREPARE_H
#define _PREPARE_H

#include <string>
#include <boost/filesystem.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace std;
using namespace boost::filesystem;
using namespace boost::posix_time;

void genXML(string dir) {
	string xmlStr = dir + "/pro.xml";
	std::ofstream xml;
	xml.open(xmlStr.c_str());

	xml << "<?xml version=\"1.0\"?>" << endl;
	xml << "<project>" << endl;

	recursive_directory_iterator end;

	xml << "\t<header>" << endl;
	for (recursive_directory_iterator i(dir); i != end; i++) {
		path file = *i;
		//file = file.relative_path();
		string str = file.string();

		if (str.find(".h") != string::npos || str.find(".hpp") != string::npos) {
			xml << "\t\t<file>" << str << "<file>" << endl;
		}
	}
	xml << "\t<header>" << endl;

	xml << "\t<source>" << endl;
	for (recursive_directory_iterator i(dir); i != end; i++) {
		path file = *i;
		//file = file.generic_string();
		string str = file.string();

		if (str.find(".c") != string::npos || str.find(".cpp") != string::npos) {
			xml << "\t\t<file>" << str << "<file>" << endl;
		}
	}
	xml << "\t<source>" << endl;
	xml << "<project>" << endl;
	xml.close();
}

string prepare(string stdDir) {

	ptime now = second_clock::local_time();
	string nowStr = to_iso_string(now);
	string timeDir = stdDir + "\\" + nowStr;
	path newDir(timeDir);
	create_directory(newDir);

	// move file vao thu muc

	string cm = "move " + stdDir + "\\submit\\* " + timeDir;
	system(cm.c_str());
	return timeDir;
}

#endif