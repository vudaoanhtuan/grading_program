#ifndef SCAN
#define SCAN

#include <boost\filesystem.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <boost\date_time\posix_time\posix_time.hpp>
#include "grade.h"

using namespace std;
using namespace boost::filesystem;
using namespace boost::posix_time;
using namespace boost::gregorian;

#define _CRT_SECURE_NO_WARNINGS

void scanDir() {
	
	std::ifstream config("./config.ini");
	string testcaseDirStr;
	string studentDirStr;
	string filename;
	getline(config, testcaseDirStr);
	getline(config, studentDirStr);
	getline(config, filename);
	config.close();

	path testcaseDir(testcaseDirStr);
	path studentDir(studentDirStr);

	while (1) {
		directory_iterator end;
		for (directory_iterator i(studentDir); i != end; i++) {
			path stdPath = (*i);
			string stdPathStr = stdPath.string();
			string newFileStr = stdPathStr + "\\" + filename;
			path newFilePath(newFileStr);
			if (exists(newFilePath)) {

				// bien dich
				// warning: chua check thu muc bin ton tai
				string programPathStr = stdPathStr + "\\bin\\program.exe";
				cout << programPathStr << endl;
				string cm = "g++ " + newFileStr + " -o " + programPathStr;
				cout << cm << endl;
				system(cm.c_str());

				// tao thu muc thoi gian
				ptime now = second_clock::local_time();
				string nowStr = to_iso_string(now);
				path newDir(stdPathStr + "\\" + nowStr);
				create_directory(newDir);

				// move file vao thu muc
				path newFileDir(newDir.string() + "\\" + filename);	
				copy_file(newFilePath, newFileDir);
				remove(newFilePath);

				std::cout << "Compiled!" << endl;
				
				// cham diem
				cout << grade(testcaseDir.string(), programPathStr) << endl;
				/*
					ghi file
					...
				*/
			}
		}
	}

}

#endif // !SCAN
