#ifndef _RUN_H
#define _RUN_H

#include <boost/filesystem.hpp>
#include <string>
#include "prepare.h"
#include "compile.h";

using namespace std;
using namespace boost::filesystem;

void run(string stdDir, string testcaseDir) {
	
	int compileError = compile(stdDir);

	string logFileStr = stdDir + "\\pro.log";
	string stdOutputDir = stdDir + "\\output";

	create_directory(stdOutputDir);


	if (compileError) {
		// compile error, break
		cout << "compile error";
		return;
	}
	else {
		directory_iterator end;
		int numPass = 0;
		int totalTest = 0;
		for (directory_iterator i(testcaseDir); i != end; i++) {
			totalTest++;
			// testcase
			path tcName = *i;
			path tcInputFile(tcName.string() + "\\input");
			path tcOutputFile(tcName.string() + "\\output");

			// student output


			string stdOutput = stdOutputDir + "\\" + tcName.filename().string();
			// cout << stdOutput << endl;
			cout << "grading test " << tcName.filename().string();

			// chay chuong trinh
			string cm = stdDir + "\\main < " + tcInputFile.string()
				+ " > " + stdOutput;
			system(cm.c_str());

			// check ouput here
			bool pass = checkOutput(tcOutputFile.string(), stdOutput);
			if (pass) {
				numPass++;
				cout << ": pass\n";
			}
			else {
				cout << ": fail\n";
			}
			
		}
		cout << "Ratio: " << numPass << "/" << totalTest << endl;
		cout << "Total: " << numPass * 10.0 / totalTest << endl;
	}

}

#endif