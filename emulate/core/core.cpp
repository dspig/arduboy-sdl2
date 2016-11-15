#include "core.h"

/* Drawing */

void ArduboyCore::paintScreen(const unsigned char *image)
{
	SDL_Renderer * renderer = arduboy_renderer();
		
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
		
	for (int i = 0; i < (HEIGHT * WIDTH)/8; i++) {
		for (int j = 0; j < 8; j++) {
			bool white = (image[i] & (1 << j)) > 0;
			
			if (white) {
				SDL_SetRenderDrawColor(renderer, 240, 240, 120, 255);		
			} else {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			}
		
	
			SDL_Rect pixel = {
			    (i % WIDTH) * (1 << PIXEL_SIZE),
			    ((i / WIDTH) * 8 + j) * (1 << PIXEL_SIZE),
				1 << PIXEL_SIZE,
				1 << PIXEL_SIZE
			};

			SDL_RenderFillRect(renderer, &pixel);
		}
	}
	
	SDL_RenderPresent(renderer);

}

// paint from a memory buffer, this should be FAST as it's likely what
// will be used by any buffer based subclass
void ArduboyCore::paintScreen(unsigned char image[])
{
	paintScreen((const unsigned char *)image);
}

void ArduboyCore::blank()
{
	SDL_Renderer * renderer = arduboy_renderer();
		
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

/* Buttons */

uint8_t ArduboyCore::getInput()
{
  return buttonsState();
}


uint8_t ArduboyCore::buttonsState()
{
  uint8_t buttons;
  
//   // using ports here is ~100 bytes smaller than digitalRead()
// #ifdef AB_DEVKIT
//   // down, left, up
//   buttons = ((~PINB) & B01110000);
//   // right button
//   buttons = buttons | (((~PINC) & B01000000) >> 4);
//   // A and B
//   buttons = buttons | (((~PINF) & B11000000) >> 6);
// #elif defined(ARDUBOY_10)
//   // down, up, left right
//   buttons = ((~PINF) & B11110000);
//   // A (left)
//   buttons = buttons | (((~PINE) & B01000000) >> 3);
//   // B (right)
//   buttons = buttons | (((~PINB) & B00010000) >> 2);
// #endif

// TODO: fix
  buttons = 0;  
  return buttons;
}
