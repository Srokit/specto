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
   * The number of windows to run fft over.
   * This will affect window size. It will be calculated as
   * windowSize = fileDuration * sampleRate / (numWindows * (1 - windowOverlapFrac))
   */
  int numWindows;

  /**
   * The fraction of the window that will overlap with the preceeding window.
   * Should be between 0 and 1.
   */
  double windowOverlapFrac;

  /**
   * The number of frequency bins to include in the spectogram.
   * Note that these bins will be spaced lograrithmically
   * according to the Mel scale.
   */
  int numFrequencyBins;

  /**
   * The minimum frequency to include in the spectogram.
   */
  int minFrequency;

  /**
   * The maximum frequency to include in the spectogram.
   */
  int maxFrequency;
};

// TODO(Stan): Add comments to this interface.
class ISpectogram {
 public:
  virtual bool loadFile(const std::string&) = 0;
  virtual int getNumWindows() = 0;
  virtual int getNumFrequencyBins() = 0;
  virtual double getDBFSAtWindowIndexAndFrequencyBinIndex(int, int) = 0;
};

inline static constexpr SpectogramOptions defaultSpectogramOptions() {
  return {
    .numWindows = 1000,
    .windowOverlapFrac = 0.5,
    .numFrequencyBins = 100,
    .minFrequency = 0,
    .maxFrequency = 8000,
  };
}

typedef std::unique_ptr<ISpectogram> Spectogram;

// Recommended to use this factory function instead of the constructor
// so that the Spectogram is destructed automatically.
Spectogram makeSpectogram(SpectogramOptions = defaultSpectogramOptions());

}  // namespace specto
