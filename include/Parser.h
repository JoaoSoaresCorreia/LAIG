#ifndef _PARSER_H_
#define _PARSER_H_

#include "tinyxml.h"

class Parser{

	Parser(char *filename);
	~Parser();

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);

protected:

	//root
	TiXmlDocument* document;
	
	//globals tag
	TiXmlElement* globals;

	//graph tag
	TiXmlElement* graph;

	
	TiXmlElement* initElement; 
	TiXmlElement* matsElement;
	TiXmlElement* textsElement;

	//primitives??
	TiXmlElement* leavesElement;
	TiXmlElement* nodesElement;
	

};

#endif