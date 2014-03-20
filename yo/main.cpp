#include "common.h"
#include "app.h"

#define WINDOW_TITLE_PREFIX "Chapter 1"


int CurrentWidth = 800,
	CurrentHeight = 600,
	WindowHandle = 0;

void Initialize(int, char*[]);
void InitWindow(int, char*[]);
void ResizeFunction(int, int);
void RenderFunction(void);
void KeyboardSpecialFunction( int key, int x, int y );
void KeyboardFunction( unsigned char key, int x, int y );

App app;

int main(int argc, char* argv[]){
	Initialize(argc, argv);

	glutMainLoop();

	exit(EXIT_SUCCESS);
}

void Initialize(int argc, char* argv[]){
	InitWindow(argc, argv);

	fprintf(stdout,"INFO: OpenGL Version: %s\n",glGetString(GL_VERSION));

    GLenum err = glewInit();
    if (GLEW_OK != err){
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(1);
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    // Clear all GL errors (bug in glew).
    // see: https://www.opengl.org/wiki/OpenGL_Loading_Library#GLEW
    while(glGetError() != GL_NO_ERROR);

    app.init();
}

void InitWindow(int argc, char* argv[]){
	glutInit(&argc, argv);

	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(
		GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS
	);

	glutInitWindowSize(CurrentWidth, CurrentHeight);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	WindowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);

	if(WindowHandle < 1) {
		fprintf(stderr,"ERROR: Could not create a new rendering window.\n");
		exit(EXIT_FAILURE);
	}

	glutReshapeFunc(ResizeFunction);
	glutDisplayFunc(RenderFunction);
    glutSpecialFunc(KeyboardSpecialFunction);
    glutKeyboardFunc(KeyboardFunction);
}

void KeyboardSpecialFunction( int key, int x, int y ){
    // TODO
}

void KeyboardFunction( unsigned char key, int x, int y ){
    if ( key == 27 ){
        app.destroy();
        exit(0);
    }
}

void ResizeFunction(int Width, int Height){
	CurrentWidth = Width;
	CurrentHeight = Height;
	glViewport(0, 0, CurrentWidth, CurrentHeight);
}

void RenderFunction(void){
	app.render();
	glutSwapBuffers();
	glutPostRedisplay();
}
