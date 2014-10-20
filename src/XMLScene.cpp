#include "XMLScene.h"

XMLScene::XMLScene(char *filename){

	this->filename=filename;

}

void XMLScene::loadFile(){
	Parser *p = new Parser(this->filename);
	this->p=p;
	return;
}

void XMLScene::init(){
	/*MOST IMPORTANT! LOAD FILE FIRST*/
	loadFile();

	// Enables lighting computations
	glEnable(GL_LIGHTING);

	//set globals
	set_upGlobals();

	glMatrixMode(GL_MODELVIEW);



	setUpdatePeriod(30);
	return;
}
void XMLScene::display(){

	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	axis.draw();
	CGFscene::activeCamera->applyView();

	//to complex function, SHALL BE modified
	set_upLights();

	/*LE POWER DRAW*/
	
	glPushMatrix();
	glGetFloatv(GL_MODELVIEW_MATRIX, &getParser()->get_root_node().Node::transMatrix[0]);
	getParser()->get_root_node().setTransMatrix(getParser()->get_root_node().Node::transMatrix);
	getParser()->get_root_node().draw(getParser()->get_root_node().get_le_appearance());
	glPopMatrix();



	glutSwapBuffers();
	return;
}


void XMLScene::set_upGlobals(){

	glClearColor(p->getGlobals().get_background(0), p->getGlobals().get_background(1), p->getGlobals().get_background(2), p->getGlobals().get_background(3));
	glPolygonMode(GL_FRONT_AND_BACK, p->getGlobals().get_mode());
	glShadeModel(p->getGlobals().get_shading());
	glCullFace(p->getGlobals().get_face());
	glFrontFace(p->getGlobals().get_order());
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, p->getGlobals().get_doublesided());
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, p->getGlobals().get_local());
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, p->getGlobals().get_ambient());

	return;
}

void XMLScene::set_upLights(){

	/*First Spot lights*/
	for(unsigned int i = 0; i<p->get_s_lights().size(); i++){

		if(p->get_s_lights()[i].get_enabled() == true){

			p->get_s_lights()[i].enable();
			p->get_s_lights()[i].draw();

		}
		else
			p->get_s_lights()[i].disable();

		p->get_s_lights()[i].update();

	}

	/*Then Omni Lights*/

	for(unsigned int i = 0; i<p->get_o_lights().size(); i++){

		if(p->get_o_lights()[i].get_enabled() == true){

			p->get_o_lights()[i].enable();
			p->get_o_lights()[i].draw();

		}
		else
			p->get_o_lights()[i].disable();

		p->get_o_lights()[i].update();
	}


	return;
}