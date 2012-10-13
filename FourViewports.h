#ifndef _FOURVIEWPORTS_H_
#define _FOURVIEWPORTS_H_
/*
 *	FourViewports.h
 *
 *	Some project description here...
 *
 *	Coded by Joseph Marrero
 *	1/2/2007
 */
#include <string>
using namespace std;


void initialize( );
void deinitialize( );

void render( );
void resize( int width, int height );
void keyboard_keypress( unsigned char key, int x, int y );
void idle( );
void writeText( void *font, std::string &text, int x, int y );

void renderCube( );
void drawViewportOutline( );


double aspect = 0.0f;
double width = 0.0f, height = 0.0f;
#endif
