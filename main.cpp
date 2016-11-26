#include <iostream>
#include <SDL2/SDL.h>
#include "emulate/cleanup.h"

#include SKETCH

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

// Clip outside of screen drawing
bool clip = true;

uint8_t sdl_buttons;

static SDL_Rect rect = {0, 0, 640, 480};

// Draws an alpha-blended pixel, used by draw_line
void arduboy_pixel( short x, short y, bool white ) {
  // SDL_Rect pixel = {
  //   (Sint16)((rect.w / 2) - ((64 - x) << ARDUBOY_ENHANCE)),
  //   (Sint16)((rect.h / 3) - ((32 - y) << ARDUBOY_ENHANCE)),
  //   1 << ARDUBOY_ENHANCE,
  //   1 << ARDUBOY_ENHANCE
  // };
  //
  // uint32_t color;
  //
  // if(x < 0 || x > 127 || y < 0 || y > 63) {
  //   color = clip ? 0xFFFFFF : (white ? 0xF0F0F0 : 0xC0C0C0);
  // } else {
  //   color = white ? 0xFFFFFF : 0x000000;
  // }
  //
  // SDL_FillRect(screen, &pixel, color);
	SDL_Renderer * renderer = arduboy_renderer();	
	
	fprintf(stdout, "pixel: %d x %d = %d\n", x, y, white);
	
	if (white) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);		
	} else {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}
		
	
	// SDL_Rect pixel = {
	//     (Sint16)((rect.w / 2) - ((64 - x) << PIXEL_SIZE)),
	//     (Sint16)((rect.h / 3) - ((32 - y) << PIXEL_SIZE)),
	// 	1 << PIXEL_SIZE,
	// 	1 << PIXEL_SIZE
	// };

	SDL_Rect pixel = {
	    x * (1 << PIXEL_SIZE),
	    y * (1 << PIXEL_SIZE),
		1 << PIXEL_SIZE,
		1 << PIXEL_SIZE
	};

	fprintf(stdout, "pixel (x %d, y %d, w %d, h %d)\n", pixel.x, pixel.y, pixel.w, pixel.h);
	
	SDL_RenderFillRect(renderer, &pixel);
}

SDL_Renderer *renderer = NULL;

SDL_Renderer * arduboy_renderer() {
	return renderer;
}

int main(int, char**){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0){
		logSDLError(std::cout, "SDL_Init");
        return 1;
    }
	
	SDL_Window *win = SDL_CreateWindow(
		"Arduboy Emulator",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (win == nullptr){
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}

	renderer = SDL_CreateRenderer(
		win,
		-1,
		SDL_RENDERER_ACCELERATED);// | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == nullptr){
		logSDLError(std::cout, "CreateRenderer");
		cleanup(win);
		SDL_Quit();
		return 1;
	}

	bool reset = true;
	bool quit = false;
	SDL_Event e;
	while (!quit) {
		while (SDL_PollEvent(&e)){

			if (reset) {
				setup();
				reset = false;
			}

			//If user closes the window
			if (e.type == SDL_QUIT){
				quit = true;
			}
			
	        if(e.type == SDL_KEYDOWN) {
	          if(e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q) { quit = true; }
	          else if(e.key.keysym.sym == SDLK_c) clip = !clip;
	          // Arduboy keypad emulation
	          else if(e.key.keysym.sym == SDLK_UP   ) sdl_buttons |= UP_BUTTON;  // Up
	          else if(e.key.keysym.sym == SDLK_RIGHT) sdl_buttons |= RIGHT_BUTTON;  // Right
	          else if(e.key.keysym.sym == SDLK_LEFT ) sdl_buttons |= LEFT_BUTTON;  // Left
	          else if(e.key.keysym.sym == SDLK_DOWN ) sdl_buttons |= DOWN_BUTTON;  // Down
	          else if(e.key.keysym.sym == SDLK_z    ) sdl_buttons |= A_BUTTON;  // A
	          else if(e.key.keysym.sym == SDLK_x    ) sdl_buttons |= B_BUTTON;  // B
	        } else if(e.type == SDL_KEYUP) {
	          // Arduboy keypad emulation
	          if(e.key.keysym.sym == SDLK_UP   ) sdl_buttons &= ~UP_BUTTON;  // Up
	          else if(e.key.keysym.sym == SDLK_RIGHT) sdl_buttons &= ~RIGHT_BUTTON;  // Right
	          else if(e.key.keysym.sym == SDLK_LEFT ) sdl_buttons &= ~LEFT_BUTTON;  // Left
	          else if(e.key.keysym.sym == SDLK_DOWN ) sdl_buttons &= ~DOWN_BUTTON;  // Down
	          else if(e.key.keysym.sym == SDLK_z    ) sdl_buttons &= ~A_BUTTON;  // A
	          else if(e.key.keysym.sym == SDLK_x    ) sdl_buttons &= ~B_BUTTON;  // B
	          else if(e.key.keysym.sym == SDLK_r    ) reset = true;  // B
	        }			
		}	
			
		loop();
	}
	
	cleanup(renderer, win);
	SDL_Quit();
	return 0;
}

// ** HELPER STUFF BELOW ********************************************
#ifdef __WIN32__
PCHAR* CommandLineToArgvA( PCHAR CmdLine, int* _argc ) {
  PCHAR *argv;
  PCHAR _argv;
  ULONG len;
  CHAR   a;
  ULONG i, j;
  ULONG argc = 0;

  BOOLEAN in_QM = FALSE;
  BOOLEAN in_TEXT = FALSE;
  BOOLEAN in_SPACE = TRUE;

  len = strlen( CmdLine );
  i = ( ( len + 2 ) / 2 ) * sizeof( PVOID ) + sizeof( PVOID );

  argv = ( PCHAR* )malloc( i + ( len + 2 ) * sizeof( CHAR ) );
  _argv = ( PCHAR )( ( ( PUCHAR ) argv ) + i );
  argv[ 0 ] = _argv;

  i = 0;
  j = 0;

  while( (a = CmdLine[i]) ) {
    if( in_QM ) {
      if( a == '\"' ) {
        in_QM = FALSE;
      } else {
        _argv[ j ] = a;
        j++;
      }
    } else {
      switch( a ) {
        case '\"':
          in_QM = TRUE;
          in_TEXT = TRUE;
          if( in_SPACE ) {
              argv[ argc ] = _argv + j;
              argc++;
          }
          in_SPACE = FALSE;
          break;
        case ' ':
        case '\t':
        case '\n':
        case '\r':
          if( in_TEXT ) {
            _argv[ j ] = '\0';
            j++;
          }
          in_TEXT = FALSE;
          in_SPACE = TRUE;
          break;
        default:
          in_TEXT = TRUE;
          if( in_SPACE ) {
              argv[ argc ] = _argv + j;
              argc++;
          }
          _argv[ j ] = a;
          j++;
          in_SPACE = FALSE;
          break;
      }
    }
    i++;
  }
  _argv[ j ] = '\0';
  argv[ argc ] = NULL;

  *_argc = argc;
  return( argv );
}

int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
  LPSTR *argv;
  int argc;
  int ret;
  LPSTR lpCmdLine2;
  
  lpCmdLine2 = (typeof lpCmdLine2)malloc(strlen((char*)lpCmdLine) + 5);
  strcpy( lpCmdLine2, "me " );
  strcat( lpCmdLine2, lpCmdLine );

  argv = CommandLineToArgvA( lpCmdLine2, &argc );
  if ( argv == NULL ) {
    printf( "Console [error]: Command line parsing failed\n" );
    return( 5 );
  }
  
  ret = main( argc, argv );

  free( lpCmdLine2 );
  free( argv );
  return( ret );
}

#endif
