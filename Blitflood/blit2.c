#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>



#define WIDTH 64
#define HEIGHT 64


unsigned char *frameBuffer, masks[8];

clearfb() {
	memset(frameBuffer, 0, (WIDTH*HEIGHT)>>3);
}



drawPoint(x,y)
int x,y;
{
	char str[256];
	sprintf(str, "%c[%02d;%02dH*", 27, 1+y, 1+x);
	printf("%s", str);
}


clearPoint(x,y)
int x,y;
{
	char str[256];
	sprintf(str, "%c[%02d;%02dH ", 27, 1+y, 1+x);
	//printf("%s", str);
}




update(x0,y0,x1,y1)
int x0,y0,x1,y1;
{	
	int i;
	for(i=0; i<100000; i++) {
		drawLine(x0,y0,x1,y1);
	}
}


getBit(x,y)
int x,y;
{
	int bit, byt, abit;

	abit = (y*WIDTH + x);
	byt = abit>>3;
	bit = abit % 8;
	return(frameBuffer[byt] & masks[bit]);
}


render(frame)
int frame;
{
	int x,y;

	/* draw the frame buffer on the screen 
	   if the corresponding bit is set, draw an asterisk, else a space */

	for (y=0; y<HEIGHT; y++)
		for (x=0; x<WIDTH; x++)
			if (getBit(x,y))
				drawPoint(x,y);
			else
				clearPoint(x,y);

printf("frame %d\n", frame);
//sleep(1);
}



drawLine(x0,y0,x1,y1)
int x0,y0,x1,y1;
{
	/*
	y=mx+b
	b = y0, m = slope (y0-y1)/(x0-x1)

	y = ((y0-y1)/(x0-x1))*j+y0
	y/8
	*/
	
	int j=0;
	for(j=x0; j<=x1; j++){
		int tot, bt, by;
		
		tot = ((y1-y0)/(x1-x0))*j + y0;
		
		by = (j+tot*WIDTH)>>3;
		bt = j%8;
		frameBuffer[by] = frameBuffer[by] | masks[bt];
		//printf("%d, %d\n", j, tot);
	}
}




main(argc,argv,envp)
int argc;
char **argv, **envp;
{
	int x0, x1, y0, y1;
	struct timeval t1,t2;
	gettimeofday(&t1,0);
	
	x0 = atoi(argv[1]);
	y0 = atoi(argv[2]);
	x1 = atoi(argv[3]);
	y1 = atoi(argv[4]);

	int i, frame=0;
	for (i=0; i<8; i++)
		masks[i] = 1<<i;

	frameBuffer = (unsigned char *) malloc((WIDTH*HEIGHT)>>3);
	clearfb();

	while (1) {
		update(x0,y0,x1,y1);
		render(frame);
		frame++;
		//sleep(1);
		gettimeofday(&t2,0);
		if(frame == 100){
			
			unsigned int time1 = 1000000*t1.tv_sec+t1.tv_usec;
			unsigned int time2 = 1000000*t2.tv_sec+t2.tv_usec;
			unsigned int fps = 100/((time2-time1)/1000000);
			printf("time1: %u, time2: %u, elapsed: %u\n", time1, time2, time2-time1);
			//printf("frame rate: %u frames per sec\n", (unsigned int)(300/(time2 - time1)/1000000) );
			printf("fps: %u \n", fps);
			exit(0);
		}
	}
}
