#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include"CGFtexture.h"
#include<string>

using namespace std;

class Texture : public CGFtexture{
	
	string id, file;
	float texlength_s, texlength_t;

public:
	Texture(){}
	~Texture(){}

	void set_id(string id){this->id=id; return;}
	string get_id(){return this->id;}

	void set_file(string file){this->file=file; return;}
	string get_file(){return this->file;}

	void set_texlength_s(float texlength_s){this->texlength_s=texlength_s; return;}
	float get_texlength_s(){return this->texlength_s;}

	void set_texlength_t(float texlength_t){this->texlength_t=texlength_t; return;}
	float get_texlength_t(){return this->texlength_t;}


};


#endif