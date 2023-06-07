/**
 * File: src/spectogram_impl.h
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Spectogram implementation interface.
 * Version: 0.1
 * Date: 2023-06-02
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#pragma once

#include <string>
#include <vector>

#include "AudioFile.h"

#include "matrix.h"
#include "specto/spectogram.h"

namespace specto_impl {

class SpectogramImpl : public specto::ISpectogram {
 public:
  explicit SpectogramImpl(const specto::SpectogramOptions&);
  bool loadFile(const std::string&) override;
  int getNumWindows() override;
  int getNumFrequencyBins() override;
  double getDBFSAtWindowIndexAndFrequencyBinIndex(int, int) override;
 private:
  void calcSpectorgram_();
  int calcValues_();
  void loadAudioFile_(const std::string&);
  void calcMelFilterBanks_();
  float fftBinToHz_(int bin) { return samplingResolution_ * bin;}

  int windowLen_;
  int windowHop_;
  int numMelBins_;
  int numWindows_;
  // Also equal to nyquist / samplingResolution
  int numFftBins_;
  float samplingResolution_;

  bool didNotLoadFile_;

  // Mono channel audio data.
  // Will be filled with the first channel audio data from file.
  std::vector<float> audioData_;

  int sampleRate_;

  Matrix stft_;
  Matrix melFilterBanks_;
  Matrix spectogram_;
};

}  // namespace specto_impl
