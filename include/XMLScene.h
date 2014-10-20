#ifndef _XMLSCENE_H_
#define _XMLSCENE_H_

#define BUFFSIZE 256
#include "Parser.h"
#include "CGFscene.h"
#include "CGFshader.h"

class XMLScene : public CGFscene{
	
	char *filename;
	Parser *p;

public:
	XMLScene(char *filename);
	~XMLScene(){}
	void loadFile();
	Parser* getParser(){return this->p;}
	void init();
	void display();
	void set_upGlobals();
	void set_upLights();

};



#endif