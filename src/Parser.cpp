#pragma once
#include "Parser.h"

Parser::Parser(char *filename){

	//Open and check if file is ok

	document = new TiXmlDocument( filename );
	bool loaded = document->LoadFile();

	if(!loaded){

		printf( "Could not load file '%s'. Error='%s'. Exiting.\n", filename, document->ErrorDesc() );
		exit( 1 );

	}

	//Reading Top Bottom

	TiXmlElement* root = document->FirstChildElement( "anf" );

	if(root == NULL)
	{
		printf("ANF element not found! Exiting!\n");
		exit(1);
	}

	globals = root->FirstChildElement();

	cameras = globals->NextSiblingElement("cameras");

	lights = globals->NextSiblingElement("lights");

	textures = globals->NextSiblingElement("textures");

	appearances = globals->NextSiblingElement("appearances");

	graph = globals->NextSiblingElement("graph");


	/*Globals Section*/
	if(globals == NULL)
	{
		printf("globals element not found! Exiting!\n");
		//exit(1);
	}
	else
	{
		printf("\nGLOBALS\n\n");

		Globals temp;

		TiXmlElement* drawing = globals->FirstChildElement("drawing");

		if(drawing)
		{
			printf("\n\nInside drawing \n");

			string mode, shading;
			char *background=NULL;
			float b1, b2, b3, b4;

			mode = drawing->Attribute("mode");

			if(mode=="fill" || mode=="line" || mode=="point"){

				temp.set_mode(mode);
				cout << "Mode = " << mode << endl;
			}
			else{
				printf("Error parsing mode\n");
				//exit(1);
			}

			shading = drawing->Attribute("shading");

			if(shading=="flat" || shading=="gouraud"){

				temp.set_shading(shading);
				cout << "Shading = " << shading << endl;
			}
			else
			{
				printf("Error parsing shadding\n");
				//exit(1);
			}

			background = (char*) drawing->Attribute("background");

			if(background && sscanf(background,"%f %f %f %f",&b1, &b2, &b3, &b4) == 4){

				temp.set_background(b1,b2,b3,b4);
				printf("Background values (b1 b2 b3 b4): %f %f %f %f\n", b1, b2, b3, b4);
			}
			else
			{
				printf("Error parsing background\n");
				//exit(1);
			}

		}


		TiXmlElement* culling = globals->FirstChildElement("culling");

		if(culling)
		{
			printf("\n\nInside culling \n");
			//values to object

			string face, order;

			face=culling->Attribute("face");

			if(face=="none" || face=="back" || face=="front" || face=="both"){

				temp.set_face(face);
				cout << "Face = " << face << endl;
			}
			else
			{
				printf("Error parsing face\n");
				//exit(1);
			}

			order=culling->Attribute("order");

			if(order=="ccw" || face=="cw"){

				temp.set_order(order);
				cout << "Order = " << order << endl;
			}
			else
			{
				printf("Error parsing order\n");
				//exit(1);
			}

		}


		TiXmlElement* lighting = globals->FirstChildElement("lighting");

		if(lighting)
		{
			printf("\n\nInside lighting \n");
			//values to object

			bool doublesided, local, enabled;
			char *ambient=NULL;
			float a1, a2 ,a3, a4;

			if(strcmp(lighting->Attribute("doublesided"), "true") == 0)
			{
				doublesided = true;
			}
			else doublesided=false;

			if(doublesided==0 || doublesided == 1){

				temp.set_doublesided(doublesided);
				cout<<"Doublesided = "<< boolalpha << doublesided << endl; 

			}
			else
			{
				printf("Error parsing doublesided\n");
				//exit(1);
			}

			if(strcmp(lighting->Attribute("local"), "true") == 0)
			{
				local = true;
			}
			else local = false;

			if(local==0 || local == 1){

				temp.set_local(local);
				cout<<"Local = "<< boolalpha << local << endl; 

			}
			else
			{
				printf("Error parsing local\n");
				//exit(1);
			}

			if(strcmp(lighting->Attribute("enabled"), "true") == 0){
				enabled=true;
			}
			else enabled = false;

			if(enabled==0 || enabled == 1){

				temp.set_enabled(enabled);
				cout<<"Enabled = "<< boolalpha << enabled << endl; 

			}
			else
			{
				printf("Error parsing enabled\n");
				//exit(1);
			}

			ambient = (char*) lighting->Attribute("ambient");

			if(ambient && sscanf(ambient,"%f %f %f %f",&a1, &a2, &a3, &a4) == 4){
				temp.set_ambient(a1,a2,a3,a4);
				printf("Ambient values (a1 a2 a3 a4): %f %f %f %f\n", a1, a2, a3, a4);
			}
			else
			{
				printf("Error parsing ambient\n");
				//exit(1);
			}

		}

		this->globals_obj = temp;
		//temp.~Globals();
	}


	/*Cameras Section*/

	if(cameras == NULL){
		printf("cameras element not found! Exiting!\n");
		//exit(1);
	}
	else{
		printf("\nCAMERAS\n\n");

		string initial;
		initial = cameras->Attribute("initial");

		cout<<"CAMARA INICIAL = " << initial <<endl;


		TiXmlElement* camera = cameras->FirstChildElement();

		while(camera){

			if (strcmp(camera->Value(),"perspective")==0){
				printf("\nInside perspective \n");

				PerspectiveCamera temp;

				string id;
				float near, far, angle;
				char *pos;
				float pos1, pos2, pos3;
				char *target;
				float t1, t2, t3;

				id = camera->Attribute("id");
				temp.set_id(id);
				cout<<"ID: " << id << endl;

				if(camera->QueryFloatAttribute("near",&near)==TIXML_SUCCESS &&
					camera->QueryFloatAttribute("far",&far)==TIXML_SUCCESS &&
					camera->QueryFloatAttribute("angle",&angle)==TIXML_SUCCESS)
				{

					temp.set_near(near);
					temp.set_far(far);
					temp.set_angle(angle);

					printf("Near %f\n", near);
					printf("Far %f\n", far);
					printf("Angle %f\n", angle);
				}
				else
				{
					printf("Error parsing initial 3 perspective atributes (near, far, angle)");
				}

				pos = (char*) camera->Attribute("pos");

				if(pos && sscanf(pos,"%f %f %f",&pos1, &pos2, &pos3) == 3){

					temp.set_pos(pos1, pos2, pos3);

					printf("Pos values (pos1 pos2 pos3): %f %f %f\n", pos1, pos2, pos3);
				}
				else
				{
					printf("Error parsing pos\n");
					//exit(1);
				}

				target = (char*) camera->Attribute("target");

				if(target && sscanf(target,"%f %f %f",&t1, &t2, &t3) == 3){

					temp.set_target(t1, t2, t3);

					printf("Target values (t1 t2 t3): %f %f %f\n", t1, t2, t3);
				}
				else
				{
					printf("Error parsing target\n");
					//exit(1);
				}

				p_cameras.push_back(temp);
				//temp.~PerspectiveCamera();

			}

			if (strcmp(camera->Value(),"ortho")==0){
				printf("\nInside ortho \n");
				//values to object

				OrthoCamera temp;

				string id, direction;
				float near, far, left, right, top, bottom;

				id = camera->Attribute("id");
				temp.set_id(id);
				cout<<"ID: " << id << endl;

				direction = camera->Attribute("direction");
				temp.set_direction(direction);
				cout<<"Direction: " << direction << endl;

				if(camera->QueryFloatAttribute("near",&near)==TIXML_SUCCESS &&
					camera->QueryFloatAttribute("far",&far)==TIXML_SUCCESS &&
					camera->QueryFloatAttribute("left",&left)==TIXML_SUCCESS &&
					camera->QueryFloatAttribute("right",&right)==TIXML_SUCCESS &&
					camera->QueryFloatAttribute("top",&top)==TIXML_SUCCESS &&
					camera->QueryFloatAttribute("bottom",&bottom)==TIXML_SUCCESS)
				{

					temp.set_near(near);
					temp.set_far(far);
					temp.set_left(left);
					temp.set_right(right);
					temp.set_top(top);
					temp.set_bottom(bottom);

					printf("Near %f\n", near);
					printf("Far %f\n", far);
					printf("Left %f\n", left);
					printf("Right %f\n", right);
					printf("Top %f\n", top);
					printf("Bottom %f\n", bottom);
				}
				else
				{
					printf("Error parsing ortho atributes (near, far, left, right, top, bottom)");
				}

				o_cameras.push_back(temp);
				//temp.~OrthoCamera();

			}

			camera = camera->NextSiblingElement();
		}
	}

	if(lights == NULL){
		printf("lights element not found! Exiting!\n");
		//exit(1);
	}
	else
	{
		printf("\nLIGHTS\n\n");

		light = lights->FirstChildElement();

		while(light)
		{

			if(strcmp(light->Attribute("type"),"omni")==0){

				OmniLight temp;

				string id;
				bool enabled, marker;
				char *pos;
				float pos1, pos2, pos3;

				id = light->Attribute("id");
				temp.set_id(id);
				cout<<"ID: " << id << endl;

				if(strcmp(light->Attribute("enabled"), "true") == 0)
				{
					enabled=true;
				}
				else enabled=false;

				if(enabled==0 || enabled == 1){

					temp.set_enabled(enabled);
					cout<<"Enabled = "<< boolalpha << enabled << endl; 

				}
				else
				{
					printf("Error parsing enabled\n");
					//exit(1);
				}

				if(strcmp(light->Attribute("marker"), "true") == 0)
				{
					marker=true;
				}
				else marker=false;

				if(marker == 0 || marker == 1){

					temp.set_marker(marker);
					cout<<"Marker = "<< boolalpha << marker << endl; 


				}
				else
				{
					printf("Error parsing marker\n");
					//exit(1);
				}

				pos = (char*) light->Attribute("pos");

				if(pos && sscanf(pos,"%f %f %f",&pos1, &pos2, &pos3) == 3){

					temp.set_pos(pos1, pos2, pos3);
					printf("Pos values (pos1 pos2 pos3): %f %f %f\n", pos1, pos2, pos3);
				}
				else
				{
					printf("Error parsing pos\n");
					//exit(1);
				}

				TiXmlElement *component=light->FirstChildElement();

				while(component)
				{

					printf("Inside component \n");

					string type;
					char *value;
					float v1, v2, v3, v4;


					type = component->Attribute("type");
					if(type=="ambient" || type=="diffuse" || type=="specular"){
						cout<<"Type = " << type << endl;
					}
					else
					{
						printf("Error parsing type\n");
						//exit(1);
					}

					value = (char*) component->Attribute("value");

					if(value && sscanf(value,"%f %f %f %f",&v1, &v2, &v3, &v4) == 4){
						if(type=="ambient"){
							temp.set_ambient(v1, v2, v3, v4);
						}
						else if(type=="diffuse"){
							temp.set_diffuse(v1, v2, v3, v4);
						}
						else if(type=="specular"){
							temp.set_specular(v1, v2, v3, v4);
						}
						printf("Value values (v1 v2 v3 v4): %f %f %f %f\n", v1, v2, v3, v4);
					}
					else
					{
						printf("Error parsing value\n");
						//exit(1);
					} 

					component=component->NextSiblingElement();
				}

				temp.create();
				o_lights.push_back(temp);
				//temp.~OmniLight();

			}

			if(strcmp(light->Attribute("type"),"spot")==0){

				SpotLight temp;

				string id;
				bool enabled, marker;
				char *pos;
				float pos1, pos2, pos3;
				char *target;
				float t1, t2, t3;
				float angle, exponent;

				id = light->Attribute("id");
				temp.set_id(id);
				cout<<"ID: " << id << endl;

				if(strcmp(light->Attribute("enabled"), "true") == 0)
				{
					enabled=true;
				}
				else enabled=false;

				if(enabled==0 || enabled == 1){

					temp.set_enabled(enabled);

					cout<<"Enabled = "<< boolalpha << enabled << endl; 

				}
				else
				{
					printf("Error parsing enabled\n");
					//exit(1);
				}

				if(strcmp(light->Attribute("marker"), "true") == 0)
				{
					marker=true;
				}
				else marker=false;

				if(marker == 0 || marker == 1){

					temp.set_marker(marker);

					cout<<"Marker = "<< boolalpha << marker << endl; 

				}
				else
				{
					printf("Error parsing marker\n");
					//exit(1);
				}

				pos = (char*) light->Attribute("pos");

				if(pos && sscanf(pos,"%f %f %f",&pos1, &pos2, &pos3) == 3){

					temp.set_pos(pos1, pos2, pos3);

					printf("Pos values (pos1 pos2 pos3): %f %f %f\n", pos1, pos2, pos3);
				}
				else
				{
					printf("Error parsing pos\n");
					//exit(1);
				}

				target = (char*) light->Attribute("target");

				if(target && sscanf(target,"%f %f %f",&t1, &t2, &t3) == 3){

					temp.set_target(t1, t2, t3);

					printf("Target values (t1 t2 t3): %f %f %f\n", t1, t2, t3);
				}
				else
				{
					printf("Error parsing target\n");
					//exit(1);
				}

				if(light->QueryFloatAttribute("angle",&angle)==TIXML_SUCCESS &&
					light->QueryFloatAttribute("exponent",&exponent)==TIXML_SUCCESS)
				{

					temp.set_angle(angle);
					temp.set_exponent(exponent);

					printf("Angle %f\n", angle);
					printf("Exponent %f\n", exponent);
				}
				else
				{
					printf("Error parsing spot light atributes (angle, exponent)");
				}

				TiXmlElement *component=light->FirstChildElement();

				while(component)
				{

					printf("Inside component \n");

					string type;
					char *value;
					float v1, v2, v3, v4;


					type = component->Attribute("type");
					if(type=="ambient" || type=="diffuse" || type=="specular"){
						cout<<"Type = " << type << endl;
					}
					else
					{
						printf("Error parsing type\n");
						//exit(1);
					}

					value = (char*) component->Attribute("value");

					if(value && sscanf(value,"%f %f %f %f",&v1, &v2, &v3, &v4) == 4){

						if(type=="ambient"){
							temp.set_ambient(v1, v2, v3, v4);
						}
						else if(type=="diffuse"){
							temp.set_diffuse(v1, v2, v3, v4);
						}
						else if(type=="specular"){
							temp.set_specular(v1, v2, v3, v4);
						}

						printf("Value values (v1 v2 v3 v4): %f %f %f %f\n", v1, v2, v3, v4);
					}
					else
					{
						printf("Error parsing value\n");
						//exit(1);
					} 

					component=component->NextSiblingElement();
				}

				temp.create();
				s_lights.push_back(temp);
				//temp.~SpotLight();

			}

			light=light->NextSiblingElement();
		}

	}


	/*Textures Section*/

	if(textures == NULL)
	{
		printf("textures element not found! Exiting!\n");
		//exit(1);
	}
	else
	{
		printf("\n TEXTURES \n\n");
		texture = textures->FirstChildElement();

		while(texture)
		{

			string id, file;
			float texlength_s, texlength_t;

			id = texture->Attribute("id");
			file = texture->Attribute("file");

			Texture *temp = new Texture(file);			
			temp->set_id(id);

			cout<< "File = " << file << endl;
			cout<< "ID: " << id <<endl;

			if( texture->QueryFloatAttribute("texlength_s",&texlength_s)==TIXML_SUCCESS &&
				texture->QueryFloatAttribute("texlength_t",&texlength_t)==TIXML_SUCCESS)
			{

				temp->set_texlength_s(texlength_s);
				temp->set_texlength_t(texlength_t);

				printf("Texlength_s %f\n", texlength_s);
				printf("Texlength_t %f\n", texlength_t);
			}
			else
			{
				printf("Error parsing texlength_s && texlength_t\n");
				//exit(1);
			} 

			textures_obj.push_back(temp);
			//temp->~Texture();

			texture=texture->NextSiblingElement();
		}

	}


	/*Appearence Section*/

	if(appearances == NULL)
	{
		printf("appearances element not found! Exiting!\n");
		//exit(1);
	}
	else
	{

		printf("\nAPPEARANCES\n\n");

		appearance = appearances->FirstChildElement();

		while(appearance)
		{
			Appearance *temp = new Appearance();

			string id, textureref="";
			float shininess;

			id = appearance->Attribute("id");
			temp->set_id(id);
			cout << "ID: "<< id << endl;

			if(appearance->Attribute("textureref") != NULL)
				textureref = appearance->Attribute("textureref");
			temp->set_textureref(textureref);
			cout << "Textureref= "<< textureref << endl;

			if(appearance->QueryFloatAttribute("shininess",&shininess)==TIXML_SUCCESS){
				temp->set_shininess(shininess);
				printf("Sininess %f\n", shininess);
			}

			TiXmlElement *component=appearance->FirstChildElement();

			while(component)
			{
				printf("Inside component \n");
				string type;
				char *value;
				float v1, v2, v3, v4;


				type = component->Attribute("type");
				if(type=="ambient" || type=="diffuse" || type=="specular"){
					cout<<"Type = " << type << endl;
				}
				else
				{
					printf("Error parsing type\n");
					//exit(1);
				}

				value = (char*) component->Attribute("value");

				if(value && sscanf(value,"%f %f %f %f",&v1, &v2, &v3, &v4) == 4){

					if(type=="ambient"){
						temp->set_ambient(v1, v2, v3, v4);
					}
					else if(type=="diffuse"){
						temp->set_diffuse(v1, v2, v3, v4);
					}
					else if(type=="specular"){
						temp->set_specular(v1, v2, v3, v4);
					}

					printf("Value values (v1 v2 v3 v4): %f %f %f %f\n", v1, v2, v3, v4);
				}
				else
				{
					printf("Error parsing value\n");
					//exit(1);
				} 
				component=component->NextSiblingElement();
			}
			

			temp->set_sWrap(get_textl_s(textureref));
			temp->set_tWrap(get_textl_t(textureref));
			temp->create(get_refTexure(textureref));
			appearances_obj.push_back(temp);
			//temp.~Appearance();

			appearance=appearance->NextSiblingElement();

		}
	}


	/*Graph Section*/

	if(graph == NULL)
	{
		printf("graph element not found! Exiting!\n");
		//exit(1);
	}
	else
	{

		printf("\n GRAPH\n\n");

		const char *rootid;
		char * atemp;
		rootid=graph->Attribute("rootid");
		cout<<"ROOTID: "<<rootid<<endl;

		//printf("Graph root id = %s ", graph->Attribute("rootid"));
		node = graph->FirstChildElement();

		while(node)
		{
			CompositeNode temp;
			temporary_nodes.insert(std::pair<string, CompositeNode>(node->Attribute("id"), temp));
			node=node->NextSiblingElement();
		}



		/*Second iteration! First one is to create all nodes!*/

		node = graph->FirstChildElement();

		while(true){

			atemp=(char *) node->Attribute("id");
			if(strcmp(atemp,rootid)==0)
				break;

			node=node->NextSiblingElement();
		}

		while(node)
		{
			string id;
			id = node->Attribute("id");
			temporary_nodes.find(id)->second.set_id(id);
			printf("Node id '%s' \n", node->Attribute("id"));
			TiXmlElement *child=node->FirstChildElement();

			while(child)
			{
				if (strcmp(child->Value(),"transforms")==0)
				{

					transform = child->FirstChildElement();

					while(transform)
					{
						char* type_temp;
						type_temp = (char*)transform->Attribute("type");

						if(strcmp(type_temp,"rotate")==0){

							string axis;
							float angle;

							axis = transform->Attribute("axis");

							if(transform->QueryFloatAttribute("angle",&angle)==TIXML_SUCCESS){
								printf("Angle %f\n", angle);
							}

							Rotate *r = new Rotate(axis, angle);
							temporary_nodes.find(id)->second.push_tranformation(r);

						}

						/***/

						if(strcmp(type_temp,"scale")==0){

							char *factor;
							float f1, f2, f3;
							factor = (char*) transform->Attribute("factor");

							if(factor && sscanf(factor,"%f %f %f",&f1, &f2, &f3) == 3){

								Scale *s=new Scale(f1, f2, f3);
								temporary_nodes.find(id)->second.push_tranformation(s);

							}
						}

						/***/

						if(strcmp(type_temp,"translate")==0){

							char *to;
							float t1, t2, t3;
							to = (char*) transform->Attribute("to");

							if(to && sscanf(to,"%f %f %f",&t1, &t2, &t3) == 3){

								Translate *t=new Translate(t1, t2, t3);

								temporary_nodes.find(id)->second.push_tranformation(t);

							}
						}

						transform = transform->NextSiblingElement();
					}
				}


				if (strcmp(child->Value(),"appearanceref")==0)
				{

					/**/
					if(child->Attribute("id") == "inherit")
					{
						Appearance *p = new Appearance();
						p = NULL;
						temporary_nodes.find(id)->second.push_appearance(p);
					}
					else{
						string appear_id;
						appear_id = child->Attribute("id");
						/*
						Appearance *p = new Appearance();
						p->set_id(id);
						*/

						temporary_nodes.find(id)->second.push_appearance(setAppearance(appear_id));
						/*add the Appearance with the name  id="Appearanceref"*/
					}


					printf("inside appearanceref\n");
				}


				if (strcmp(child->Value(),"primitives")==0)
				{
					//access primitives information

					printf("Inside primitives \n");

					TiXmlElement *object_primitive = child->FirstChildElement();

					while(object_primitive){

						/*Inside primitives, and recognition of primitive*/
						/*Create object based on primitive*/
						if (strcmp(object_primitive->Value(),"rectangle")==0){
							Rectangle *r=new Rectangle();

							char *xy1;
							char *xy2;
							float x1, y1, x2, y2;

							xy1 = (char*) object_primitive->Attribute("xy1");

							if(xy1 && sscanf(xy1,"%f %f",&x1, &y1) == 2){
								r->set_x1(x1);
								r->set_y1(y1);
							}

							xy2 = (char*) object_primitive->Attribute("xy2");

							if(xy2 && sscanf(xy2,"%f %f",&x2, &y2) == 2){
								r->set_x2(x2);
								r->set_y2(y2);
							}

							printf("primitive: '%s' \n", object_primitive->Value());

							temporary_nodes.find(id)->second.push_descendents(r);

						}
						object_primitive = object_primitive->NextSiblingElement();
					}


				}

				if (strcmp(child->Value(),"descendants")==0)
				{
					TiXmlElement *descendent = child->FirstChildElement();

					while(descendent){
						string noderef;
						noderef = descendent->Attribute("id");

						temporary_nodes.find(id)->second.push_descendents(getDescendent(noderef));

						descendent = descendent->NextSiblingElement();

					}

					//descendentes_id.push_back(child->Attribute("id"));
					printf("inside descendants\n");
				}

				child=child->NextSiblingElement();
			}

			root_node = temporary_nodes.find(id)->second;
			/*maybe a break;*/
			break;

		}
	}
};


Appearance* Parser::setAppearance(string appear_id){

	for(unsigned int i =0; i<appearances_obj.size(); i++){
		if(appearances_obj[i]->get_id() == appear_id)
		{
			return appearances_obj[i];
		}
	}
	return NULL;/*Impossible because all objects must have an appearance*/
}


CGFtexture* Parser::get_refTexure(string textureref){

	for(unsigned int i = 0; i<textures_obj.size(); i++){

		if(textures_obj[i]->get_id() == textureref){

			return textures_obj[i]->get_textureMapped();

		}

	}
	return NULL;

}

float Parser::get_textl_s(string textureref){

	for(unsigned int i = 0; i<textures_obj.size(); i++){

		if(textures_obj[i]->get_id() == textureref){

			return textures_obj[i]->get_texlength_s();

		}

	}
	return 0;

}

float Parser::get_textl_t(string textureref){

	for(unsigned int i = 0; i<textures_obj.size(); i++){

		if(textures_obj[i]->get_id() == textureref){

			return textures_obj[i]->get_texlength_t();

		}

	}
	return 0;

}




CompositeNode* Parser::getDescendent(string noderef){

	printf("\n DESCENDENT\n\n");

	node = graph->FirstChildElement();

	char *temp_noderef;
	const char *actual_noderef = noderef.c_str();

	while(true){

		temp_noderef=(char *) node->Attribute("id");
		if(strcmp(temp_noderef, actual_noderef)==0)
			break;

		node=node->NextSiblingElement();
	}

	/*Dentro do n� descendente*/
	while(node)
	{
		string id;
		id = node->Attribute("id");
		temporary_nodes.find(id)->second.set_id(id);
		printf("Node id '%s' \n", node->Attribute("id"));
		TiXmlElement *child=node->FirstChildElement();

		while(child)
		{
			if (strcmp(child->Value(),"transforms")==0)
			{

				transform = child->FirstChildElement();

				while(transform)
				{
					char* type_temp;
					type_temp = (char*)transform->Attribute("type");

					if(strcmp(type_temp,"rotate")==0){

						string axis;
						float angle;

						axis = transform->Attribute("axis");

						if(transform->QueryFloatAttribute("angle",&angle)==TIXML_SUCCESS){
							printf("Angle %f\n", angle);
						}

						Rotate *r = new Rotate(axis, angle);
						temporary_nodes.find(id)->second.push_tranformation(r);

					}

					/***/

					if(strcmp(type_temp,"scale")==0){

						char *factor;
						float f1, f2, f3;
						factor = (char*) transform->Attribute("factor");

						if(factor && sscanf(factor,"%f %f %f",&f1, &f2, &f3) == 3){

							Scale *s=new Scale(f1, f2, f3);
							temporary_nodes.find(id)->second.push_tranformation(s);

						}
					}

					/***/

					if(strcmp(type_temp,"translate")==0){

						char *to;
						float t1, t2, t3;
						to = (char*) transform->Attribute("to");

						if(to && sscanf(to,"%f %f %f",&t1, &t2, &t3) == 3){

							Translate *t=new Translate(t1, t2, t3);

							temporary_nodes.find(id)->second.push_tranformation(t);

						}
					}

					transform = transform->NextSiblingElement();
				}
			}


			if (strcmp(child->Value(),"appearanceref")==0)
			{

				/**/
				//if(child->Attribute("id") == "inherit")
				char* app_t_t;
				app_t_t = (char*)child->Attribute("id");

				if(strcmp(app_t_t,"inherit")==0)
				{
					Appearance *p = new Appearance();
					p = NULL;
					temporary_nodes.find(id)->second.push_appearance(p);
				}
				else{
					string appear_id;
					appear_id = child->Attribute("id");
					/*
					Appearance *p = new Appearance();
					p->set_id(id);
					*/

					temporary_nodes.find(id)->second.push_appearance(setAppearance(appear_id));
					/*add the Appearance with the name  id="Appearanceref"*/
				}


				printf("inside appearanceref\n");
			}


			if (strcmp(child->Value(),"primitives")==0)
			{
				//access primitives information

				printf("Inside primitives \n");

				TiXmlElement *object_primitive = child->FirstChildElement();

				while(object_primitive){

					/*Inside primitives, and recognition of primitive*/
					/*Create object based on primitive*/
					if (strcmp(object_primitive->Value(),"rectangle")==0){
						Rectangle *r=new Rectangle();

						char *xy1;
						char *xy2;
						float x1, y1, x2, y2;

						xy1 = (char*) object_primitive->Attribute("xy1");

						if(xy1 && sscanf(xy1,"%f %f",&x1, &y1) == 2){
							r->set_x1(x1);
							r->set_y1(y1);
						}

						xy2 = (char*) object_primitive->Attribute("xy2");

						if(xy2 && sscanf(xy2,"%f %f",&x2, &y2) == 2){
							r->set_x2(x2);
							r->set_y2(y2);
						}

						printf("primitive: '%s' \n", object_primitive->Value());

						temporary_nodes.find(id)->second.push_descendents(r);

					}
					object_primitive = object_primitive->NextSiblingElement();
				}


			}

			if (strcmp(child->Value(),"descendants")==0)
			{
				TiXmlElement *descendent = child->FirstChildElement();

				while(descendent){
					string noderef;
					noderef = descendent->Attribute("id");

					temporary_nodes.find(id)->second.push_descendents(getDescendent(noderef));

					descendent = descendent->NextSiblingElement();

				}

				//descendentes_id.push_back(child->Attribute("id"));
				printf("inside descendants\n");
			}

			child=child->NextSiblingElement();
		}

		return &temporary_nodes.find(id)->second;

	}

	return NULL;
}

