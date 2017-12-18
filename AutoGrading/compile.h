#ifndef _COMPILE_H
#define _COMPILE_H
#include <boost/filesystem.hpp>
#include "parser.h"
using namespace boost::filesystem;

bool compile(path project) {
	string proxml = project.string() + "\\pro.xml";
	ProjectFile files = parseProject(proxml);
	string cm = "g++ ";
	for (int i = 0; i < files.header.size(); i++)
		cm = cm + " " + project.string() + "\\" + files.header[i].string();
	for (int i = 0; i < files.source.size(); i++)
		cm = cm + " " + project.string() + "\\" + files.source[i].string();

	cm = cm + " -o " + project.string() +"\\main > " + project.string() + "\\pro.log 2>&1";
	//cout << cm << endl;
	int flag = system(cm.c_str());

	return flag;
}

#endif