/**
 * File: src/mel_filter_banks.h
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Mel filter banks creation interface.
 * Version: 0.1
 * Date: 2023-06-05
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#include <vector>

namespace specto_impl {

// Options for creating a mel filter bank matrix.
struct FilterBanksOptions {
  int numBanks;
  int numFreqBins;
  float samplingResolution;
};

/**
 * Returns a positive mel filter bank matrix.
 * All values in the range [0, 1).
 * 
 * Multiply this matrix by the STFT matrix to get the mel spectrogram.
 */
std::vector<std::vector<float>> makeMelFilterBanks(const FilterBanksOptions&);

}  // namespace specto_impl
