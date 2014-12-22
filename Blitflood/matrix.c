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
				clamp(v, i);
				printf("point num: %d x: %f, y: %f, z: %f\n", i, v[i].x, v[i].y, v[i].z);
			}
			break;
		case 2:
			for(i=0; i<cnt; i++) {
				v[i].x = v[i].x*cosf(rad)-v[i].z*sinf(rad);
				v[i].z = v[i].x*sinf(rad)+v[i].z*cosf(rad);
				clamp(v, i);
				printf("point num: %d x: %f, y: %f, z: %f\n", i, v[i].x, v[i].y, v[i].z);
			}
			break;
		case 3:
			for(i=0; i<cnt; i++) {
				v[i].x = v[i].x*cosf(rad)+v[i].y*sinf(rad);
				v[i].y = -v[i].x*sinf(rad)+v[i].y*cosf(rad);
				clamp(v, i);
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

		clamp(v, i);

		printf("point num: %d x: %f, y: %f, z: %f\n", i, v[i].x, v[i].y, v[i].z);
	}
}

scale (m4x1 *v, int cnt, float sx, float sy, float sz) {
	int i;
	for(i=0; i<cnt; i++) {
		v[i].x *= sx;
		v[i].y *= sy;
		v[i].z *= sz;

		clamp(v, i);

		printf("point num: %d x: %f, y: %f, z: %f\n", i, v[i].x, v[i].y, v[i].z);
	}
}

clamp (m4x1 *v, int i) {
	
	
	v[i].x = (v[i].x > 1) ? 1 : v[i].x;
	v[i].y = (v[i].y > 1) ? 1 : v[i].y;
	v[i].z = (v[i].z > 1) ? 1 : v[i].z;

	v[i].x = (v[i].x < -1) ? -1 : v[i].x;
	v[i].y = (v[i].y < -1) ? -1 : v[i].y;
	v[i].z = (v[i].z < -1) ? -1 : v[i].z;
}

main(argc,argv,envp)
int argc;
char **argv, **envp;
{
	struct m4x1 v;
	int i;
	int op = atoi(argv[1]);

	if(argc == 2) {
//printf("reached assign v[0]\n");

		v.x = .3;
		v.y = .76;
		v.z = .24;
		v.w = 1.0;

		switch(op) {
			case 1:
//printf("reached case 1\n");
				translate(&v, 1, .5, .7, 2);
				break;
			case 2:
				scale(&v, 1, .4, 2, .7);
				break;
			case 3:
				//third rotate parameter is axis of rotation.
				//1=x, 2=y, 3=z
				rotate(&v, 1, 3, 1.27);
				break;
		}
	} else {
		printf("usage: 1 int parameter, 1=translate, 2=scale, 3=rotate (all values, axis number, scale, and translate values hard coded)");
	}

}
