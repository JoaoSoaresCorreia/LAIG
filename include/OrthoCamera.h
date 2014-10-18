#ifndef _ORTHOCAMERA_H_
#define _ORTHOCAMERA_H_

#include<string>
#include "CGFcamera.h"
using namespace std;

class OrthoCamera : public CGFcamera{

	string id, direction;
	float near, far, left, right, top, bottom;

public:

	OrthoCamera(){}
	~OrthoCamera(){}

	void set_id(string id){this->id = id; return;}
	string get_id(){return id;}

	void set_direction(string direction){this->direction = direction; return;}
	string get_direction(){return direction;}

	void set_near(float near){this->near = near; return;}
	float get_near(){return near;}

	void set_far(float far){this->far = far; return;}
	float get_far(){return far;}

	void set_left(float left){this->left = left; return;}
	float get_left(){return left;}

	void set_right(float right){this->right = right; return;}
	float get_right(){return right;}

	void set_top(float top){this->top = top; return;}
	float get_top(){return top;}

	void set_bottom(float bottom){this->bottom = bottom; return;}
	float get_bottom(){return bottom;}
};


#endif