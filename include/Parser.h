#ifndef _PARSER_H_
#define _PARSER_H_

#include "tinyxml.h"

class Parser{
public:
	Parser(char *filename);
	~Parser();
	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);

protected:

	//root
	TiXmlDocument* document;
	
	//globals tag
	TiXmlElement* globals;

	//cameras tag
	TiXmlElement* cameras;

	//lights tag
	TiXmlElement* lights;
	
	//textures tag
	TiXmlElement* textures;

	//appearances tag
	TiXmlElement* appearances;

	//graph tag
	TiXmlElement* graph;

	////nodes tag
	TiXmlElement* node;
	
	

};

#endif