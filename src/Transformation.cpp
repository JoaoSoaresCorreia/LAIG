#include "Transformation.h"

Translate::Translate(float x,float y, float z){

	this->x=x;
	this->y=y;
	this->z=z;

}

void Translate::apply()
{
	glTranslatef(x,y,z);
}

/******************************************/

Scale::Scale(float x,float y, float z){

	this->x=x;
	this->y=y;
	this->z=z;

}

/******************************************/

void Scale::apply()
{
	glScalef(x,y,z);
}

/******************************************/

Rotate::Rotate(std::string axis,float angle)
{
	this->axis=axis;
	this->angle=angle;
}

void Rotate::apply()
{

	if(axis=="x")
		glRotatef(angle,1,0,0);
	else if(axis=="y")
		glRotatef(angle,0,1,0);
	else if(axis=="z")
		glRotatef(angle,0,0,1);

}

