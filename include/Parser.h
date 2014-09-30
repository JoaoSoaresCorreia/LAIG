#ifndef _PARSER_H_
#define _PARSER_H_

#include "tinyxml.h"

class Parser{

	Parser(char *filename);
	~Parser();

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);

protected:

	TiXmlDocument* document;

	TiXmlElement* initElement; 
	TiXmlElement* matsElement;
	TiXmlElement* textsElement;
	TiXmlElement* leavesElement;
	TiXmlElement* nodesElement;
	TiXmlElement* graphElement;

};

#endif