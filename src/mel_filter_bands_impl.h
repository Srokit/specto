/**
 * File: src/mel_filter_bands_impl.h
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Mel filter bands impl interface
 * Version: 0.1
 * Date: 2023-06-08
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#pragma once

#include "specto/mel_filter_bands.h"

#include "matrix.h"

namespace specto_impl {

class MelFilterBandsImpl : public specto::IMelFilterBands {
 public:
  explicit MelFilterBandsImpl(const specto::MelFilterBandsOptions&);
  int getNumMelBands() override;
  int getNumFrequencyBins() override;
  float getWeightAtFreqBinAndMelBand(int, int) override;
 private:
  void calculateMelFilterWeights_();

  Matrix melFilterWeights_;

  int numMelBands_;
  int numFrequencyBins_;
  int sampleRate_;
};

}  // namespace specto_impl
