#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <math.h>


float norm, d, normsx, normsy, normsz;
float p1[] = {8, 7, -10};
float p2[] = {2, 6, -8};
float p3[] = {9, 1, 5};

void init(void){
	
	int i;
	
	//subtract viewpoint
	for(i=0; i<3; i++)
		p1[i] = p1[i]-2;
	for(i=0; i<3; i++)
		p2[i] = p2[i]-2;
	for(i=0; i<3; i++)
		p3[i] = p3[i]-2;
	
	//scale based on min and max
	for(i=0; i<3; i++)
		p1[i] = p1[i]/10;
	for(i=0; i<3; i++)
		p2[i] = p2[i]/10;
	for(i=0; i<3; i++)
		p3[i] = p3[i]/10;
		
	//calculation of normals
	
		normsx = ((p2[1]-p1[1])*(p3[2]-p1[2]))-((p2[2]-p1[2])*(p3[1]-p1[1]));
		normsy = ((p2[2]-p1[2])*(p3[0]-p1[0]))-((p2[0]-p1[0])*(p3[2]-p1[2]));
		normsz = ((p2[0]-p1[0])*(p3[2]-p1[1]))-((p2[1]-p1[1])*(p3[0]-p1[0]));
		d = sqrtf((normsx*normsx)+(normsy*normsy)+(normsz*normsz));
		
		//normalize vectors
		normsx = normsx/d;
		normsy = normsy/d;
		normsz = normsz/d;
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	//draw red dot to show view point
	printf("Red dot represents camera/eye location\n");
	glBegin(GL_POINTS);
	glColor3f(1,0,0);
	glVertex3f(0,0,0);
	glEnd();
	
	//calculate RGB and draw traingle
	glBegin(GL_TRIANGLES);
	
	norm = (1.57079633-acosf( (normsx*0)+(normsy*0)+(normsz*1.0) ))/1.57079633;
	printf("RGB values = %f, %f, %f\n", 0.0, 0.0, norm);
	if(norm > 0) {//draw lighted triangle
		glColor3f(0.0, 0.0, norm);
		glVertex3f(p1[0], p1[1], p1[2]);
		glVertex3f(p2[0], p2[1], p2[2]);
		glVertex3f(p3[0], p3[1], p3[2]);
	}

	glEnd();
	glFlush();
}

void reshape(int x, int y){
	//printf("reshape\n");
}

void keyboard(unsigned char key, int x, int y){
	//printf("Keypress: %d   X: %d   Y: %d\n", key, x, y);
}

main(argc,argv,envp)
int argc;
char **argv, **envp;
{

	if(argc != 1) {
		printf("Usage: no inputs, all vertices hardcoded.\n");
		exit(1);
	}
	
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutCreateWindow(argv[0]);
	init();
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMainLoop();
}


