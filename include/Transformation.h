#ifndef _TRANSFORMATION_H_
#define _TRANSFORMATION_H_
#include "glui.h"
#include <string>

class Transformation{


public:
	Transformation(){}
	~Transformation(){}
	virtual void apply() = 0;

};

/*****************************************/

class Translate : public Transformation{

	float x,y,z;

public:
	Translate(float x,float y, float z);
	~Translate(){}
	void apply();
};

/*****************************************/

class Scale : public Transformation{
	
	float x,y,z;

public:
	Scale(float x,float y, float z);
	~Scale(){}
	void apply();
};

/*****************************************/

class Rotate : public Transformation{

	std::string axis;
	float angle;

public:
	Rotate(std::string axis,float angle);
	~Rotate(void);
	void apply();


};



#endif