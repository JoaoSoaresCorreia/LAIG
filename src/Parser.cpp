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

	textures = globals->NextSiblingElement("texxtures");

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
		TiXmlElement* drawing = globals->FirstChildElement("drawing");

		if(drawing)
		{
			printf("Inside drawing \n");
			//values to object
		}


		TiXmlElement* culling = globals->FirstChildElement("culling");

		if(culling)
		{
			printf("Inside culling \n");
			//values to object
		}


		TiXmlElement* lighting = globals->FirstChildElement("lighting");

		if(lighting)
		{
			printf("Inside lighting \n");
			//values to object
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
		//printf("Graph root id = %s ", graph->Attribute("rootid"));
		node = graph->FirstChildElement();
		char *prefix="  -";

		while(node)
		{
			printf("Node id '%s' \n", node->Attribute("id"));
			TiXmlElement *child=node->FirstChildElement();
			
			while(child)
			{
				if (strcmp(child->Value(),"primitives")==0)
				{
					//access primitives information

					printf("Inside primitives \n");

					TiXmlElement *object_primitive = child->FirstChildElement();

					while(object_primitive){

						/*Inside primitives, and recognition of primitive*/
						/*Create object based on primitive*/

						object_primitive = object_primitive->NextSiblingElement();
					}

					/*
					// access node data by searching for its id in the nodes section
					
					TiXmlElement *noderef=findChildByAttribute(nodesElement,"id",child->Attribute("id"));

					if (noderef)
					{
						// print id
						printf("  - Node id: '%s'\n", child->Attribute("id"));

						// prints some of the data
						printf("    - Material id: '%s' \n", noderef->FirstChildElement("material")->Attribute("id"));
						printf("    - Texture id: '%s' \n", noderef->FirstChildElement("texture")->Attribute("id"));

						// repeat for other leaf details
					}
					else
						printf("  - Node id: '%s': NOT FOUND IN THE NODES SECTION\n", child->Attribute("id"));
						*/

				}
				/*
				if (strcmp(child->Value(),"Leaf")==0)
				{
					// access leaf data by searching for its id in the leaves section
					TiXmlElement *leaf=findChildByAttribute(leavesElement,"id",child->Attribute("id"));

					if (leaf)
					{
						// it is a leaf and it is present in the leaves section
						printf("  - Leaf id: '%s' ; type: '%s'\n", child->Attribute("id"), leaf->Attribute("type"));

						// repeat for other leaf details
					}
					else
						printf("  - Leaf id: '%s' - NOT FOUND IN THE LEAVES SECTION\n",child->Attribute("id"));
				}
				*/
				child=child->NextSiblingElement();
			}
			node=node->NextSiblingElement();
		}
	}

}