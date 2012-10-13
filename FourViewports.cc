/*
 *	FourViewports.cc
 * 
 *	Some project description here...
 *
 *	Coded by Joseph Marrero
 *	1/2/2007
 */
#include <cassert>
#include <iostream>
#include "FourViewports.h"
#include <GL/glut.h>

using namespace std;

int main( int argc, char *argv[] )
{
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE );
	glutInitWindowSize( 640, 480 );
	
	glutCreateWindow( "FourViewports" );

	glutDisplayFunc( render );
	glutReshapeFunc( resize );
	glutKeyboardFunc( keyboard_keypress );
	glutIdleFunc( idle );

	initialize( );
	glutMainLoop( );
	deinitialize( );

	return 0;
}



void initialize( )
{
	glEnable( GL_ALPHA_TEST );
	
	glEnable( GL_POINT_SMOOTH );
	glEnable( GL_LINE_SMOOTH );
	glEnable( GL_POLYGON_SMOOTH );
	glHint( GL_POINT_SMOOTH_HINT, GL_NICEST );
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
	glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	

	glShadeModel( GL_SMOOTH );
	glClearDepth( 1.0f );						
	glDepthFunc( GL_LEQUAL );
	//glEnable( GL_DEPTH_TEST );
	glDisable( GL_CULL_FACE );
	glFrontFace( GL_CW );


	glPixelStorei( GL_PACK_ALIGNMENT, 4 );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );


	// TO DO: Initialization code goes here...
}

void deinitialize( )
{
	// TO DO: Deinitialization code goes here...
}


void render( )
{
	glClearColor( 0.1f, 0.1f, 0.1f, 0.1f );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// top-left
	glViewport( 0, 0, width / 2.0, height / 2.0 );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	glOrtho( -1.0 * aspect, 1.0 * aspect, -1.0, 1.0, -10.0, 10.0 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );
	glTranslatef( 0.0, 0.0f, -6.0f );
	//glRotatef( 90.0f, 1.0, 0.0f, 0.0f );
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	renderCube( );
	//drawViewportOutline( );

	/* Write text */
	int width = glutGet((GLenum)GLUT_WINDOW_WIDTH);
	int height = glutGet((GLenum)GLUT_WINDOW_HEIGHT);

	writeText( GLUT_BITMAP_HELVETICA_18, std::string("Front"), 2, 22 );
	writeText( GLUT_BITMAP_8_BY_13, std::string("Press Q to quit."), 2, 5 );

	// top-right
	glViewport( width / 2.0, 0, width / 2.0, height / 2.0 );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	glOrtho( -1.0 * aspect, 1.0 * aspect, -1.0, 1.0, -10.0, 10.0 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );
	glTranslatef( 0.0, 0.0f, -6.0f );
	glRotatef( 90.0f, 1.0, 0.0f, 0.0f );
	renderCube( );
	//drawViewportOutline( );

	/* Write text */
	width = glutGet((GLenum)GLUT_WINDOW_WIDTH);
	height = glutGet((GLenum)GLUT_WINDOW_HEIGHT);

	writeText( GLUT_BITMAP_HELVETICA_18, std::string("Top"), 2, 22 );

	// bottom-left
	glViewport( 0, height / 2.0, width / 2.0, height / 2.0 );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	glOrtho( -1.0 * aspect, 1.0 * aspect, -1.0, 1.0, -10.0, 10.0 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );
	glTranslatef( 0.0, 0.0f, -6.0f );
	glRotatef( 90.0f, 0.0, 1.0f, 0.0f );
	renderCube( );
	//drawViewportOutline( );

	/* Write text */
	width = glutGet((GLenum)GLUT_WINDOW_WIDTH);
	height = glutGet((GLenum)GLUT_WINDOW_HEIGHT);

	writeText( GLUT_BITMAP_HELVETICA_18, std::string("Side"), 2, 22 );

	// bottom-right
	glViewport( width / 2.0, height / 2.0, width / 2.0, height / 2.0 );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	gluPerspective( 40.0f, aspect, 1.0, 50.0 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	glTranslatef( 0.0, 0.0f, -6.0f );
	glRotatef( 45.0f, 1.0, 1.0f, 0.0f );
	renderCube( );
	//drawViewportOutline( );

	/* Write text */
	width = glutGet((GLenum)GLUT_WINDOW_WIDTH);
	height = glutGet((GLenum)GLUT_WINDOW_HEIGHT);

	writeText( GLUT_BITMAP_HELVETICA_18, std::string("Perspective"), 2, 22 );
	
	glutSwapBuffers( );
}

void resize( int w, int h )
{
	//glViewport( 0, 0, width, height );

	width = w;
	height = h;
	

	if( height == 0 )
		height = 1;
	aspect = (double) width / (double) height;
	
	//glMatrixMode( GL_PROJECTION );
	//glLoadIdentity( );
	//gluPerspective( 60.0f, aspect, 1.0, 50.0 );
	////glOrtho( -1.0, 1.0, -1.0, 1.0, -100.0, 100.0 );
	//glMatrixMode( GL_MODELVIEW );
}

void keyboard_keypress( unsigned char key, int x, int y )
{
	switch( key )
	{
		case 'Q':
		case 'q':
		case GLUT_KEY_F1:
		case GLUT_KEY_END:
			deinitialize( );
			exit( 0 );
			break;
		default:
			break;
	}

}

void idle( )
{ glutPostRedisplay( ); }

void writeText( void *font, std::string &text, int x, int y )
{
	int width = glutGet( (GLenum) GLUT_WINDOW_WIDTH );
	int height = glutGet( (GLenum) GLUT_WINDOW_HEIGHT );

	glDisable( GL_DEPTH_TEST );
	glDisable( GL_TEXTURE_2D );
	//glDisable( GL_LIGHTING );

	glMatrixMode( GL_PROJECTION );
	glPushMatrix( );
		glLoadIdentity( );	
		glOrtho( 0, width, 0, height, 1.0, 10.0 );
			
		glMatrixMode( GL_MODELVIEW );
		glPushMatrix( );
			glLoadIdentity( );
			glColor3f( 1.0f, 1.0f, 1.0f );
			glTranslatef( 0.0f, 0.0f, -1.0f );
			glRasterPos2i( x, y );

			for( unsigned int i = 0; i < text.size( ); i++ )
				glutBitmapCharacter( font, text[ i ] );
			
		glPopMatrix( );
		glMatrixMode( GL_PROJECTION );
	glPopMatrix( );
	glMatrixMode( GL_MODELVIEW );

	//glEnable( GL_LIGHTING );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_TEXTURE_2D );

}


void renderCube( )
{
	//static float rot = 0.0f;
	//if( rot >= 360.0f )
	//	rot = 0.0f;
	// TO DO: Drawing code goes here...
	//glTranslatef( 0.0, 0.0f, -6.0f );
	//glRotatef( 45.0f, -1.0f, -1.0f, -1.0f );
	//glRotatef( rot, 0.0f, 1.0f, 0.0f);                        // Rotate The Cube On X, Y & Z
	

        glBegin(GL_QUADS);                                      // Start Drawing The Cube
                glColor3f(0.0f,1.0f,0.0f);                      // Set The Color To Green
                glVertex3f( 1.0f, 1.0f,-1.0f);                  // Top Right Of The Quad (Top)
				glColor3f(0.0f,0.7f,0.0f); 
                glVertex3f(-1.0f, 1.0f,-1.0f);                  // Top Left Of The Quad (Top)
				glColor3f(0.0f,0.4f,0.0f); 
                glVertex3f(-1.0f, 1.0f, 1.0f);                  // Bottom Left Of The Quad (Top)
				glColor3f(0.0f,0.2f,0.0f); 
                glVertex3f( 1.0f, 1.0f, 1.0f);                  // Bottom Right Of The Quad (Top)
				glColor3f(1.0f,0.5f,0.0f);                      // Set The Color To Orange
                glVertex3f( 1.0f,-1.0f, 1.0f);                  // Top Right Of The Quad (Bottom)
				glColor3f(0.8f,0.3f,0.0f);  
                glVertex3f(-1.0f,-1.0f, 1.0f);                  // Top Left Of The Quad (Bottom)
				glColor3f(0.7f,0.2f,0.0f);  
                glVertex3f(-1.0f,-1.0f,-1.0f);                  // Bottom Left Of The Quad (Bottom)
				glColor3f(0.4f,0.1f,0.0f);  
                glVertex3f( 1.0f,-1.0f,-1.0f);                  // Bottom Right Of The Quad (Bottom)
				glColor3f(1.0f,0.0f,0.0f);                      // Set The Color To Red
                glVertex3f( 1.0f, 1.0f, 1.0f);                  // Top Right Of The Quad (Front)
				glColor3f(0.8f,0.0f,0.0f);
                glVertex3f(-1.0f, 1.0f, 1.0f);                  // Top Left Of The Quad (Front)
				glColor3f(0.6f,0.0f,0.0f);
                glVertex3f(-1.0f,-1.0f, 1.0f);                  // Bottom Left Of The Quad (Front)
				glColor3f(0.2f,0.0f,0.0f);
                glVertex3f( 1.0f,-1.0f, 1.0f);                  // Bottom Right Of The Quad (Front)
				glColor3f(0.2f,0.2f,0.0f);                      // Set The Color To Yellow
                glVertex3f( 1.0f,-1.0f,-1.0f);                  // Bottom Left Of The Quad (Back)
				glColor3f(0.6f,0.6f,0.0f);
                glVertex3f(-1.0f,-1.0f,-1.0f);                  // Bottom Right Of The Quad (Back)
				glColor3f(0.8f,0.8f,0.0f);
                glVertex3f(-1.0f, 1.0f,-1.0f);                  // Top Right Of The Quad (Back)
				glColor3f(1.0f,1.0f,0.0f);
                glVertex3f( 1.0f, 1.0f,-1.0f);                  // Top Left Of The Quad (Back)
				glColor3f(0.0f,0.0f,1.0f);                      // Set The Color To Blue
                glVertex3f(-1.0f, 1.0f, 1.0f);                  // Top Right Of The Quad (Left)
				glColor3f(0.0f,0.0f,0.8f); 
                glVertex3f(-1.0f, 1.0f,-1.0f);                  // Top Left Of The Quad (Left)
				glColor3f(0.0f,0.0f,0.6f); 
                glVertex3f(-1.0f,-1.0f,-1.0f);                  // Bottom Left Of The Quad (Left)
				glColor3f(0.0f,0.0f,0.2f); 
                glVertex3f(-1.0f,-1.0f, 1.0f);                  // Bottom Right Of The Quad (Left)
                glColor3f(1.0f,0.0f,1.0f);                      // Set The Color To Violet
                glVertex3f( 1.0f, 1.0f,-1.0f);                  // Top Right Of The Quad (Right)
				glColor3f(0.6f,0.0f,0.6f);
                glVertex3f( 1.0f, 1.0f, 1.0f);                  // Top Left Of The Quad (Right)
				glColor3f(0.4f,0.0f,0.4f);
                glVertex3f( 1.0f,-1.0f, 1.0f);                  // Bottom Left Of The Quad (Right)
				glColor3f(0.2f,0.0f,0.2f);
                glVertex3f( 1.0f,-1.0f,-1.0f);                  // Bottom Right Of The Quad (Right)
        glEnd();  



	//rot += 0.2f;
}
void drawViewportOutline( )
{
	float w = glutGet( (GLenum) GLUT_WINDOW_WIDTH ) / 2.0f;
	float h = glutGet( (GLenum) GLUT_WINDOW_HEIGHT ) / 2.0f;

	glPushMatrix( );
		glLoadIdentity( );

		glPushAttrib( GL_CURRENT_BIT );
			glColor3f( 1.0f, 1.0f, 1.0f );
			glBegin( GL_LINE_LOOP );
				glVertex2i( -1.0 * aspect, -1.0f );
				glVertex2i( 1.0 * aspect, -1.0f );
				glVertex2i( 1.0 * aspect, 1.0f );
				glVertex2i( -1.0 * aspect, 1.0f );
			glEnd( );
		glPopAttrib( );
	glPopMatrix( );
}