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
float maxx, maxy, maxz, minx, miny, minz, max, min, norm, norm2, xoffset, yoffset, zoffset, 
/*x, y, and z orientation:*/xor, yor, zor;
float *d;
char *fname;//source (ASCII ply) file name

void init(void){
	int i, c, fcnt;
	char *s;
	char buf[1024];
	FILE *f;

	zor = 1.0;

	f = fopen("test.ply", "r");
	fgets(buf, sizeof(buf), f);
	s=strchr(buf, '\n'); *s=0;
	
	while(strcmp(buf, "end_header")){
		fgets(buf, sizeof(buf), f);
		s=strchr(buf, '\n'); *s=0;

		if(s = strstr(buf, "element vertex ")){
			s += 15;
			v = atoi(s);
			//fprintf(stderr, "Vertices: %d\n", v);
		}
		
		if(s = strstr(buf, "element face ")){
			s += 13;
			fa = atoi(s);
			//fprintf(stderr, "Faces: %d\n", fa);
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
	//test print max and min
	//fprintf(stderr, "Max: %f, Min: %f\n", max, min);
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

	//calculation of normals
	for(i=0; i < fa; i++){
		norms[i].x = ((vertices[faces[i].p2].y-vertices[faces[i].p1].y)*(vertices[faces[i].p3].z-vertices[faces[i].p1].z))-((vertices[faces[i].p2].z-vertices[faces[i].p1].z)*(vertices[faces[i].p3].y-vertices[faces[i].p1].y));
		norms[i].y = ((vertices[faces[i].p2].z-vertices[faces[i].p1].z)*(vertices[faces[i].p3].x-vertices[faces[i].p1].x))-((vertices[faces[i].p2].x-vertices[faces[i].p1].x)*(vertices[faces[i].p3].z-vertices[faces[i].p1].z));
		norms[i].z = ((vertices[faces[i].p2].x-vertices[faces[i].p1].x)*(vertices[faces[i].p3].y-vertices[faces[i].p1].y))-((vertices[faces[i].p2].y-vertices[faces[i].p1].y)*(vertices[faces[i].p3].x-vertices[faces[i].p1].x));
		d[i] = sqrtf((norms[i].x*norms[i].x)+(norms[i].y*norms[i].y)+(norms[i].z*norms[i].z));
		
		//normalize vectors
		norms[i].x = norms[i].x/d[i];
		norms[i].y = norms[i].y/d[i];
		norms[i].z = norms[i].z/d[i];
	}
	//error checking first point fprints:
	//fprintf(stderr, "Point1: %f, %f, %f, Face1: %d, %d, %d\n", vertices[0].x, vertices[0].y, vertices[0].z, faces[0].p1, faces[0].p2, faces[0].p3);
	//fprintf(stderr, "Point2: %f, %f, %f, Face2: %d, %d, %d\n", vertices[1].x, vertices[1].y, vertices[1].z, faces[1].p1, faces[1].p2, faces[1].p3);
}

void display(void){
	float normmax, normmin = 0;
	glClear(GL_COLOR_BUFFER_BIT);
	
	glBegin(GL_TRIANGLES);
		int n;
		//draw emissive polys
		for(n=0; n < fa; n++){
			norm = (1.57079633-acosf( (norms[n].x*xor)+(norms[n].y*yor)+(norms[n].z*zor) ))/1.57079633;
			if(norm > normmax) normmax = norm;
			if(norm < normmin) normmin = norm;
			norm2 = (1.57079633-acosf(norms[n].z*1.0))/1.57079633;
			if(norm2 > 0 && norm <= 0){//if facing and not lighted
				glColor3f(.01, .01, .01);
				glVertex3f(vertices[faces[n].p1].x, vertices[faces[n].p1].y, vertices[faces[n].p1].z);
				glVertex3f(vertices[faces[n].p2].x, vertices[faces[n].p2].y, vertices[faces[n].p2].z);
				glVertex3f(vertices[faces[n].p3].x, vertices[faces[n].p3].y, vertices[faces[n].p3].z);
			} if(norm2 > 0 && norm > 0) {//if facing and lighted
				glColor3f(norm, norm, norm);
				glVertex3f(vertices[faces[n].p1].x, vertices[faces[n].p1].y, vertices[faces[n].p1].z);
				glVertex3f(vertices[faces[n].p2].x, vertices[faces[n].p2].y, vertices[faces[n].p2].z);
				glVertex3f(vertices[faces[n].p3].x, vertices[faces[n].p3].y, vertices[faces[n].p3].z);
			}
		}

	//printf("Max norm: %f\n", normmax);
	//printf("Min norm: %f\n", normmin);
	glEnd();
	glFlush();
}

void reshape(int x, int y){
	//printf("reshape\n");
}

void keyboard(unsigned char key, int x, int y){
	//printf("Keypress: %d   X: %d   Y: %d\n", key, x, y);
	//keypress causes .05 rad rotation
	if(key == 119) {//keypress 'w'
		yor = yor*cosf(.05)+zor*sinf(.05);
		zor = -yor*sinf(.05)+zor*cosf(.05);
	}
	if(key == 115) {//keypress 's'
		yor = yor*cosf(-.05)+zor*sinf(-.05);
		zor = -yor*sinf(-.05)+zor*cosf(-.05);
	}
	if(key == 97) {//keypress 'a'
		xor = xor*cosf(.05)-zor*sinf(.05);
		zor = xor*sinf(.05)+zor*cosf(.05);
	}
	if(key == 100) {//keypress 'd'
		xor = xor*cosf(-.05)-zor*sinf(-.05);
		zor = xor*sinf(-.05)+zor*cosf(-.05);
	}
	if(key == 113) {//keypress 'q'
		xor = xor*cosf(-.05)+yor*sinf(-.05);
		yor = -xor*sinf(-.05)+yor*cosf(-.05);
	}
	if(key == 101) {//keypress 'e'
		xor = xor*cosf(.05)+yor*sinf(.05);
		yor = -xor*sinf(.05)+yor*cosf(.05);
	}
	xor = xor/(xor*xor+yor*yor+zor*zor);
	yor = yor/(xor*xor+yor*yor+zor*zor);
	zor = zor/(xor*xor+yor*yor+zor*zor);
	
	display();
}

main(argc,argv,envp)
int argc;
char **argv, **envp;
{

	if(argc != 2) {
		printf("Usage: run with ASCII source name token.\n");
		exit(1);
	}

	fname = argv[1];
	
	printf("Use W, A, S, D, Q, & E to rotate light source about the x, y, and z axes\n");
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutCreateWindow(argv[0]);
	init();
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMainLoop();
}


