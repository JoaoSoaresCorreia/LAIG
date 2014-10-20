#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include"CGFtexture.h"
#include<string>
#include<iostream>

using namespace std;

class Texture : public CGFtexture{
	
	string id, file;
	float texlength_s, texlength_t;
	CGFtexture* textureMapped;

public:
	Texture(string file) : CGFtexture(file) {
		this->file=file; 
		try
		{
			textureMapped= new CGFtexture(file);
		}
		catch(...)
		{
			cout <<"Ficheiro " << file << " nao encontrado!" << endl;
		}
	}
	~Texture(){}

	CGFtexture* get_textureMapped(){return this->textureMapped;}

	void set_id(string id){this->id=id; return;}
	string get_id(){return this->id;}

	string get_file(){return this->file;}

	void set_texlength_s(float texlength_s){this->texlength_s=texlength_s; return;}
	float get_texlength_s(){return this->texlength_s;}

	void set_texlength_t(float texlength_t){this->texlength_t=texlength_t; return;}
	float get_texlength_t(){return this->texlength_t;}


};


#endif