#ifndef __ARDUBOY_EMULATE_H__
#define __ARDUBOY_EMULATE_H__

#ifdef __WIN32__
#include <Windows.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <inttypes.h>

//
#include <SDL2/SDL.h>

#define PIXEL_SIZE 2
#define SCREEN_WIDTH (128 * (1 << PIXEL_SIZE))
#define SCREEN_HEIGHT (64 * (1 << PIXEL_SIZE))


#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2


#define REFS0 0
#define REFS1 0
#define MUX0 0
#define MUX1 0
#define MUX2 0
#define MUX3 0
#define MUX4 0
#define MUX5 0

// extern unsigned char ADMUX;
// extern volatile unsigned char ADC;
// extern volatile unsigned char ADSC;
// extern volatile unsigned char ADCSRA;
// extern volatile unsigned int ADCSRB;

/* EMULATION SHEITE */
#define PROGMEM
#define B00000000 0
#define B00000001 1
#define B00000010 2
#define B00000100 4
#define B00001000 8
#define B00010000 16
#define B00100000 32
#define B01000000 64
#define B10000000 128
#define B11110000 0xF0

#define SLEEP_MODE_IDLE 0

#define _BV(N) (1 << (N))

#define LEFT_BUTTON _BV(5)
#define RIGHT_BUTTON _BV(6)
#define UP_BUTTON _BV(7)
#define DOWN_BUTTON _BV(4)
#define A_BUTTON _BV(3)
#define B_BUTTON _BV(2)


#define _MMIO_BYTE(mem_addr) (*(volatile uint8_t *)(mem_addr))
#define _MMIO_WORD(mem_addr) (*(volatile uint16_t *)(mem_addr))
#define _MMIO_DWORD(mem_addr) (*(volatile uint32_t *)(mem_addr))

#define _SFR_MEM_ADDR(sfr) (sfr)
#define _SFR_ADDR(sfr) _SFR_MEM_ADDR(sfr)
#define _SFR_BYTE(sfr) _MMIO_BYTE(_SFR_ADDR(sfr))

#define F(str) (str)

#define 	bit_is_set(sfr, bit)   (_SFR_BYTE(sfr) & _BV(bit))

#ifndef __WIN32__
typedef bool boolean;
typedef uint8_t byte;
typedef uint16_t word;
#endif

/* == WMATH ====================== */
	
void randomSeed(unsigned long seed);
long random(long howbig);
//long random(long howsmall, long howbig);
long map(long x, long in_min, long in_max, long out_min, long out_max);

//unsigned int makeWord(unsigned int w);
unsigned int makeWord(unsigned char h, unsigned char l);

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __WIN32__
int max(int a, int b);
int min(int a, int b);
int abs(int value);
#else
typedef uint16_t word;
#endif

#ifdef __cplusplus
}
#endif

/* =============================== */

/* Arduino */

void power_adc_disable();
void power_adc_enable();

void delay(unsigned int ms);
uint32_t millis();
uint32_t micros();
// void arduboy_spi(byte c8);
// void set_sleep_mode(byte mode);
// void sleep_mode();
// void drawSprite(int x, int y, const byte *sheet, byte w, byte h, byte index, byte color);
//
// /*
// static struct {
//   void(*drawSprite)(int, int, const byte *, byte, byte, byte, byte);
// } arduboy = {&drawSprite};
// */
//
static inline byte pgm_read_byte(const byte *wat) {
  return *wat;
}

static inline word pgm_read_word(const word *wat) {
  return *wat;
}

void arduboy_pixel( short x, short y, bool white );

SDL_Renderer * arduboy_renderer();

uint8_t buttonsState();

#define WIDTH 128
#define HEIGHT 64

#define INVERT 2 //< lit/unlit pixel
#define WHITE 1 //< lit pixel
#define BLACK 0 //< unlit pixel

/* END OF SAID SHEITE */
#endif//__ARDUBOY_EMULATE_H__