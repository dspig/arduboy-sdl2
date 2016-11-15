#include "emulate.h"

#include <stdio.h>
#include <sys/time.h>

/* == WMATH ====================== */

void randomSeed(unsigned long seed) {
  if(seed != 0) srand(seed);
}

long random(long howbig) {
  if (howbig == 0) return 0;
  return rand() % howbig;
}

long random(long howsmall, long howbig) {
  if (howsmall >= howbig) return howsmall;
  long diff = howbig - howsmall;
  return random(diff) + howsmall;
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

unsigned int makeWord(unsigned int w) { return w; }
unsigned int makeWord(unsigned char h, unsigned char l) { return (h << 8) | l; }

int max(int a, int b) {
	return a > b ? a : b;
}

int min(int a, int b) {
	return a < b ? a : b;
}

int abs(int value) {
	return value < 0 ? -value : value;
}

/* =============================== */

void delay(unsigned int ms) {
  SDL_Delay(ms);
}

uint32_t millis() {
  return SDL_GetTicks();
}

uint32_t micros() {
	struct timeval tp;
    gettimeofday(&tp, NULL);
	return tp.tv_usec;
}

/**/

void set_sleep_mode(byte mode) {
  // TODO?
}

void sleep_mode() {
  // TODO?
}

void drawSprite(int x, int y, const byte *sheet, byte w, byte h, byte index, byte color) {
  short base = (unsigned)index * ((w * h) >> 3);
  for(byte u = 0; u < w; u++) {
    for(byte v = 0; v < h; v++) {
		arduboy_pixel(x + u, y + v, (sheet[base + u + (v >> 3) * w] >> (v & 7)) & 1);
    }
  }
}

SoftwareSerial Serial;


