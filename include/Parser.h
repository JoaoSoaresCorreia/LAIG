#ifndef _PARSER_H_
#define _PARSER_H_

#include "tinyxml.h"
#include <iostream>
#include <vector>
#include "Globals.h"
#include "PerspectiveCamera.h"
#include "OrthoCamera.h"
#include "OmniLight.h"
#include "SpotLight.h"
#include "Texture.h"
#include "Appearance.h"

using namespace std;

class Parser{
public:
	Parser(char *filename);
	~Parser();
	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
	
	/*Globals*/
	Globals getGlobals(){return globals_obj;}
	vector<PerspectiveCamera> get_p_cameras(){return p_cameras;}
	vector<OrthoCamera> get_o_cameras(){return o_cameras;}
	vector<OmniLight> get_o_lights(){return o_lights;}
	vector<SpotLight> get_s_lights(){return s_lights;}
	vector<Texture> get_textures(){return textures_obj;}
	vector<Appearance> get_appearances(){return appearances_obj;}

protected:

	/*Objects*/
	Globals globals_obj;
	
	vector<PerspectiveCamera> p_cameras;
	vector<OrthoCamera> o_cameras;
	vector<OmniLight> o_lights;
	vector<SpotLight> s_lights;
	vector<Texture> textures_obj;
	vector<Appearance> appearances_obj;
	
	
	
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