/*---------------------------------------------------------------------------------

	$Id: main.cpp,v 1.13 2008-12-02 20:21:20 dovoto Exp $

	bouncing dvd-esque demo -- damien
	:)


---------------------------------------------------------------------------------*/
#include <nds.h>
#include <gl2d.h>
#include <nds/arm9/sound.h>
#include <stdio.h>

int random_colour(){
	return RGB15(rand()%255, rand()%255,rand()%255);
}

void random_cols(int (arr)[4]){
	for (int i=0;i<4;i++)
		arr[i] = random_colour();
}

float x, y, xspeed, yspeed;
int width, height;
int cols[4];

void setup_values(){
	// ds screen resolution is 256x192
	x = rand() % 255;// start at random location
	y = rand() % 190;// start at random location
	width = 50;
	height = 20;
	xspeed = 0.5f;// speed of movement
	yspeed = 0.5f;// speed of movement
	random_cols(cols);

}
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	videoSetMode(MODE_5_3D);
	consoleDemoInit();
	glScreen2D();
	setup_values();

	bool gradient = true;

	while(1) {
		glBegin2D();		
		scanKeys();

		int keys = keysDown();
		if (keys & KEY_A) {
			x = rand() % 255;
			y = rand() % 190;
			random_cols(cols);
		}
		if (keys & KEY_L){ // decrease speed
			xspeed += (xspeed < 0) ? 0.01f : -0.01f;
			yspeed += (yspeed < 0) ? 0.01f : -0.01f;
		}
		if (keys & KEY_R){ // increase speed
			xspeed += (xspeed < 0) ? -0.01f : 0.01f;
			yspeed += (yspeed < 0) ? -0.01f : 0.01f;
		}
		if (keys & KEY_LEFT){
			if (width > 1) width -= 1; // reduce width when LEFT pressed
		}
		if (keys & KEY_RIGHT){ // increase width when RIGHT pressed
			width += 1;
		}
		if (keys & KEY_UP){	// decrease height when UP pressed
			if (height > 1) height -= 1;
		}
		if (keys & KEY_DOWN){ // increase height when DOWN pressed
			height += 1;
		}
		if (keys & KEY_SELECT){ // reset values
			setup_values();
		}
		if (keys & KEY_START){
			gradient = !gradient;
		}
		if (keys & KEY_X)
			swiSoftReset();
		int x2 = (x + width);
		int y2 = (y + height);

		if (gradient)
			glBoxFilledGradient(x,y,x2,y2, cols[0],cols[1],cols[2],cols[3]); // draw our box wit gradient
		else
			glBoxFilled(x,y,x2,y2,cols[0]); // draw our box solid fill


		glLine(x, y, x2, y2, cols[1]);
		glLine(x2, y2, x, y, cols[1]);

		if (x2 >= 256 || x <= 0) {
			xspeed *= -1; 
			random_cols(cols);}
			// invert our speed value and set a random colour for the box
		if (y2 >= 192 || y <= 0) {
			yspeed *= -1; 
			random_cols(cols);}

		x += xspeed;
		y += yspeed;
		
		printf("\x1b[3;0Hbouncing dvd test - damien :)");
		printf("\x1b[5;0Hpress A to randomise");
		printf("\x1b[6;0HL + R to adjust speed");
		printf("\x1b[7;0HLeft + Right to adjust width");
		printf("\x1b[8;0HUp + Down to adjust height");
		printf("\x1b[9;0HSELECT to reset values");
		printf("\x1b[10;0HSTART to switch colour mode");


		printf("\x1b[12;0H col0: %d        ", cols[0]);
		printf("\x1b[13;0H col1: %d        ", cols[1]);
		printf("\x1b[14;0H col2: %d        ", cols[2]);
		printf("\x1b[15;0H col3: %d        ", cols[3]);

		printf("\x1b[17;0Hw: %d h: %d        ", width, height);
		printf("\x1b[18;0Hxspeed: %f        ", xspeed);
		printf("\x1b[19;0Hyspeed: %f        ", yspeed);
		printf("\x1b[20;0Hx: %f y: %f        ", x, y);

		glEnd2D();
		glFlush(0);
		swiWaitForVBlank();
	}

	return 0;
}
