#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <math.h>

struct vert{
	float x, y, z;
} *vertices, *norms;

struct face{
	int p1, p2, p3;
} *faces;

int v, fa;
float maxx, maxy, maxz, minx, miny, minz, max, min, norm, xoffset, yoffset, zoffset;
float *d;

void init(void){
	int i, c, fcnt;
	char *s;
	char buf[1024];
	FILE *f;

	f = fopen("test.ply", "r");
	fgets(buf, sizeof(buf), f);
	s=strchr(buf, '\n'); *s=0;
	
	while(strcmp(buf, "end_header")){
		fgets(buf, sizeof(buf), f);
		s=strchr(buf, '\n'); *s=0;

		if(s = strstr(buf, "element vertex ")){
			s += 15;
			v = atoi(s);
			fprintf(stderr, "Vertices: %d\n", v);
		}
		
		if(s = strstr(buf, "element face ")){
			s += 13;
			fa = atoi(s);
			fprintf(stderr, "Faces: %d\n", fa);
		}
	}

	vertices = (struct vert *) malloc(v*sizeof(struct vert));
	faces = (struct face *) malloc(fa*sizeof(struct face));
	norms = (struct vert *) malloc(fa*sizeof(struct vert));
	d = (float *) malloc(fa*sizeof(float *));

	for (i=0; i < v; i++){
		fgets(buf, sizeof(buf), f);
		sscanf(buf, "%f %f %f", &(vertices[i].x), &(vertices[i].y), &(vertices[i].z));
		if(vertices[i].x > maxx) maxx = vertices[i].x;
		if(vertices[i].x < minx) minx = vertices[i].x;
		if(vertices[i].y > maxy) maxy = vertices[i].y;
		if(vertices[i].y < miny) miny = vertices[i].y;
		if(vertices[i].z > maxz) maxz = vertices[i].z;
		if(vertices[i].z < minz) minz = vertices[i].z;
	}
	if ((maxx - minx) > (maxy - miny)){
		if ((maxx - minx) > (maxz - minz)){
			max = maxx;
			min = minx;
		}
		else{
			max = maxz;
			min = minz;
		}
	}
	else if ((maxy - miny) > (maxz - minz)){
		max = maxy;
		min = minz;
	}
	else{
		max = maxz;
		min = minz;
	}
	fprintf(stderr, "Max: %f, Min: %f\n", max, min);
	for(i=0; i < v; i++){
		vertices[i].x /= (max - min)/6.0;
		vertices[i].y /= (max - min)/6.0;
		vertices[i].z /= (max - min)/6.0;
		xoffset += vertices[i].x;
		yoffset += vertices[i].y;
		zoffset += vertices[i].z;
	}
	xoffset /= v;
	yoffset /= v;
	zoffset /= v;
	for(i=0; i < v; i++){
		vertices[i].x -= xoffset;
		vertices[i].y -= yoffset;
		vertices[i].z -= zoffset;
	}
	for(i=0; i < fa; i++){
		fgets(buf, sizeof(buf), f);
		sscanf(buf, "%d %d %d %d", &fcnt, &(faces[i].p1), &(faces[i].p2), &(faces[i].p3));
	}
	fclose(f);
	for(i=0; i < fa; i++){
		norms[i].x = ((vertices[faces[i].p2].y-vertices[faces[i].p1].y)*(vertices[faces[i].p3].z-vertices[faces[i].p1].z))-((vertices[faces[i].p2].z-vertices[faces[i].p1].z)*(vertices[faces[i].p3].y-vertices[faces[i].p1].y));
		norms[i].y = ((vertices[faces[i].p2].z-vertices[faces[i].p1].z)*(vertices[faces[i].p3].x-vertices[faces[i].p1].x))-((vertices[faces[i].p2].x-vertices[faces[i].p1].x)*(vertices[faces[i].p3].z-vertices[faces[i].p1].z));
		norms[i].z = ((vertices[faces[i].p2].x-vertices[faces[i].p1].x)*(vertices[faces[i].p3].y-vertices[faces[i].p1].y))-((vertices[faces[i].p2].y-vertices[faces[i].p1].y)*(vertices[faces[i].p3].x-vertices[faces[i].p1].x));
		d[i] = sqrtf((norms[i].x*norms[i].x)+(norms[i].y*norms[i].y)+(norms[i].z*norms[i].z));
	}
	fprintf(stderr, "Point1: %f, %f, %f, Face1: %d, %d, %d\n", vertices[0].x, vertices[0].y, vertices[0].z, faces[0].p1, faces[0].p2, faces[0].p3);
	fprintf(stderr, "Point2: %f, %f, %f, Face2: %d, %d, %d\n", vertices[1].x, vertices[1].y, vertices[1].z, faces[1].p1, faces[1].p2, faces[1].p3);
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	
	glBegin(GL_TRIANGLES);
		int n;
		for(n=0; n < fa; n++){
			norm = (1.57079633-acosf((norms[n].x*0)+(norms[n].y*0)+(norms[n].z*1.0)))/1.57079633;
			fprintf(stderr, "Norm: %f\n", norm);
			if(norm > 0){
				glColor3f(norm, norm, norm);
				glVertex3f(vertices[faces[n].p1].x, vertices[faces[n].p1].y, vertices[faces[n].p1].z);
				glVertex3f(vertices[faces[n].p2].x, vertices[faces[n].p2].y, vertices[faces[n].p2].z);
				glVertex3f(vertices[faces[n].p3].x, vertices[faces[n].p3].y, vertices[faces[n].p3].z);
			}
		}
	glEnd();
	glFlush();
}

void reshape(int x, int y){
	printf("reshape\n");
}

void keyboard(unsigned char key, int x, int y){
	printf("Keypress: %d   X: %d   Y: %d\n", key, x, y);
}

main(argc,argv,envp)
int argc;
char **argv, **envp;
{
	glutInit(&argc, argv);
	glutInitWindowSize(400, 400);
	glutCreateWindow(argv[0]);
	init();
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMainLoop();	
}
