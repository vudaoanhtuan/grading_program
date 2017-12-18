#include <iostream>
#include <boost\filesystem.hpp>
#include "scan.h"
#include <boost\date_time\posix_time\posix_time.hpp>
#include "grade.h"
#include <vector>
#include "parser.h";
#include "prepare.h";
#include "compile.h"
#include "run.h";
#include <fstream>
#include <string>

int main(int narg, char* args[]) {
	if (narg < 3) {
		cout << "missing argument";
		return 1;
	} 
	string std_submit = string(args[1]) ;
	string testcase = string(args[2]);
	run(std_submit, testcase);
	return 0;
}

