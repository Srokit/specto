/**
 * File: inc/specto/mel_filter_bands.h
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Spectogram public interface and factory function.
 * Version: 0.1
 * Date: 2023-06-02
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#pragma once

#include <memory>

namespace specto {

struct MelFilterBandsOptions {
  int numMelBands;
  // This shoud be half or half + 1 of the FFT size that one
  //   would use this MelFilterBands with.
  int numFrequencyBins;
  int sampleRate;
};

/**
 * Data representation of a group of Mel filter bands.
 */
class IMelFilterBands {
 public:
  virtual int getNumMelBands() = 0;
  virtual int getFrequencyBins() = 0;
  virtual float getWeightAtMelBandAndFreqBin(int, int) = 0;
  virtual ~IMelFilterBands() = default;
};

typedef std::unique_ptr<IMelFilterBands> MelFilterBands;

inline static constexpr MelFilterBandsOptions defaultMelFilterBandsOptions() {
  return {
    .numMelBands = 256,
    // This assumes an FFT size of 16384.
    .numFrequencyBins = 8192,
    .sampleRate = 44100,
  };
}

MelFilterBands createMelFilterBands(
    MelFilterBandsOptions = defaultMelFilterBandsOptions());

}  // namespace specto
