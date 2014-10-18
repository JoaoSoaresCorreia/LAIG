#include "Globals.h"


void Globals::set_background(float b1, float b2, float b3, float b4){

	this->background[0] = b1;
	this->background[1] = b2;
	this->background[2] = b3;
	this->background[3] = b4;

	return;
}

void Globals::set_mode(string mode){

	if(mode == "fill"){
		this->mode = GL_FILL;
	}
	else if(mode == "line"){
		this->mode = GL_LINE;
	}
	else if(mode == "point"){
		this->mode = GL_POINT;
	}
	return;
}

void Globals::set_shading(string shading){
	
	if(shading == "flat")
	{
		this->shading = GL_FLAT;
	}
	else if(shading == "gouraud")
	{
		this->shading = GL_SMOOTH;
	}
	return;
}



void Globals::set_face(string face){
	
	if(face == "none"){
		this->face = GL_NONE;
	}
	else if(face == "back"){
		this->face = GL_BACK;
	}
	else if(face == "front"){
		this->face = GL_FRONT;
	}
	else if(face == "both"){
		this->face = GL_FRONT_AND_BACK;
	}
	return;
}

void Globals::set_order(string order){

	if(order == "ccw"){
		this->order = GL_CCW;
	}
	else if(order == "cw"){
		this->order = GL_CW;
	}
	return;
}

void Globals::set_ambient(float a1, float a2, float a3, float a4){

	this->ambient[0] = a1;
	this->ambient[1] = a2;
	this->ambient[2] = a3;
	this->ambient[3] = a4;

	return;
}