#ifndef _SPOTLIGHT_H_
#define _SPOTLIGHT_H_
#include "CGFlight.h"
#include<string>
using namespace std;

class SpotLight{

	string id;
	bool enabled, marker;
	float pos[3];
	float target[3];
	float angle, exponent;
	/*components*/
	float ambient[4];
	float diffuse[4];
	float specular[4];

	CGFlight* light;

public:
	SpotLight(){}
	~SpotLight(){}

	void set_id(string id){this->id=id; return;}
	string get_id(){return this->id;}


	void set_pos(float pos1, float pos2, float pos3);
	float get_pos(int n){return this->pos[n];}

	void set_target(float t1, float t2, float t3);
	float get_target(int n){return this->target[n];}

	void set_enabled(bool enabled){this->enabled = enabled; return;}
	bool get_enabled(){return this->enabled;}

	void set_marker(bool marker){this->marker = marker; return;}
	bool get_marker(){return this->marker;}

	void set_angle(float angle){this->angle = angle; return;}
	float get_angle(){return this->angle;}

	void set_exponent(float exponent){this->exponent = exponent; return;}
	float get_exponent(){return this->exponent;}

	/*Components*/

	void set_ambient(float v1, float v2, float v3, float v4);
	float get_ambient(int n){return this->ambient[n];}

	void set_diffuse(float v1, float v2, float v3, float v4);
	float get_diffuse(int n){return this->diffuse[n];}

	void set_specular(float v1, float v2, float v3, float v4);
	float get_specular(int n){return this->specular[n];}

	/**/

	void create(){

		glLightfv(GL_LIGHT0, GL_POSITION, this->pos);
		glLightfv(GL_LIGHT0, GL_AMBIENT, this->ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, this->diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, this->specular);
		glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION, this->target);
		glLightf(GL_LIGHT0,GL_SPOT_CUTOFF, this->angle);
		glLightf(GL_LIGHT0,GL_SPOT_EXPONENT, this->exponent);

		light = new CGFlight(GL_LIGHT0, this->pos, this->target);

	}

	void enable(){this->light->enable(); return;}
	void draw(){this->light->draw(); return;}
	void update(){this->light->update(); return;}
	void disable(){this->light->disable(); return;}

};



#endif