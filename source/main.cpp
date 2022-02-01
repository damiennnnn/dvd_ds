/*---------------------------------------------------------------------------------

	$Id: main.cpp,v 1.13 2008-12-02 20:21:20 dovoto Exp $

	bouncing dvd-esque demo -- damien
	:)


---------------------------------------------------------------------------------*/

#include "box.h"
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	videoSetMode(MODE_5_3D);
	consoleDemoInit();
	glScreen2D();

	bool gradient = true;
	Box _box;

	while(1) {
		glBegin2D();		
		scanKeys();

		int keys = keysDown();
		if (keys & KEY_A) {
			_box.Randomise();
		}
		if (keys & KEY_L){ // decrease speed
			_box.AdjustSpeed(0);
		}
		if (keys & KEY_R){ // increase speed
			_box.AdjustSpeed(1);
		}
		if (keys & KEY_LEFT){
			_box.DecreaseSize(1,0);
		}
		if (keys & KEY_RIGHT){ // increase width when RIGHT pressed
			_box.IncreaseSize(1,0);
		}
		if (keys & KEY_UP){	// decrease height when UP pressed
			_box.DecreaseSize(0,1);
		}
		if (keys & KEY_DOWN){ // increase height when DOWN pressed
			_box.IncreaseSize(0,1);
		}
		if (keys & KEY_SELECT){ // reset values
		}
		if (keys & KEY_START){
			gradient = !gradient;
		}

		_box.Update();
		_box.Draw(gradient);

		printf("\x1b[3;0Hbouncing dvd test - damien :)");
		printf("\x1b[5;0Hpress A to randomise");
		printf("\x1b[6;0HL + R to adjust speed");
		printf("\x1b[7;0HLeft + Right to adjust width");
		printf("\x1b[8;0HUp + Down to adjust height");
		printf("\x1b[9;0HSELECT to reset values");
		printf("\x1b[10;0HSTART to switch colour mode");
		_box.PrintDebugInfo();

		glEnd2D();
		glFlush(0);
		swiWaitForVBlank();
	}

	return 0;
}
