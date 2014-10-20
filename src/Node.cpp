#include "Node.h"

/*
Texture* Node::get_texture(string textureref){

for(unsigned int i = 0; i< textures.size(); i++){
if(textures[i]->get_id()==textureref)
{
return textures[i];
}
}

return NULL;
}
*/
void CompositeNode::draw(Appearance *father_ap){

	glPushMatrix();

	glMultMatrixf(& Node::transMatrix[0]);

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	glPopMatrix();



	glPushMatrix();

	if(le_appearance[0]==NULL)
	{
		father_ap->apply();

		for(unsigned int i = 0; i<descendents.size(); i++){

			for(unsigned int j=0;j<transforms.size();j++)
				transforms[j]->apply();
			glGetFloatv(GL_MODELVIEW_MATRIX, & Node::transMatrix[0]);
			glPopMatrix();
			setTransMatrix(transMatrix);

			descendents[i]->draw(father_ap);
		}
	}
	else{

		le_appearance[0]->apply();

		for(unsigned int i = 0; i<descendents.size(); i++){

			for(unsigned int j=0;j<transforms.size();j++)
				transforms[j]->apply();
			glGetFloatv(GL_MODELVIEW_MATRIX, & Node::transMatrix[0]);
			glPopMatrix();
			setTransMatrix(transMatrix);

			descendents[0]->draw(le_appearance[0]);


			//
		}
	}
	glPopMatrix();

	return;
}

void Rectangle::draw(Appearance *father_ap)
{
	float textS;
	float textT;

	/*MANEIRA DE IR BUSCAR OS VALORES ESTÀ ERRADA! TENHO DE IR BUSCAR ISTO AO APPEARANCE! ---> MUDAR APPEARANCE!
	ASSIM CONSIGO RESOLVER SITUAÇÂO DE QUANDO UM APPEARANCE NAO TEM TEXTREF E OS VALORES FICAM A 1!!!!!!!!!!!!!!!


	*/
	/*

	quer use do pai ou do filho! textS e textT vai-se buscar a appearance! 

	ap->apply()?aplica texture?

	*/

	/*TESTEEEEEEEEEEE PURPOSEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE*/
	//	if(this->ap == NULL){
	/*Means innert*/
	//textS = 10;// Node::get_texture(father_ap->get_textureref())->get_texlength_s();
	//textT = 10;// Node::get_texture(father_ap->get_textureref())->get_texlength_t();
	/*	}
	else
	{
	/*Uses own*/
	/*		textS = Node::get_texture(ap->get_textureref())->get_texlength_s();
	textT = Node::get_texture(ap->get_textureref())->get_texlength_t();
	}*/

	if(this->ap == NULL){
		textS = father_ap->get_sWrap();
		textT = father_ap->get_tWrap();


	}
	else{
		textS = ap->get_sWrap();
		textT = ap->get_tWrap();

	}

	this->comp=get_comp();
	this->larg=get_larg();

	glBegin(GL_QUADS);
	{
		glTexCoord2f(0,0);
		glNormal3f(0,0,1);
		glVertex3f( x1, y1, 0);

		glTexCoord2f(comp/(float)textS,0);
		glNormal3f(0,0,1);
		glVertex3f( x2, y1, 0);

		glTexCoord2f(comp/(float)textS,larg/(float)textT);
		glNormal3f(0,0,1);
		glVertex3f( x2, y2, 0);

		glTexCoord2f(0,larg/(float)textT);
		glNormal3f(0,0,1);
		glVertex3f( x1, y2, 0); 
	}
	glEnd();
}


Triangle::Triangle(float a[3],float b[3],float c[3])
{

	point1.x=a[0];
	point1.y=a[1];
	point1.z=a[2];
	point2.x=b[0];
	point2.y=b[1];
	point2.z=b[2];
	point3.x=c[0];
	point3.y=c[1];
	point3.z=c[2];

	normalCalc();

	textS=1;
	textT=1;

	c1=sqrt(powf((point3.x-point2.x),2.0)+powf((point3.y-point2.y),2.0)+powf((point3.z-point2.z),2.0));
	b1=sqrt(powf((point1.x-point2.x),2.0)+powf((point1.y-point2.y),2.0)+powf((point1.z-point2.z),2.0));
	a1=sqrt(powf((point3.x-point1.x),2.0)+powf((point3.y-point1.y),2.0)+powf((point3.z-point1.z),2.0));
	beta=acos((powf(a1,2)-powf(b1,2)+powf(c1,2))/(2*a1*c1));
}

void Triangle::draw(Appearance *father_ap)
{

	if(this->ap == NULL){
		textS = father_ap->get_sWrap();
		textT = father_ap->get_tWrap();


	}
	else{
		textS = ap->get_sWrap();
		textT = ap->get_tWrap();

	}

	glBegin(GL_TRIANGLES);
	glTexCoord2f(1/(float)textS*(c1-a1*cos(beta)),(1/(float)textS*(a1*cos(beta))));
	glNormal3f(normals[0].x,normals[0].y,normals[0].z);
	glVertex3f( point1.x, point1.y,point1.z);

	glTexCoord2f(0,0);
	glNormal3f(normals[1].x,normals[1].y,normals[1].z);
	glVertex3f( point2.x, point2.y,point2.z);

	glTexCoord2f(c1/(float)textS,0);
	glNormal3f(normals[2].x,normals[2].y,normals[2].z);
	glVertex3f( point3.x, point3.y,point3.z);		
	glEnd();

}

void Triangle::normalCalc()
{

	Point e1,e2,n;

	e1.x=0;
	e1.y=0;
	e1.z=0;
	e2.x=0;
	e2.y=0;
	e2.z=0;
	n.x=0;
	n.y=0;
	n.z=0;

	float l;

	e1.x = point2.x - point1.x;
	e1.y = point2.y - point1.y;
	e1.z = point2.z - point1.z;
	e2.x = point3.x - point1.x;
	e2.y = point3.y - point1.y;
	e2.z = point3.z - point1.z;
	n.x = (e1.y * e2.z) - (e1.z * e2.y);
	n.y = (e1.z * e2.x) - (e1.x * e2.z);
	n.z = (e1.x * e2.y) - (e1.y * e2.x);
	// Normalize (divide by root of dot product)
	l = sqrt(n.x * n.x + n.y * n.y + n.z * n.z);
	n.x /= l;
	n.y /= l;
	n.z /= l;

	normals.push_back(n);


	e1.x = point1.x - point2.x;
	e1.y = point1.y - point2.y;
	e1.z = point1.z - point2.z;
	e2.x = point3.x - point2.x;
	e2.y = point3.y - point2.y;
	e2.z = point3.z - point2.z;
	n.x = (e1.y * e2.z) - (e1.z * e2.y);
	n.y = (e1.z * e2.x) - (e1.x * e2.z);
	n.z = (e1.x * e2.y) - (e1.y * e2.x);
	// Normalize (divide by root of dot product)
	l = sqrt(n.x * n.x + n.y * n.y + n.z * n.z);
	n.x /= l;
	n.y /= l;
	n.z /= l;

	normals.push_back(n);

	e1.x = point1.x - point3.x;
	e1.y = point1.y - point3.y;
	e1.z = point1.z - point3.z;
	e2.x = point2.x - point3.x;
	e2.y = point2.y - point3.y;
	e2.z = point2.z - point3.z;
	n.x = (e1.y * e2.z) - (e1.z * e2.y);
	n.y = (e1.z * e2.x) - (e1.x * e2.z);
	n.z = (e1.x * e2.y) - (e1.y * e2.x);
	// Normalize (divide by root of dot product)
	l = sqrt(n.x * n.x + n.y * n.y + n.z * n.z);
	n.x /= l;
	n.y /= l;
	n.z /= l;

	normals.push_back(n);
}



Cylinder::Cylinder(float base,float top,float height,int slices,int stacks)
{

	CGFobject();

	this->top=top;
	this->base=base;
	this->height=height;
	this->slices=slices;
	this->stacks=stacks;

	deltaRadius=(top-base)/(float)stacks;
	float radius=base;
	float deltaH=height/stacks;
	float deltaAngle=(2*PI)/(float)slices;

	vector <Point> help;
	Point point;


	for (float i=0;i<=height;i+=deltaH)
	{
		for (float j=0;j<=2*PI+deltaAngle;j+=deltaAngle)
		{
			point.x=radius*cos(j);
			point.y=radius*sin(j);
			point.z=i;

			help.push_back(point);
		}
		points.push_back(help);
		help.clear();
		radius+=deltaRadius;
	}

	normalsCalc();
	textsCalc();

}


Cylinder::~Cylinder()
{
}

void Cylinder::draw()
{
	int nextP,nextC;
	float angle=(2*PI)/(float)slices;
	//draw base
	glBegin(GL_POLYGON);
	for (int i =  points[0].size()-1; i >=0 ;i--)
	{
	
		glTexCoord2f(0.5 + cos(i*angle)/2.0,0.5 + sin(i*angle)/2.0);
		glNormal3f( 0,0,1);
		glVertex3f( points[0][i].x,points[0][i].y,points[0][i].z);
	
	}  
	glEnd();


	//draw top
	glBegin(GL_POLYGON);
	for (unsigned int i =  0; i <points[points.size()-1].size();i++)
	{
		glTexCoord2f(0.5 + cos(i*angle)/2.0,0.5 + sin(i*angle)/2.0);
		glNormal3f( 0,0,-1);
		glVertex3f( points[points.size()-1][i].x,points[points.size()-1][i].y,points[points.size()-1][i].z);
	} 
	glEnd();


	//draw sides
	//I->HORIZONTAL row
	for (unsigned int i = 0; i < points.size()-1;i++)
	{
		//J->VERTICAL column
		glBegin(GL_QUADS);
		for (unsigned int j = 0; j < points[i].size()-1;j++)
		{
			
			nextP=j+1;

			
			nextC=i+1;

			glTexCoord2f(texts[i][j].x,texts[i][j].y);
			glNormal3f(normals[i][j].x,normals[i][j].y,normals[i][j].z);
			glVertex3f( points[i][j].x,points[i][j].y,points[i][j].z);

			glTexCoord2f(texts[i][nextP].x,texts[i][nextP].y);
			glNormal3f(normals[i][nextP].x,normals[i][nextP].y,normals[i][nextP].z);
			glVertex3f( points[i][nextP].x,points[i][nextP].y,points[i][nextP].z);  

			glTexCoord2f(texts[nextC][nextP].x,texts[nextC][nextP].y);
			glNormal3f(normals[nextC][nextP].x,normals[nextC][nextP].y,normals[nextC][nextP].z);
			glVertex3f( points[nextC][nextP].x,points[nextC][nextP].y,points[nextC][nextP].z);

			glTexCoord2f(texts[nextC][j].x,texts[nextC][j].y);
			glNormal3f(normals[nextC][j].x,normals[nextC][j].y,normals[nextC][j].z);
			glVertex3f( points[nextC][j].x,points[nextC][j].y,points[nextC][j].z);

		}  
		glEnd();
	}
}


void Cylinder::draw1()
{
	int nextP,nextC;
	float angle=(2*PI)/(float)slices;
	//draw base
	glBegin(GL_POLYGON);
	for (int i =  points[0].size()-1; i >=0 ;i--)
	{
	
		glTexCoord2f(0.5 + cos(i*angle)/2.0,0.5 + sin(i*angle)/2.0);
		glNormal3f( 0,0,1);
		glVertex3f( points[0][i].x,points[0][i].y,points[0][i].z);
	
	}  
	glEnd();


	//draw top
	glBegin(GL_POLYGON);
	for (unsigned int i =  0; i <points[points.size()-1].size();i++)
	{
		glTexCoord2f(0.5 + cos(i*angle)/2.0,0.5 + sin(i*angle)/2.0);
		glNormal3f( 0,0,-1);
		glVertex3f( points[points.size()-1][i].x,points[points.size()-1][i].y,points[points.size()-1][i].z);
	} 
	glEnd();


	//draw sides



	//I->HORIZONTAL row
	for (unsigned int i = 0; i < points.size()-1;i++)
	{
		//J->VERTICAL column
		glBegin(GL_QUADS);
		for (unsigned int j = 0; j < points[i].size()-1;j++)
		{
			
			nextP=j+1;

			nextC=i+1;

			glNormal3f(normals[i][j].x,normals[i][j].y,normals[i][j].z);
			glVertex3f( points[i][j].x,points[i][j].y,points[i][j].z);

			glNormal3f(normals[i][nextP].x,normals[i][nextP].y,normals[i][nextP].z);
			glVertex3f( points[i][nextP].x,points[i][nextP].y,points[i][nextP].z);  

			glNormal3f(normals[nextC][nextP].x,normals[nextC][nextP].y,normals[nextC][nextP].z);
			glVertex3f( points[nextC][nextP].x,points[nextC][nextP].y,points[nextC][nextP].z);

			glNormal3f(normals[nextC][j].x,normals[nextC][j].y,normals[nextC][j].z);
			glVertex3f( points[nextC][j].x,points[nextC][j].y,points[nextC][j].z);

		}  
		glEnd();
	}
}

void Cylinder::normalsCalc()
{
	vector<Point> lineNormal;
	Point help;

	for (unsigned int i = 0; i < points.size();i++)
	{
		for (unsigned int j = 0; j < points[i].size();j++)
		{
			help=normalCalc(i,j);
			lineNormal.push_back(help);
		}
		normals.push_back(lineNormal);
		lineNormal.clear();
	}
}

Point Cylinder::normalCalc(int i,int j)
{

	int nextP=0,nextC=0;

	if(j==points[i].size()-1)
		nextP=j;
	else
		nextP=j+1;

	if(i==points.size()-1)
		nextC=0;
	else
		nextC=i+1;

	Point e1,e2,n;

	e1.x=0;
	e1.y=0;
	e1.z=0;
	e2.x=0;
	e2.y=0;
	e2.z=0;
	n.x=0;
	n.y=0;
	n.z=0;

	float l;

	e1.x = points[i][nextP].x - points[i][j].x;
	e1.y = points[i][nextP].y - points[i][j].y;
	e1.z = points[i][nextP].z - points[i][j].z;
	e2.x = points[nextC][j].x - points[i][j].x;
	e2.y = points[nextC][j].y - points[i][j].y;
	e2.z = points[nextC][j].z - points[i][j].z;
	n.x = (e1.y * e2.z) - (e1.z * e2.y);
	n.y = (e1.z * e2.x) - (e1.x * e2.z);
	n.z = (e1.x * e2.y) - (e1.y * e2.x);
	// Normalize (divide by root of dot product)
	l = sqrt(n.x * n.x + n.y * n.y + n.z * n.z);
	n.x /= l;
	n.y /= l;
	n.z /= l;

	return n;
}


void Cylinder::textsCalc()
{
	float angle=0;
	vector<Point> lineText;
	Point help;

	for (unsigned int i = 0; i < points.size();i++)
	{
		for (unsigned int j = 0; j < points[i].size();j++)
		{

			help=textCalc(i,j,angle);
			lineText.push_back(help);
			angle+=(2*PI)/(float)slices;
		}
		texts.push_back(lineText);
		lineText.clear();
		angle=0;
	}
}

Point Cylinder::textCalc(int i,int j,float angle)
{
	Point t;
	t.x=0;
	t.y=0;
	t.z=0;


		t.x = angle / (float)(2*PI);
		t.y =  points[i][j].z / (height+top/2.0+base/2.0);

	return t;
}

Sphere::Sphere(float radius,int slices, int stacks)
{

	this->radius=radius;
	this->stacks=stacks;
	this->slices=slices;
}


void Sphere::draw()
{
	GLUquadric *quad= gluNewQuadric();
	gluQuadricTexture(quad,GL_TRUE);
	gluQuadricOrientation(quad,GLU_OUTSIDE);
	gluSphere(quad,radius,slices,stacks);
}



Sphere::~Sphere()
{
}


Torus::Torus(float inner,float outer,int slices,int loop)
{
	this->inner=inner;
	this->outer=outer;
	this->slices=slices;
	this->loop=loop;
	float alphaJump=(2*PI)/(float)slices;
	float phiJump=(PI)/(float)loop;
	Point point;
	ringRadius = (outer-inner)/2.0;
	float mediumRadius=ringRadius+inner;
	vector<Point> help;



	for (double phi = 0; phi < 2*PI+phiJump;phi+=phiJump) // Elevation [0, PI]
	{
		for (double alpha = 0.; alpha < 2*PI+alphaJump; alpha += alphaJump) // Azimuth [0, 2PI]
		{
			point.x= (outer+inner*cos(phi))*cos(alpha);
			point.y= (outer+inner*cos(phi))*sin(alpha);
			point.z= inner*sin(phi);
			help.push_back(point);

		}
		points.push_back(help);
		help.clear();
	}


	normalsCalc();
	textsCalc();
}

void Torus::draw()
{

	int nextP,nextC;
	float auxTextX=0,auxTextY=0;

	for (unsigned int i = 0; i < points.size()-1;i++)
	{

		glBegin(GL_TRIANGLE_STRIP);
		for (unsigned int j = 0; j < points[i].size()-1;j++)
		{
		
				nextP=j+1;
                nextC=i+1;


			glTexCoord2f( texts[i][j].x,texts[i][j].y);
			glNormal3f( normals[i][j].x,normals[i][j].y,normals[i][j].z);
			glVertex3f( points[i][j].x,points[i][j].y,points[i][j].z);

			glTexCoord2f( texts[i][nextP].x,texts[i][nextP].y);
			glNormal3f( normals[i][nextP].x,normals[i][nextP].y,normals[i][nextP].z);  
			glVertex3f( points[i][nextP].x,points[i][nextP].y,points[i][nextP].z);  

			glTexCoord2f( texts[nextC][j].x,texts[nextC][j].y);
			glNormal3f(normals[nextC][j].x,normals[nextC][j].y,normals[nextC][j].z);
			glVertex3f( points[nextC][j].x,points[nextC][j].y,points[nextC][j].z);

			glTexCoord2f( texts[nextC][nextP].x,texts[nextC][nextP].y);
			glNormal3f( normals[nextC][nextP].x,normals[nextC][nextP].y,normals[nextC][nextP].z); 
			glVertex3f( points[nextC][nextP].x,points[nextC][nextP].y,points[nextC][nextP].z);



		}  
		glEnd();
	}
}

void Torus::normalsCalc()
{
	vector<Point> lineNormal;
	Point help;

	for (unsigned int i = 0; i < points.size();i++)
	{
		for (unsigned int j = 0; j < points[i].size();j++)
		{
			help=normalCalc(i,j);
			lineNormal.push_back(help);
		}
		normals.push_back(lineNormal);
		lineNormal.clear();
	}
}

Point Torus::normalCalc(int i,int j)
{

	int nextP=0,nextC=0;

	if(j==points[i].size()-1)
		nextP=0;
	else
		nextP=j+1;

	if(i==points.size()-1)
		nextC=0;
	else
		nextC=i+1;

	Point e1,e2,n;

	e1.x=0;
	e1.y=0;
	e1.z=0;
	e2.x=0;
	e2.y=0;
	e2.z=0;
	n.x=0;
	n.y=0;
	n.z=0;

	float l;

	e1.x = points[i][nextP].x - points[i][j].x;
	e1.y = points[i][nextP].y - points[i][j].y;
	e1.z = points[i][nextP].z - points[i][j].z;
	e2.x = points[nextC][j].x - points[i][j].x;
	e2.y = points[nextC][j].y - points[i][j].y;
	e2.z = points[nextC][j].z - points[i][j].z;
	n.x = (e1.y * e2.z) - (e1.z * e2.y);
	n.y = (e1.z * e2.x) - (e1.x * e2.z);
	n.z = (e1.x * e2.y) - (e1.y * e2.x);
	// Normalize (divide by root of dot product)
	l = sqrt(n.x * n.x + n.y * n.y + n.z * n.z);
	n.x /= l;
	n.y /= l;
	n.z /= l;

	return n;
}


void Torus::textsCalc()
{
	vector<Point> lineText;
	Point help;
	float angle=0;

	for (unsigned int i = 0; i < points.size();i++)
	{
		for (unsigned int j = 0; j < points[i].size();j++)
		{
			help=textCalc(i,j,angle);
			lineText.push_back(help);
			angle+=(2*PI)/(float)slices;
		}
		texts.push_back(lineText);
		lineText.clear();
		angle=0;
	}
}

Point Torus::textCalc(int i,int j,float angle)
{
	Point t;
	t.x=0;
	t.y=0;
	t.z=0;




	t.x = j/(float)loop;
	t.y = i/(float)slices;
	
	return t;
}


Torus::~Torus()
{

}
