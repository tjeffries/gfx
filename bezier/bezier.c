#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <endian.h>
#include <GL/glut.h>

#define VSTR "element vertex "
#define FSTR "element face "


void reshape(int w, int h)
{
	printf("reshape\n");
}

void keyboard(unsigned char key, int x, int y)
{
	printf("keypress: %d    x: %d    y: %d\n", key, x, y);

}

float x0, y0, x1, y1, x2, y2;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
		float i;//(t)
		float x, y, z;
		printf("reached beginning of display loop\n");

		for(i=0; i<1.0; i+=.00001) {

			x = ( (1-i)*(1-i)*(x0)+2*(1-i)*(i*x1)+i*i*(x2) );
			y = ( (1-i)*(1-i)*(y0)+2*(1-i)*(i*y1)+i*i*(y2) );
			//to draw point: glvertex3f(x, y, 0);
//printf("run display loop, t= %f x= %f y=%f\n", i, x, y);
			glVertex3f(x,y,z);
		}
    glEnd ();
    glFlush();
//sleep(10);
}

main(argc, argv, envp)
int argc;
char **argv, **envp;
{
	int frame =0;
	char *fname;//source (ply) file name
//printf("argc = %d\n", argc);
	if(argc != 7) {
		printf("usage: run with 3 points in format 'x1 y1 x2 y2 x3 y3'.\n");
		exit(1);
	}

	x0 = atof(argv[1]);
	y0 = atof(argv[2]);
	x1 = atof(argv[3]);
	y1 = atof(argv[4]);
	x2 = atof(argv[5]);
	y2 = atof(argv[6]);

printf("program start.\n");

	glutInit(&argc, argv);
	//glutInitDisplayMode (GLUT_SINGLE | GLUT_INDEX);
	//glutInitDisplayMode (GLUT_SINGLE);
	glutInitWindowSize (800, 800);
	glutCreateWindow (argv[0]);
	glutReshapeFunc (reshape);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc (display);
	glutMainLoop();

printf("program end.\n");
}


