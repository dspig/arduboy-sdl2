#include "Arduboy.h"

// make an instance of arduboy used for many functions
Arduboy arduboy;


// This function runs once in your game.
// use it for anything that needs to be set only once in your game.
void setup() {
	Serial.begin(115200);
	Serial.println("Arduboy Demo!");
	
	// initiate arduboy instance
	arduboy.begin();
	// arduboy.beginNoLogo();

	// here we set the framerate to 15, we do not need to run at
	// default 60 and it saves us battery life
	arduboy.setFrameRate(15);
}

int x = 20, xFactor = 2;
int y = 20, yFactor = 3;
int radius = 10;

int count = 0;

// our main game loop, this runs once every cycle/frame.
// this is where our game logic goes.
void loop() {

	// pause render until it's time for the next frame
	if (!(arduboy.nextFrame()))
		return;

	// first we clear our screen to black
	arduboy.clear();

	x += xFactor;
	y += yFactor;

	if (x > (128 - radius) || x < radius) {
		xFactor = -xFactor;
	}

	if (y > (64 - radius) || y < radius) {
		yFactor = -yFactor;
	}

	arduboy.drawCircle(x, y, radius, 1);

	// then we finaly we tell the arduboy to display what we just wrote to the display
	arduboy.display();
}
