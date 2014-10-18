#ifndef _APPEARANCE_H_
#define _APPEARANCE_H_

#include <string>

using namespace std;

class Appearance{

	string id;
	float shininess;
	string textureref;
	float ambient[4];
	float diffuse[4];
	float specular[4];

public:

	Appearance(){}
	~Appearance(){}

	void set_id(string id){this->id=id; return;}
	string get_id(){return this->id;}

	void set_shininess(float shininess){this->shininess = shininess; return;}
	float get_shininess(){return this->shininess;}

	void set_textureref(string textureref){this->textureref=textureref; return;}
	string get_textureref(){return this->textureref;}

	/*Components*/

	void set_ambient(float v1, float v2, float v3, float v4);
	float get_ambient(int n){return this->ambient[n];}

	void set_diffuse(float v1, float v2, float v3, float v4);
	float get_diffuse(int n){return this->diffuse[n];}

	void set_specular(float v1, float v2, float v3, float v4);
	float get_specular(int n){return this->specular[n];}
	
};



#endif