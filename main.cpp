#include <SDL/SDL.h>
#include <iostream>
#include <string>

const char GAME_TITLE[] = "Ludum Dare 34 Game";

//Attributes of the screen
const Uint32 SCREEN_WIDTH = 720;
const Uint32 SCREEN_HEIGHT = 480;
const Uint32 SCREEN_BPP = 32;
const Uint32 MAX_FPS = 40;
const Uint32 min_frametime = 1000 / MAX_FPS;

class World
{
public:
  Uint32 frametime;
  SDL_Rect s_offset;
  
  World();

private:
  Uint32 epoch;
};

World::World(void)
{
  epoch = frametime = SDL_GetTicks();
  s_offset.x = s_offset.y = 0;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
  SDL_Rect offset;

  offset.x = x;
  offset.y = y;

  SDL_BlitSurface(source, NULL, destination, &offset);
}

void draw_screen(World *world, SDL_Surface* screen)
{
}

SDL_Surface* load_image(std::string filename)
{
  //Temp
  SDL_Surface *loadedImage = NULL;

  SDL_Surface *optimizedImage = NULL;

  loadedImage = SDL_LoadBMP(filename.c_str());

  if (loadedImage != NULL)
  {
    optimizedImage = SDL_DisplayFormat(loadedImage);

    SDL_FreeSurface(loadedImage);
  }

  return optimizedImage;
}

int main(int argc, char* args[])
{
  //Init SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
    return -1;
  }

  //Set up screen
  SDL_Surface *screen = NULL;
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_DOUBLEBUF);

  if (screen == NULL)
  {
    std::cout << "Error setting video mode: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_WM_SetCaption(GAME_TITLE, NULL);

  //Load image
  SDL_Surface *background = NULL;
  background = load_image("background.bmp"); // 720x480

  bool running = true;
  SDL_Event event;
  World *world = new World();

  while (running)
  {
    world->frametime = SDL_GetTicks();

    while (SDL_PollEvent(&event) != 0)
    {
      switch (event.type)
      {
      case SDL_KEYDOWN:
	switch (event.key.keysym.sym)
	{
	case SDLK_SPACE:
	  break;
	case SDLK_RALT:
	  break;
	default:
	  ;
	}
	break;
      case SDL_KEYUP:
	if (event.key.keysym.sym == SDLK_ESCAPE ||
	    event.key.keysym.sym == SDLK_q)
	{
	  running = false;
	}
	break;
      default:
	;
      }
    }

    //Apply image
    apply_surface(0, 0, background, screen);

    draw_screen(world, screen);
    
    SDL_Flip(screen);
    
    if (SDL_GetTicks() - world->frametime < min_frametime)
    {
      SDL_Delay(min_frametime - (SDL_GetTicks() - world->frametime));
    }
  }

  SDL_Flip(screen);

  SDL_FreeSurface(background);

  //Quit SDL
  SDL_Quit();

  return EXIT_SUCCESS;
}
