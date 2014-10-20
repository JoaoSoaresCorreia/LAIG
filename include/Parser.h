#ifndef _PARSER_H_
#define _PARSER_H_

#include "tinyxml.h"
#include <iostream>
#include <vector>
#include <map>
#include "Globals.h"
#include "PerspectiveCamera.h"
#include "OrthoCamera.h"
#include "OmniLight.h"
#include "SpotLight.h"
#include "Texture.h"
#include "Appearance.h"
#include "Node.h"
#include "Transformation.h"

using namespace std;

class Parser{
public:
	Parser(char *filename);
	~Parser();

	/*Globals*/
	Globals getGlobals(){return globals_obj;}
	vector<PerspectiveCamera> get_p_cameras(){return p_cameras;}
	vector<OrthoCamera> get_o_cameras(){return o_cameras;}
	vector<OmniLight> get_o_lights(){return o_lights;}
	vector<SpotLight> get_s_lights(){return s_lights;}
	vector<Texture* > get_textures(){return textures_obj;}
	vector<Appearance* > get_appearances(){return appearances_obj;}


	Appearance* setAppearance(string id);
	CompositeNode* getDescendent(string noderef);
	CGFtexture* get_refTexure(string textureref);
	float get_textl_s(string textureref);
	float get_textl_t(string textureref);

	
	CompositeNode get_root_node(){return this->root_node;}

protected:

	/*ROOT NODE!*/

	CompositeNode root_node;

	/*Objects*/
	Globals globals_obj;
	
	vector<PerspectiveCamera> p_cameras;
	vector<OrthoCamera> o_cameras;
	vector<OmniLight> o_lights;
	vector<SpotLight> s_lights;
	vector<Texture* > textures_obj;/*ou texturas mesmo CGFTEXTURE!?!?*/
	vector<Appearance* > appearances_obj;

	/*temp nodes*/

	map<string, CompositeNode> temporary_nodes;
	vector<Node *> nodes_obj;
	vector<const char *> descendentes_id;
	/*for each node*/
	
	
	
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

	///////transform tag
	TiXmlElement* transform;

	
	
	

};

#endif