#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

GLfloat ctrlpoints[4][4][3] = {
   /*1*/{{-1.5, -1.5, 4.0}, {-0.5, -1.5, 2.0}, 
    	{0.5, -1.5, -1.0}, {1.5, -1.5, 2.0}}, 
   /*2*/{{-1.5, -0.5, 1.0}, {-0.5, -0.5, 3.0}, 
    	{0.5, -0.5, 0.0}, {1.5, -0.5, -1.0}}, 
   /*3*/{{-1.5, 0.5, 4.0}, {-0.5, 0.5, 0.0}, 
    	{0.5, 0.5, 3.0}, {1.5, 0.5, 4.0}}, 
   /*4*/{{-1.5, 1.5, -2.0}, {-0.5, 1.5, -2.0}, 
    	{0.5, 1.5, 0.0}, {1.5, 1.5, -1.0}}
};

float anglex, angley, anglez;

void display(void)
{
   int i, j, k;
   
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glColor3f(1.0, 1.0, 1.0);
   glPushMatrix ();
   glRotatef(anglex, 1.0, 0, 0);
   glRotatef(angley, 0, 1.0, 0);
   glRotatef(anglez, 0, 0, 1.0);
   	glEvalMesh2(GL_FILL, 0, 40, 0, 40);
   /*for (j = 0; j <= 8; j++) {
      glBegin(GL_LINE_STRIP);
      for (i = 0; i <= 30; i++)
         glEvalCoord2f((GLfloat)i/30.0, (GLfloat)j/8.0);
      glEnd();
      glBegin(GL_LINE_STRIP);
      for (i = 0; i <= 30; i++)
         glEvalCoord2f((GLfloat)j/8.0, (GLfloat)i/30.0);
      glEnd();
   }*/
   glPopMatrix ();
   glFlush();
}

void init(void)
{
	int i, j, k;
   int ctlw, ctlh;
   ctlw = ctlh = 4;//width and height of control point array
   int ctlp = 3;//floats per control point
	float max, min, div;
	anglex = 0;
	angley = 0;
	anglez = 0;
	
	max = min = div = 0;
	for(i=0; i<ctlw; i++){
		for(j=0; j<ctlh; j++){
			for(k=0; k<ctlp; k++){
				max = (ctrlpoints[i][j][k] > max) ? ctrlpoints[i][j][k] : max;
				min = (ctrlpoints[i][j][k] < min) ? ctrlpoints[i][j][k] : min;
			}
		}
	}
	
	div = (fabsf(max) > fabsf(min)) ? fabsf(max) : fabsf(min);
	//printf("max = %f\n min = %f\n div = %f\n", max, min, div);
	
	//normalize control points to -1 to +1 bounded space
	for(i=0; i<ctlw; i++){
		for(j=0; j<ctlh; j++){
			for(k=0; k<ctlp; k++){
				ctrlpoints[i][j][k] = (ctrlpoints[i][j][k] / div);
			}
		}
	}
	printf("max = %f\n min = %f\n\n", max, min);
	
	
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
           0, 1, 12, 4, &ctrlpoints[0][0][0]);
   glEnable(GL_MAP2_VERTEX_3);
   glMapGrid2f(40, 0.0, 1.0, 40, 0.0, 1.0);
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_FLAT);
}

void initlights(void)
{
   GLfloat ambient[] = {0.2, 0.2, 0.2, 1.0};
   GLfloat position[] = {0.0, 0.0, 2.0, 1.0};
   GLfloat mat_diffuse[] = {0.6, 0.6, 0.6, 1.0};
   GLfloat mat_specular[] = {2.8, 2.8, 1.0, 1.0};
   GLfloat mat_shininess[] = {50.0};

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT0, GL_POSITION, position);

   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void reshape(int x, int y){
		printf("reshape\n");
}

void keyboard(unsigned char key, int x, int y){
		//printf("Keypress: %d   X: %d   Y: %d\n", key, x, y);
		if(key == 119)//w key pressed
			anglex -= 3;
		if(key == 115)//s key pressed
			anglex += 3;
		if(key == 97)//keypress 'a'
			angley -= 3;
		if(key == 100)//keypress 'd'
			angley += 3;
		if(key == 113)//keypress 'q'
			anglez += 3;
		if(key == 101)//keypress 'e'
			anglez -= 3;
		//mod all angles to -360 : 360
		anglex = fmodf(anglex, 360);
		angley = fmodf(angley, 360);
		anglez = fmodf(anglez, 360);
		//printf("anglex = %f\n", anglex);
		display();
}

main(argc,argv,envp)
int argc;
char **argv, **envp;
{
        glutInit(&argc, argv);
        glutInitWindowSize(1000, 1000);
        glutCreateWindow(argv[0]);
        init();
        initlights();
        glutReshapeFunc(reshape);
        glutKeyboardFunc(keyboard);
        glutDisplayFunc(display);
        glutMainLoop();
}
