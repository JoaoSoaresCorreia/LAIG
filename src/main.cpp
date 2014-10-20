#include <iostream>
#include <exception>

#include "CGFapplication.h"
#include "XMLScene.h"
#include "Parser.h"
#include "Globals.h"

using std::cout;
using std::exception;


int main(int argc, char* argv[]) {

	CGFapplication app = CGFapplication();
	
	XMLScene *xml_scene;
	xml_scene = new XMLScene("LAIG_TP1_ANF_T01_G02_v1.anf");
	/**
	if(argc == 2)
		xml_scene = new XMLScene(argv[1]);
	else
		exit(1);
	**/
	try {
		app.init(&argc, argv);
		app.setScene(xml_scene);
		app.setInterface(new CGFinterface());
		app.run();
	}
	catch(GLexception& ex) {
		cout << "Error: " << ex.what();
		return -1;
	}
	catch(exception& ex) {
		cout << "Unexpected error: " << ex.what();
		return -1;
	}

	return 0;
}