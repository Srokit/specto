/**
 * File: example/src/time_bar.cc
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Time bar to show time axis along ui implementation.
 * Version: 0.1
 * Date: 2023-06-02
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#include "time_bar.h"

#include <sstream>

namespace example_ui {

TimeBar::TimeBar(const TimeBarOptions& options,
                 const std::string& fontPath) {
  barWidth_ = options.barWidth;
  barHeight_ = options.barHeight;
  totalDurationSec_ = options.totalDurationSec;
  numTicks_ = options.numTicks;
  calcTickPositions_();
  loadFont_(fontPath);
}

TimeBar::~TimeBar() {
  TTF_CloseFont(font_);
}

void TimeBar::draw(SDL_Renderer* renderer) const {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_Rect rect = {0, 0, barWidth_, barHeight_};
  SDL_RenderFillRect(renderer, &rect);

  int labelHeight = static_cast<int>(barHeight_ * kLabelHeightFraction);
  int tickHeight = static_cast<int>(barHeight_ * kTickHeightFraction);

  // Draw labels.
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  // Less than or equal for the last tick.
  for (int i = 0; i <= numTicks_; ++i) {
    float valSec = tickValsSec_[i];
    SDL_Texture* labelTexture = makeLabelTexture_(valSec, renderer);
    int leftX = tickPositions_[i] - kLabelWidth / 2;
    SDL_Rect dstRect = {leftX, 0, kLabelWidth, labelHeight};
    SDL_RenderCopy(renderer, labelTexture, nullptr, &dstRect);
    SDL_DestroyTexture(labelTexture);
  }

  // Draw ticks
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  // Less than or equal for the last tick.
  for (int i = 0; i <= numTicks_; ++i) {
    SDL_RenderDrawLine(renderer, tickPositions_[i], labelHeight,
                       tickPositions_[i], labelHeight + tickHeight);
  }
}

void TimeBar::calcTickPositions_() {
  float tickIntervalSec = totalDurationSec_ / numTicks_;
  int tickPosInterval = barWidth_ / numTicks_;
  // Less than or equal for the last tick.
  for (int i = 0; i <= numTicks_; ++i) {
    tickValsSec_.push_back(tickIntervalSec * i);
    tickPositions_.push_back(tickPosInterval * i);
  }
}

void TimeBar::loadFont_(const std::string& fontPath) {
  // TODO(Stan): Check if this fails
  font_ = TTF_OpenFont(fontPath.c_str(), 12);
}

SDL_Texture* TimeBar::makeLabelTexture_(float valSec,
                                        SDL_Renderer* renderer) const {
  std::ostringstream ss;
  ss.precision(3);
  ss << std::fixed << valSec << "s";
  SDL_Color color = {255, 255, 255, 255};
  SDL_Surface* surface = TTF_RenderText_Solid(font_, ss.str().c_str(), color);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  return texture;
}

}  // namespace example_ui
