/**
 * File: example/src/time_bar.h
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Time bar to show time axis along ui interface.
 * Version: 0.1
 * Date: 2023-06-02
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#pragma once

#include <string>
#include <vector>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

namespace example_ui {

struct TimeBarOptions {
  int barWidth;
  int barHeight;
  float totalDurationSec;
  int numTicks;
};

class TimeBar {
 public:
  explicit TimeBar(const TimeBarOptions&, const std::string& fontPath);
  ~TimeBar();
  void draw(SDL_Renderer*) const;
 private:
  void calcTickPositions_();
  void loadFont_(const std::string& fontPath);
  SDL_Texture* makeLabelTexture_(float valSec,
                                 SDL_Renderer* renderer) const;

  int barWidth_;
  int barHeight_;
  float totalDurationSec_;
  int numTicks_;

  TTF_Font* font_;

  static constexpr float kLabelHeightFraction = 0.7f;
  // The rest of the height is used for the ticks.
  static constexpr float kTickHeightFraction = 1.f - kLabelHeightFraction;

  static constexpr int kLabelWidth = 80;

  std::vector<float> tickValsSec_;
  std::vector<int> tickPositions_;
};

}  // namespace example_ui
