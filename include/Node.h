#ifndef _NODE_H
#define _NODE_H
#include "Transformation.h"
#include "Texture.h"
#include "Appearance.h"
#include "CGFobject.h"
#include <math.h> 
#include "Point.h"
#define PI acos(-1.0)
#include <string>
#include <vector>

using namespace std;

class Node{

	string id;
	//vector<Transformation *> transforms;
	/*Em principio nao preciso da string de baixo!*/
	//string appearanceref_texture;
	//vector<Texture *> textures;
	
	
public:
	float transMatrix[16];
	
	Node(){}
	~Node(){}

	Texture* get_texture(string textureref);

	void setID(string id){this->id=id; return;}
	string getID(){return this->id;}
	void setTransMatrix(float t_matrix[16]){
		
		for(unsigned int i=0;i<16;i++)
		{

			transMatrix[i]=t_matrix[i];
		}
	}

	//vector<Texture *> get_textures(){return this->textures;}

	virtual void draw(Appearance *father_ap) = 0;
};


class CompositeNode : public Node{

	vector<Transformation *> transforms;
	vector<Appearance *> le_appearance;
	vector<Node *> descendents;

public:

	CompositeNode(){}
	~CompositeNode(){}
	
	void set_id(string id){Node::setID(id); return;}
	string get_id(){return Node::getID();}

	void push_tranformation(Transformation *t){transforms.push_back(t); return;}

	void push_appearance(Appearance *p){le_appearance.push_back(p); return;}

	void push_descendents(Node *n){descendents.push_back(n); return;}

	Appearance * get_le_appearance(){return this->le_appearance[0];}

	void draw(Appearance *father_ap);

};



class Rectangle : public Node, public CGFobject{

	Appearance *ap;

	float x1, y1;
	float x2, y2;
	float comp, larg;
public:
	Rectangle(){this->ap=NULL;}
	~Rectangle(){}

	void draw(Appearance *father_ap);

	void set_x1(float x1){this->x1=x1;}
	void set_y1(float y1){this->y1=y1;}
	void set_x2(float x2){this->x2=x2;}
	void set_y2(float y2){this->y2=y2;}
	float get_comp(){return abs(this->x2-this->x1);}
	float get_larg(){return this->y2-this->y1;}

};


class Triangle : public Node, public CGFobject{
	
	Appearance *ap;

	Point point1;
	Point point2;
	Point point3;
	vector<Point> normals;
	float textS,textT;
	float a1,b1,c1,beta;
public:
	Triangle(){}
	Triangle(float a[3],float b[3],float c[3]);
	void normalCalc();
	~Triangle(){}
	void draw(Appearance *father_ap);
};

class Cylinder:public Node, public CGFobject {

	float top;
    float base;
	float height;
	int slices;
	int stacks;
	float deltaRadius;
	vector <vector<Point>> points;
	vector <vector<Point>> normals;
	vector <vector<Point>> texts;

public:
	Cylinder(float base,float top,float height,int slices,int stacks);
	~Cylinder();
	void normalsCalc();
	Point normalCalc(int i,int j);
	void textsCalc();
	Point textCalc(int i, int j,float angle);
	void draw();
	void draw1();
};


class Sphere:public Node, public CGFobject{

	float radius;
	int stacks;
	int slices;
public:
	Sphere();
	Sphere(float radius,int slices, int stacks);
	~Sphere();
	void draw();
};

class Torus:public Node, public CGFobject{

	float inner;
	float outer;
	int slices;
	int loop;
	float ringRadius;
	vector <vector<Point>> points;
	vector <vector<Point>> normals;
	vector <vector<Point>> texts;

public:
	Torus(float inner,float outer,int slices,int loop);
	~Torus();
	void normalsCalc();
	Point normalCalc(int i, int j);
	void textsCalc();
	Point textCalc(int i, int j,float angle);
	void draw();
};

#endif