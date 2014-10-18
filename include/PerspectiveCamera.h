//#pragma once
#ifndef _PERSPECTIVECAMERA_H_
#define _PERSPECTIVECAMERA_H_

#include<string>
#include "CGFcamera.h"
using namespace std;

class PerspectiveCamera : public CGFcamera{

	string id;
	float near, far, angle;
	float pos[3];
	float target[3];

public:

	PerspectiveCamera(){}
	~PerspectiveCamera(){}

	void set_id(string id){this->id = id; return;}
	string get_id(){return id;}

	void set_pos(float pos1, float pos2, float pos3);
	float get_pos(int n){return pos[n];}

	void set_target(float t1, float t2, float t3);
	float get_target(int n){return target[n];}

	void set_near(float near){this->near = near; return;}
	float get_near(){return near;}

	void set_far(float far){this->far = far; return;}
	float get_far(){return far;}

	void set_angle(float angle){this->angle = angle; return;}
	float get_angle(){return angle;}
};

#endif