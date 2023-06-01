
#include "sdl_drawer.h"

#include <SDL2/SDL.h>

void SDLDrawer::drawFromSpectogram(const Spectogram& spectogram) {
  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
  SDL_Texture* texture = NULL;
  SDL_Event event;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  SDL_PixelFormat* format = SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888);

  // Calculate pixel move deltas
  int deltaX = WINDOW_WIDTH / spectogram.getNumHops();
  int deltaY = WINDOW_HEIGHT / spectogram.getNumFreqBins();

  int leftOverPixelsX = WINDOW_WIDTH % spectogram.getNumHops();
  int leftOverPixelsY = WINDOW_HEIGHT % spectogram.getNumFreqBins();

  texture = SDL_CreateTexture(renderer,
                              format->format,
                              SDL_TEXTUREACCESS_STATIC,
                              WINDOW_WIDTH,
                              WINDOW_HEIGHT);
  int pitch = WINDOW_WIDTH;
  int pitchBytes = pitch * sizeof(Uint32);

  // Draw pixels
  std::unique_ptr<Uint32> pixels(new Uint32[WINDOW_WIDTH * WINDOW_HEIGHT]);
  for (int hopI = 0; hopI < spectogram.getNumHops(); hopI++) {
    int startX = hopI * deltaX;
    int endX = startX + deltaX;
    // The binI is in reverse so that the lower frequencies are at the bottom
    for (int binI = spectogram.getNumFreqBins() - 1; binI >= 0; binI--) {
      int yI = spectogram.getNumFreqBins() - 1 - binI;
      int startY = yI * deltaY;
      int endY = startY + deltaY;
      float dataPoint = spectogram.getDataPointAtHopAndFreqBin(hopI, binI);
      Uint8 red = static_cast<Uint8>(dataPoint * 255);
      Uint32 pixCol = SDL_MapRGBA(format, red, 0, 0, 255);
      for (int pixY = startY; pixY < endY; pixY++) {
        for (int pixX = startX; pixX < endX; pixX++) {
          int pixI = pixY * pitch + pixX;
          pixels.get()[pixI] = pixCol;
        }
      }
    }
  }
  int leftOverYStart = WINDOW_HEIGHT - leftOverPixelsY;
  int leftOverXStart = WINDOW_WIDTH - leftOverPixelsX;
  Uint32 black = SDL_MapRGBA(format, 0, 0, 0, 255);
  for (int pixY = leftOverYStart; pixY < WINDOW_HEIGHT; pixY++) {
    for (int pixX = 0; pixX < WINDOW_WIDTH; pixX++) {
      int pixI = pixY * pitch + pixX;
      pixels.get()[pixI] = black;
    }
  }
  for (int pixX = leftOverXStart; pixX < WINDOW_WIDTH; pixX++) {
    for (int pixY = 0; pixY < WINDOW_HEIGHT; pixY++) {
      int pixI = pixY * pitch + pixX;
      pixels.get()[pixI] = black;
    }
  }
  if (SDL_UpdateTexture(texture, NULL,
                        reinterpret_cast<void*>(pixels.get()),
                        pitchBytes) < 0) {
    printf("SDL_UpdateTexture failed: %s\n", SDL_GetError());
    return;
  }

  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);

  while (1) {
    SDL_WaitEvent(&event);
    if (event.type == SDL_QUIT)
      break;
  }

  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_FreeFormat(format);
  SDL_Quit();
}
