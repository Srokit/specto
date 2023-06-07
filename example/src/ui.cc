/**
 * File: example/src/ui.cc
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: UI example implementation.
 * Version: 0.1
 * Date: 2023-06-02
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#include "ui.h"

#include <iostream>

#include "SDL2/SDL.h"

namespace example_ui {

void drawSpectogram(const specto::Spectogram& spectogram) {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window* window;
  SDL_Renderer* renderer;
  const int kWindowWidth = 1500;
  const int kWindowHeight = 800;
  int createRes = SDL_CreateWindowAndRenderer(
      kWindowWidth, kWindowHeight, 0, &window, &renderer);
  SDL_Delay(1000);

  if (createRes < 0) {
    std::cerr << "Could not create window or renderer: " <<  SDL_GetError() << std::endl;
    return;
  }

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  int numWindows = spectogram->getNumWindows();
  int numFreqBins = spectogram->getNumFrequencyBins();

  int xDelta = 640 / numWindows;
  int yDelta = 480 / numFreqBins;

  int winStep = 1;

  // Need to jump over some windows to fit in the ui window
  if (numWindows > kWindowHeight) {
    std::cout << "Num Windows > kWindowHeight, Skipping some windows" << std::endl;
    xDelta = 1;
    winStep = numWindows / kWindowHeight;
  }

  // Print UI Stats for debug
  std::cout << "Window Width: " << kWindowWidth << std::endl;
  std::cout << "Window Height: " << kWindowHeight << std::endl;
  std::cout << "Num Windows (from spec): " << numWindows << std::endl;
  std::cout << "Num Freq Bins (from spec): " << numFreqBins << std::endl;
  std::cout << "xDelta: " << xDelta << std::endl;
  std::cout << "yDelta: " << yDelta << std::endl;

  for (int wI = 0; wI < numWindows; wI++) {
    int w = wI * winStep;
    for (int f = 0; f < numFreqBins; ++f) {
      float loudnessFactor = spectogram->getLoudnessFactorAtWindowAndFreqBin(w, f);
      SDL_SetRenderDrawColor(renderer, 255 * loudnessFactor, 0, 0, 255);
      int x = static_cast<int>(static_cast<float>(xDelta) * static_cast<float>(w));
      int y = static_cast<int>(static_cast<float>(yDelta) * static_cast<float>(f));
      SDL_Rect rect = {x, y, xDelta, yDelta};
      int r = static_cast<int>(static_cast<float>(255) * loudnessFactor);
      SDL_SetRenderDrawColor(renderer, r, r, r, 255);
      SDL_RenderFillRect(renderer, &rect);
    }
  }

  std::cout << "Showing window..." << std::endl;

  SDL_RenderPresent(renderer);

  SDL_Event e;
  while (true) {
      if (SDL_PollEvent(&e))
          if (e.type == SDL_QUIT)
              break;
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

}  // namespace example_ui