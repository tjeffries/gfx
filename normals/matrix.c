#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define XAXIS 1;
#define YAXIS 2;
#define ZAXIS 4;

typedef struct m4x1 {
	float x,y,z,w;
} m4x1;

rotate(m4x1 *v, int cnt, int axis, float rad) {
	switch(axis) {
		int i;
		case 1:
			for(i=0; i<cnt; i++) {
				v[i].y = v[i].y*cosf(rad)+v[i].z*sinf(rad);
				v[i].z = -v[i].y*sinf(rad)+v[i].z*cosf(rad);
				printf("point num: %d x: %f, y: %f, z: %f\n", i, v[i].x, v[i].y, v[i].z);
			}
			break;
		case 2:
			for(i=0; i<cnt; i++) {
				v[i].x = v[i].x*cosf(rad)-v[i].z*sinf(rad);
				v[i].z = v[i].x*sinf(rad)+v[i].z*cosf(rad);
				printf("point num: %d x: %f, y: %f, z: %f\n", i, v[i].x, v[i].y, v[i].z);
			}
			break;
		case 3:
			for(i=0; i<cnt; i++) {
				v[i].x = v[i].x*cosf(rad)+v[i].y*sinf(rad);
				v[i].y = -v[i].x*sinf(rad)+v[i].y*cosf(rad);
				printf("point num: %d x: %f, y: %f, z: %f\n", i, v[i].x, v[i].y, v[i].z);
			}
			break;
	}
}

translate(m4x1 *v, int cnt, float dx, float dy, float dz) {
	int i;
	for(i=0; i<cnt; i++) {
		v[i].x += dx;
		v[i].y += dy;
		v[i].z += dz;
		printf("point num: %d x: %f, y: %f, z: %f\n", i, v[i].x, v[i].y, v[i].z);
	}
}

scale (m4x1 *v, int cnt, float sx, float sy, float sz) {
	int i;
	for(i=0; i<cnt; i++) {
		v[i].x *= sx;
		v[i].y *= sy;
		v[i].z *= sz;
		printf("point num: %d x: %f, y: %f, z: %f\n", i, v[i].x, v[i].y, v[i].z);
	}
}

main(argc,argv,envp)
int argc;
char **argv, **envp;
{
	m4x1 *v;
	int i;
	int op = atoi(argv[1]);
	
	if(argc = 1) {
		v[0].x = .3;
		v[0].y = .76;
		v[0].z = .24;
		v[0].w = 1.0;
		switch(op) {
			case 1:
				translate(v, 1, .5, .7, 2);
				break;
			case 2:
				
				break;
			case 3:
				
				break;
		}
	} else {
		
	}
}
