#include "FileUtils.h"

#include <cstdlib>
#include <iostream>
#include <fstream>


bool fileExists(std::string myFileName) {
	bool bRetVal = true;
	std::ifstream inp;
	inp.open(myFileName.c_str(), std::ifstream::in);
	inp.close();
	if (inp.fail() ) {
		bRetVal = false;
	}	
	return bRetVal; 
}
