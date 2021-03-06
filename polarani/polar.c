#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <endian.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>


void reshape(int w, int h)
{
	printf("reshape\n");
}



float xarr[16], yarr[16], zarr[16];

void display(void)
{	
    glClear(GL_COLOR_BUFFER_BIT);

	
	glBegin(GL_POINTS);
		float i, j;//(t)
		int n;
		float x, y, z;
		float xa[4], ya[4], za[4];

	//define control points (hard coded, range from -256 to 256)
				//     1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16
	float xtmp[] = {-220,-200, 200, 220,   0,   0,   0,   0,   0,   0,   0,   0,-220,-200, 200, 220};
	float ytmp[] = {   0,-300,-300,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 300, 300,   0};
	float ztmp[] = {-256,-256,-256,-256,   0,   0,   0,   0,   0,   0,   0,   0,-256,-256,-256,-256};
	
	memcpy(&xarr, &xtmp, sizeof(xarr));
	memcpy(&yarr, &ytmp, sizeof(yarr));
	memcpy(&zarr, &ztmp, sizeof(zarr));
	
	//convert control points to between -1 and 1
	for(n=0; n<16; n++)
		xarr[n] = xarr[n]/512;
	for(n=0; n<16; n++)
		yarr[n] = yarr[n]/512;
	for(n=0; n<16; n++)
		zarr[n] = zarr[n]/512;

	//calculations for Bezier patch interpolation
		for(j=0; j<=1.0; j+=.0125) {
			for(n=0; n<4; n++) {
				xa[n] = (1-j)*(1-j)*(1-j)*(xarr[4*n+0])+3*(1-j)*(1-j)*(j)*(xarr[4*n+1])+3*(1-j)*(j)*(j)*(xarr[4*n+2])+(j*j*j)*(xarr[4*n+3]);
				ya[n] = (1-j)*(1-j)*(1-j)*(yarr[4*n+0])+3*(1-j)*(1-j)*(j)*(yarr[4*n+1])+3*(1-j)*(j)*(j)*(yarr[4*n+2])+(j*j*j)*(yarr[4*n+3]);
				za[n] = (1-j)*(1-j)*(1-j)*(zarr[4*n+0])+3*(1-j)*(1-j)*(j)*(zarr[4*n+1])+3*(1-j)*(j)*(j)*(zarr[4*n+2])+(j*j*j)*(zarr[4*n+3]);
			}
			for(i=0; i<1.0; i+=.01) {
				x = (1-i)*(1-i)*(1-i)*(xa[0])+3*(1-i)*(1-i)*(i)*(xa[1])+3*(1-i)*(i)*(i)*(xa[2])+(i*i*i)*(xa[3]);
				y = (1-i)*(1-i)*(1-i)*(ya[0])+3*(1-i)*(1-i)*(i)*(ya[1])+3*(1-i)*(i)*(i)*(ya[2])+(i*i*i)*(ya[3]);
				z = (1-i)*(1-i)*(1-i)*(za[0])+3*(1-i)*(1-i)*(i)*(za[1])+3*(1-i)*(i)*(i)*(za[2])+(i*i*i)*(za[3]);
//printf("x= %f\n", x);
				glColor3f(1-(-1)*x, 1-(-1)*y, 1-(-1)*z);
				glVertex3f(x,y,z);
			}
		}

	//display control points:
	glColor3f(1.0, 0, 0);
	for(n = 0; n<16; n++) {
		glVertex3f(xarr[n], yarr[n], zarr[n]);
	}
		
    glEnd ();
    glFlush();
//sleep(10);
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

	//printf("cos(90) = %f\n", cosf(90));

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
