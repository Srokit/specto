/**
 * File: example/mel_filter_bands_graph/src/ui.cc
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: UI implementation for MFB example.
 * Version: 0.1
 * Date: 2023-06-08
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#include "ui.h"

#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

// TODO(Stan): Investigate issue where the mel bands run off
//             the screen on the right side before reaching bottom of screen

namespace example_ui {

void drawUi(const specto::MelFilterBands& mfb) {
  // TODO(Stan): Refactor the code shared here with spectogram example into
  //             shared code
  SDL_Init(SDL_INIT_EVERYTHING);
  if (TTF_Init() < 0) {
    std::cerr << "Could not init TTF: " << TTF_GetError() << std::endl;
    return;
  }
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

  int numFrequencyBins = mfb->getNumFrequencyBins();
  int numMelBands = mfb->getNumMelBands();

  float xDelta = static_cast<float>(kWindowWidth) / numFrequencyBins;
  float yDelta = static_cast<float>(kWindowHeight) / numMelBands;

  int winStep = 1;

  // Need to jump over some windows to fit in the ui window
  if (numFrequencyBins > kWindowWidth) {
    std::cout << "Num Windows > kWindowWidth, Skipping some windows" << std::endl;
    xDelta = 1;
    winStep = numFrequencyBins / kWindowWidth;
  }

  // Print UI Stats for debug
  std::cout << "Window Width: " << kWindowWidth << std::endl;
  std::cout << "Window Height: " << kWindowHeight << std::endl;
  std::cout << "Num Freq bins (from mfb): " << numFrequencyBins << std::endl;
  std::cout << "Num Mel Bands (from mfb): " << numMelBands << std::endl;
  std::cout << "xDelta: " << xDelta << std::endl;
  std::cout << "yDelta: " << yDelta << std::endl;
  std::cout << "winStep: " << winStep << std::endl;
  std::cout << "MaxYWillBe: " << yDelta * numMelBands << std::endl;

  for (int wI = 0; wI < numFrequencyBins; wI++) {
    int w = wI * winStep;
    for (int f = 0; f < numMelBands; ++f) {
      float loudnessFactor = mfb->getWeightAtFreqBinAndMelBand(w, f);
      int x = static_cast<int>(xDelta * static_cast<float>(w));
      int y = static_cast<int>(yDelta * static_cast<float>(f));
      int xDeltaInt = static_cast<int>(xDelta);
      int yDeltaInt = static_cast<int>(yDelta);
      SDL_Rect rect = {x, y, xDeltaInt, yDeltaInt};
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
  TTF_Quit();
}

}  // namespace example_ui
