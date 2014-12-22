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



float xarr[16], yarr[16], zarr[16];

void display(void)
{	
    glClear(GL_COLOR_BUFFER_BIT);

	
	glBegin(GL_POINTS);
		float i, j;//(t)
		int n;
		float x, y, z;
		float xa[4], ya[4], za[4];
//random redraw:
	for(n=0; n<16; n++) {
		
		xarr[n] = ((float)rand()/(float)(RAND_MAX) *2) -1;
		yarr[n] = ((float)rand()/(float)(RAND_MAX) *2) -1;
		zarr[n] = ((float)rand()/(float)(RAND_MAX) *2) -1;
		//display control points:
		//glColor3f(1.0, 1.0, 1.0);
		//glVertex3f(xarr[n], yarr[n], zarr[n]);
	}

		for(j=0; j<1.0; j+=.01) {
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
	char *fname;//source (ply) file name
//printf("argc = %d\n", argc);
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
