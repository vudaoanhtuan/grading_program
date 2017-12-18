#ifndef GRADE_H
#define GRADE_H

#include <iostream>
#include <fstream>
#include <string>
#include <boost\filesystem.hpp>


using namespace std;
using namespace boost::filesystem;

string trim(string str) {
	int start = 0;
	unsigned int count = 0;
	for (count = 0; count < str.length(); count++)
		if (str[count] != ' ' && str[count] != '\t')
			break;
	str = str.erase(start, count);
	
	for (start = str.length() - 1; start >= 0; start--)
		if (str[start] != ' ' && str[start] != '\t')
			break;
	if (start != str.length()) 
		str = str.erase(start+1, str.length() - start);
	return str;
}

bool checkOutput(string pathStdFile, string pathPatternFile) {
	std::ifstream stdFile(pathStdFile);
	std::ifstream patternFile(pathPatternFile);

	string line1, line2;

	while (!stdFile.eof()) {
		getline(stdFile, line1);
		getline(patternFile, line2);
		line1 = trim(line1);
		line2 = trim(line2);
		if (line1.compare(line2))
			return 0;
	}
	return 1;
}

double grade(string testCaseDirPathStr, string stdProgramPathStr) {
	path testCaseDir(testCaseDirPathStr);
	path stdProgram(stdProgramPathStr);
	directory_iterator end;
	int numTC = 0;
	int numPass = 0;
	for (directory_iterator i(testCaseDir); i != end; i++) {
		numTC++; 
		// testcase
		path tcName = *i;
		path tcInputFile(tcName.string() + "\\input");
		path tcOutputFile(tcName.string() + "\\output");

		// student output
		path programDir(stdProgramPathStr);
		programDir = programDir.parent_path();
		string stdOutput = programDir.string() + "\\output";
	
		// chay chuong trinh
		string cm = stdProgramPathStr + " < " + tcInputFile.string() 
					+ " > " + stdOutput;
		system(cm.c_str());

		// check output
		bool pass = checkOutput(tcOutputFile.string(), stdOutput);
		if (pass)
			numPass++;

	}
	return numPass*10.0/numTC;
}

#endif
