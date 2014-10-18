#include <iostream>
#include <exception>

#include "CGFapplication.h"
#include "DemoScene.h"
#include "Parser.h"
#include "Globals.h"

using std::cout;
using std::exception;


int main(int argc, char* argv[]) {

	Parser *p = new Parser("graph_beta.anf");
	printf("Done, Created!");
	cout<<"OrthoID= "<< p->get_o_cameras()[0].get_id() << endl;


/*
	CGFapplication app = CGFapplication();

	try {
		app.init(&argc, argv);

		app.setScene(new DemoScene());
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

*/
	return 0;
}