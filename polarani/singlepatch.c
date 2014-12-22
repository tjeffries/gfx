#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

float ctlmods[6][4][4][3];

GLfloat ctrlpoints[6][4][4][3];

float anglex, angley, anglez, scale;

void display(void)
{
   int i, j, k, face;
   
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glColor3f(1.0, 1.0, 1.0);
   glPushMatrix ();
   glRotatef(anglex, 1.0, 0, 0);
   glRotatef(angley, 0, 1.0, 0);
   glRotatef(anglez, 0, 0, 1.0);
   //draw axis:
   //glColor3f(.8, 0, 0);
   glBegin(GL_LINE_STRIP);
		glVertex3f(-.8, 0, 0);
		glVertex3f(.8, 0, 0);
   glEnd();
   glBegin(GL_LINE_STRIP);
		glVertex3f(0, -.8, 0);
		glVertex3f(0, .8, 0);
   glEnd();
   glBegin(GL_LINE_STRIP);
		glVertex3f(0, 0, -.8);
		glVertex3f(0, 0, .8);
   glEnd();
   //draw bezier patch(s)
   for(face=0; face<6; face++) {
		//apply all changes from ctlmods to ctrlpoints
		for(i=0; i<4; i++)
			for(j=0; j<4; j++)
				for(k=0; k<3; k++)
					ctrlpoints[face][i][j][k] = ((ctrlpoints[face][i][j][k]*scale) + ctlmods[face][i][j][k]);
	
		glClearColor (0.0, 0.0, 0.0, 0.0);
		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
		        0, 1, 12, 4, &ctrlpoints[face][0][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		glMapGrid2f(40, 0.0, 1.0, 40, 0.0, 1.0);
		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_FLAT);
		
			//glEvalMesh2(GL_FILL, 0, 40, 0, 40);
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

		//remove all changes from ctlmods
		for(i=0; i<4; i++)
			for(j=0; j<4; j++)
				for(k=0; k<3; k++)
					ctrlpoints[face][i][j][k] = ((ctrlpoints[face][i][j][k] - ctlmods[face][i][j][k])/scale);
		printf("display face #%d\n", face);
	}
printf("made it through 1 loop\n");
   glPopMatrix ();
   glFlush();
}

void init(void)
{
	int i, j, k, l;
   int ctlw, ctlh;
   ctlw = ctlh = 4;//width and height of control point array
	float max, min, div;
	anglex = 0;
	angley = 0;
	anglez = 0;
	scale = 1;
	
	GLfloat tmppts[4][4][3] = {
   /*1*/{{-1.5, -1.5, 4.0}, {-0.5, -1.5, 2.0}, 
    	{0.5, -1.5, -1.0}, {1.5, -1.5, 2.0}}, 
   /*2*/{{-1.5, -0.5, 1.0}, {-0.5, -0.5, 3.0}, 
    	{0.5, -0.5, 0.0}, {1.5, -0.5, -1.0}}, 
   /*3*/{{-1.5, 0.5, 4.0}, {-0.5, 0.5, 0.0}, 
    	{0.5, 0.5, 3.0}, {1.5, 0.5, 4.0}}, 
   /*4*/{{-1.5, 1.5, -2.0}, {-0.5, 1.5, -2.0}, 
    	{0.5, 1.5, 0.0}, {1.5, 1.5, -1.0}}
};
	
	for(l=1; l<6; l++)
		for(i=0; i<ctlw; i++)
			for(j=0; j<ctlh; j++)
				for(k=0; k<3; k++)
					ctrlpoints[l][i][j][k] = 0;
	
	for(l=0; l<1; l++)
		for(i=0; i<ctlw; i++)
			for(j=0; j<ctlh; j++)
				for(k=0; k<3; k++)
					ctrlpoints[l][i][j][k] = tmppts[i][j][k];
	
	//check max and min
	max = min = div = 0;
	for(l=0; l<6; l++)
		for(i=0; i<ctlw; i++)
			for(j=0; j<ctlh; j++)
				for(k=0; k<3; k++){
					max = (ctrlpoints[l][i][j][k] > max) ? ctrlpoints[l][i][j][k] : max;
					min = (ctrlpoints[l][i][j][k] < min) ? ctrlpoints[l][i][j][k] : min;
				}
	
	div = (fabsf(max) > fabsf(min)) ? fabsf(max) : fabsf(min);
	//printf("max = %f\n min = %f\n div = %f\n", max, min, div);
	
	//normalize control points to 1/4th size, in a -1 to +1 bounded space
	
	for(l=0; l<6; l++)
		for(i=0; i<ctlw; i++)
			for(j=0; j<ctlh; j++)
				for(k=0; k<3; k++){
					ctrlpoints[l][i][j][k] = (ctrlpoints[l][i][j][k] / (div*4));
					//set ctlmods to 0
					ctlmods[l][i][j][k] = 0;
				}
	
	printf("max = %f\n min = %f\n\n", max, min);
	
   glutInitDisplayMode(GLUT_SINGLE);
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

void drawtick(void){
	display();
}

void reshape(int x, int y){
		//printf("reshape\n");
}

void drawclock(int n){
	//anglex += 2;
	drawtick();
	glutTimerFunc(n, drawclock, n);
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
		if(key == 61)//keypress '+'
			scale *= 1.1;
		if(key == 45)//keypress '-'
			scale *= .9;
			
		if(key == 32) {//keypress 'space' - reset all rotation to zero
			anglex = 0;
			angley = 0;
			anglez = 0;
			scale = 1;
		}
		//mod all angles to -360 : 360
		anglex = fmodf(anglex, 360);
		angley = fmodf(angley, 360);
		anglez = fmodf(anglez, 360);
		//printf("anglex = %f\n", anglex);
		drawtick();
}

main(int argc, char **argv, char **envp)
{
        glutInit(&argc, argv);
        glutInitWindowSize(1000, 1000);
        glutCreateWindow(argv[0]);
        init();
        initlights();
        glutReshapeFunc(reshape);
        glutKeyboardFunc(keyboard);
        glutDisplayFunc(display);
        drawclock(2000);
        glutMainLoop();
}
