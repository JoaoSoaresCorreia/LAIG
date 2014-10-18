#include "PerspectiveCamera.h"


void PerspectiveCamera::set_pos(float pos1, float pos2, float pos3){

	this->pos[0] = pos1;
	this->pos[1] = pos2;
	this->pos[2] = pos3;

	return;
}

void PerspectiveCamera::set_target(float t1, float t2, float t3){

	this->target[0] = t1;
	this->target[1] = t2;
	this->target[2] = t3;

	return;
}