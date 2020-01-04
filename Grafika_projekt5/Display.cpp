#include "Display.h"

Display::Display(int* argc, char** argv)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(300, 300);                    // window size
	glutInitWindowPosition(500, 500);                // distance from the top-left screen
	glutCreateWindow("BadproG - Hello world :D");    // message displayed on top bar window
	glutDisplayFunc(display);
	glutMainLoop();
}

Display::~Display()
{
}

void Display::display()
{
}
