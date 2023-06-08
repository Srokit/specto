/**
 * File: inc/specto/spectogram.h
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Spectogram public interface and factory function.
 * Version: 0.1
 * Date: 2023-06-02
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

namespace specto {

struct SpectogramOptions {
  /**
   * The window length for each FFT.
   * Preferably a power of 2 so that padding is not required for fft.
   * 
   * This will also dictate the maximum frequency that can be represented.
   * MaxFreq = floor(windowLen / 2) + 1
   */
  int windowLen;

  /**
   * The number of that the STFT should hop in between windows.
   * If this is less than windowLen, then the windows will overlap.
   */
  int windowHop;

  /**
   * The number of mel bins to include in the spectogram.
   */
  int numMelBins;
};

// TODO(Stan): Add comments to this interface.
class ISpectogram {
 public:
  virtual bool loadFile(const std::string&) = 0;
  virtual void loadDataWithSampleRate(const std::vector<float>&, int) = 0;
  virtual int getNumWindows() = 0;
  virtual int getNumFrequencyBins() = 0;
  virtual float getLoudnessFactorAtWindowAndFreqBin(int, int) = 0;
  virtual ~ISpectogram() = default;
};

inline static constexpr SpectogramOptions defaultSpectogramOptions() {
  return {
    .windowLen = 16384,  // 2^14 (power of 2 preferred)
    .windowHop = 4096,  // 1/4th of above
    .numMelBins = 256,
  };
}

typedef std::unique_ptr<ISpectogram> Spectogram;

// Recommended to use this factory function instead of the constructor
// so that the Spectogram is destructed automatically.
Spectogram makeSpectogram(SpectogramOptions = defaultSpectogramOptions());

}  // namespace specto
