//#pragma once
#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include<string>
#include<GL/glut.h>
using namespace std;

class Globals{

	/*drawing*/
	float background[4];
	int mode, shading;
	/*culling*/
	int face, order;
	/*lighting*/
	float ambient[4];
	bool doublesided, local,enabled;

public:

	Globals(){}
	~Globals(){}
	
	/*drawing*/
	void set_background(float b1, float b2, float b3, float b4);
	float get_background(int n){return background[n];}

	void set_mode(string mode);
	const int& get_mode() const{return mode;}

	void set_shading(string shading);
	const int& get_shading() const{return shading;}
	
	/*culling*/
	void set_face(string face);
	const int& get_face() const{return face;}

	void set_order(string order);
	const int& get_order() const{return order;}
	
	/*lighting*/
	void set_ambient(float a1, float a2, float a3, float a4);
	float get_ambient(int n){return ambient[n];}

	void set_doublesided(bool doublesided){this->doublesided=doublesided; return;}
	bool get_doublesided(){return doublesided;}

	void set_local(bool local){this->local=local; return;}
	bool get_local(){return local;}

	void set_enabled(bool enabled){this->enabled=enabled; return;}
	bool get_enabled(){return enabled;}
};



#endif