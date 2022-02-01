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
	soundEnable();
	int vol = 0;

	int sound_id = soundPlayNoise(7000, vol, 64);

	std::vector<Box> boxes;
	Box _box;
	boxes.push_back(_box);
	while(1) {
		glBegin2D();		
		scanKeys();

		int keys = keysDown();
		if (keys & KEY_A) {
			boxes[0].Randomise();
		}
		if (keys & KEY_L){ // decrease speed
			boxes[0].AdjustSpeed(0);
		}
		if (keys & KEY_R){ // increase speed
			boxes[0].AdjustSpeed(1);
		}
		if (keys & KEY_LEFT){
			boxes[0].DecreaseSize(1,0);
		}
		if (keys & KEY_RIGHT){ // increase width when RIGHT pressed
			boxes[0].IncreaseSize(1,0);
		}
		if (keys & KEY_UP){	// decrease height when UP pressed
			boxes[0].DecreaseSize(0,1);
		}
		if (keys & KEY_DOWN){ // increase height when DOWN pressed
			boxes[0].IncreaseSize(0,1);
		}
		if (keys & KEY_Y){ // reset values
			Box _newBox;
			boxes.push_back(_newBox);
		}
		if (keys & KEY_START){
			gradient = !gradient;
		}

		for (int i =0; i < boxes.size(); i++)
		{
			if (boxes[i].Update())
			{
				vol = 64;
			}
			boxes[i].Draw(gradient);
		}
		printf("\x1b[2;0Hbouncing dvd test - damien :)");
		printf("\x1b[4;0Hpress A to randomise");
		printf("\x1b[5;0HL + R to adjust speed");
		printf("\x1b[6;0HLeft + Right to adjust width");
		printf("\x1b[7;0HUp + Down to adjust height");
		printf("\x1b[8;0HSELECT to reset values");
		printf("\x1b[9;0HSTART to switch colour mode");
		printf("\x1b[10;0HY to create new box");

		printf("\x1b[12;0H volume: %d        ", vol);
		boxes[0].PrintDebugInfo();

		soundSetVolume(sound_id, vol);
		vol -= 4;
		if (vol < 0) vol = 0;
		glEnd2D();
		glFlush(0);
		swiWaitForVBlank();
	}

	return 0;
}
