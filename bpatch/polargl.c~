#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <endian.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <GL/glut.h>


void reshape(int w, int h)
{
	printf("reshape\n");
}

GLfloat ctrlpoints[4][4][3] = {
   {{-.5, -.5, 1.0}, {-0.5, -.75, 1.0}, {0.5, -.5, -1.0}, {1.0, -1.0, 1.0}}, 
   {{-.5, -0.5, 1.0}, {-0.5, -0.5, 1.0}, {0.5, -0.5, 0.0}, {.5, -0.5, -1.0}}, 
   {{-.5,  0.5, 1.0}, {-0.5, 0.5,  0.0}, {0.5, 0.5, 0.0}, {.5, 0.5, 1.0}}, 
   {{-.5, 1.0, -1.0}, {-0.5, .25, -1.0}, {0.5, .5, 0.0}, {.5, .5, -1.0}}
};

void display(void)
{
   int i, j, n;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//display control points:
	glBegin(GL_POINTS);
	glColor3f(1.0, 0, 0);
	for(i=0; i<4; i++)
		for(j=0; j<4; j++) {
			glVertex3f(ctrlpoints[i][j][0], ctrlpoints[i][j][1], ctrlpoints[i][j][2]);
			printf("%f, %f, %f\n", ctrlpoints[i][j][0], ctrlpoints[i][j][1], ctrlpoints[i][j][2] );
	}
	glEnd();

   
   glColor3f(1.0, 1.0, 1.0);
   //glPushMatrix ();
   //glRotatef(85.0, 1.0, 1.0, 1.0);
   for (j = 0; j <= 8; j++) {
      glBegin(GL_LINE_STRIP);
      for (i = 0; i <= 30; i++)
         glEvalCoord2f((GLfloat)i/30.0, (GLfloat)j/8.0);
      glEnd();
      glBegin(GL_LINE_STRIP);
      for (i = 0; i <= 30; i++)
         glEvalCoord2f((GLfloat)j/8.0, (GLfloat)i/30.0);
      glEnd();
   }
   //glPopMatrix ();
   glFlush();
}

void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
           0, 1, 12, 4, &ctrlpoints[0][0][0]);
   glEnable(GL_MAP2_VERTEX_3);
   glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_FLAT);
}

void keyboard(unsigned char key, int x, int y)
{
	display();
}

main(argc, argv, envp)
int argc;
char **argv, **envp;
{
	int i;
	int frame =0;

	if(argc != 1) {
		printf("usage: no inputs.\n");
		exit(1);
	}
	srand((unsigned int)time(NULL));
	

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
