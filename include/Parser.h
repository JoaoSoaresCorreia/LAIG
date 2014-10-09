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
	
	////light tag
	TiXmlElement* light;

	//textures tag
	TiXmlElement* textures;

	//texture tag
	TiXmlElement* texture;

	//appearances tag
	TiXmlElement* appearances;

	////appearances tag
	TiXmlElement* appearance;

	//////component

	//graph tag
	TiXmlElement* graph;

	////node tag
	TiXmlElement* node;

	
	
	

};

#endif