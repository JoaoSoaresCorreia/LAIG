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


	//First Approach:  <graph rootid="ss"> ----- <primitives>

	globals = root->FirstChildElement();

	graph = globals->NextSiblingElement("graph");

	nodesElement = graph->FirstChildElement();

	leavesElement = nodesElement -> FirstChildElement("primitives");

	//test method only!

}