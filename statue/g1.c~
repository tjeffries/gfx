#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <GL/glut.h>

typedef struct tristruct {
	float x1, y1, z1,
		  x2, y2, z2,
		  x3, y3, z3;
} tristruct;

tristruct *tarr;

void init(void)
{
}


/*  Draw 2 diagonal lines to form an X
 */
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin (GL_LINES);
		int i;
		for(i=0; i<4999996; i++) {
			glVertex3f (t[i].x1, t[i].y1, t[i].z1);
			glVertex3f (t[i].x2, t[i].y2, t[i].z2);
			glVertex3f (t[i].x3, t[i].y3, t[i].z3);
		}
    glEnd ();
    glFlush();
}

void reshape(int w, int h)
{
	printf("reshape\n");
}

void keyboard(unsigned char key, int x, int y)
{
	printf("keypress: %d    x: %d    y: %d\n", key, x, y);

}



main(argc, argv, envp)
int argc;
char **argv, **envp;
{
   glutInit(&argc, argv);
   //glutInitDisplayMode (GLUT_SINGLE | GLUT_INDEX);
   //glutInitDisplayMode (GLUT_SINGLE);
   glutInitWindowSize (400, 400);
   glutCreateWindow (argv[0]);
   init();
   glutReshapeFunc (reshape);
   glutKeyboardFunc(keyboard);
   glutDisplayFunc (display);
   glutMainLoop();
}
