#include "OmniLight.h"

void OmniLight::set_pos(float pos1, float pos2, float pos3){

	this->pos[0] = pos1;
	this->pos[1] = pos2;
	this->pos[2] = pos3;

	return;
}

void OmniLight::set_ambient(float v1, float v2, float v3, float v4){

	this->ambient[0]=v1;
	this->ambient[1]=v2;
	this->ambient[2]=v3;
	this->ambient[3]=v4;

	return;
}

void OmniLight::set_diffuse(float v1, float v2, float v3, float v4){

	this->diffuse[0]=v1;
	this->diffuse[1]=v2;
	this->diffuse[2]=v3;
	this->diffuse[3]=v4;

	return;
}

void OmniLight::set_specular(float v1, float v2, float v3, float v4){

	this->specular[0]=v1;
	this->specular[1]=v2;
	this->specular[2]=v3;
	this->specular[3]=v4;

	return;
}