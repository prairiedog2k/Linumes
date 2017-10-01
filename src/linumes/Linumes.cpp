#include <cstdlib>
#include <iostream>

#include "LinumesModeManager.h"
#include "xmlParser.h"

#include "boss/Boss.h"

#ifdef MING_ENTRY
#include "Windows.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int iCmdShow)
{
    return main(0, NULL);
}
#endif
using namespace std;
int main (int argc, char *argv[]) {
	std::cout << "LINUMES developer@mountain 2007" << endl;
#ifdef DEBUG
	std::cout << "(DEBUG MODE ENABLED)" << endl;
#endif 	
	
	ModeManager *lmm = new LinumesModeManager( "LinumesConfiguration.xml");
	if ( lmm->init() ) {
		lmm->run();
	}	
	delete lmm;

	return 0;
}
