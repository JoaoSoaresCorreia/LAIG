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

	//First Approach:  <graph rootid="ss"> ----- <primitives>



}