/**
 * File: src/mel_filter_bands_impl.cc
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Mel filter bands impl implementation.
 * Version: 0.1
 * Date: 2023-06-08
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#include "mel_filter_bands_impl.h"

#include <memory>

#include "mel_filter_banks.h"

namespace specto_impl {

MelFilterBandsImpl::MelFilterBandsImpl(
    const specto::MelFilterBandsOptions& opts) {
  numMelBands_ = opts.numMelBands;
  numFrequencyBins_ = opts.numFrequencyBins;
  sampleRate_ = opts.sampleRate;
  calculateMelFilterWeights_();
}
int MelFilterBandsImpl::getNumMelBands() {
  return numMelBands_;
}
int MelFilterBandsImpl::getNumFrequencyBins() {
  return numFrequencyBins_;
}
float MelFilterBandsImpl::getWeightAtFreqBinAndMelBand(
    int freqBin, int melBand) {
  // Must reverse the order since row num is mel band num
  // and col num is freq bin num
  return melFilterWeights_.getVal(melBand, freqBin);
}

void MelFilterBandsImpl::calculateMelFilterWeights_() {
  auto melFilterBanks = makeMelFilterBanks({
    .numBanks = numMelBands_,
    .numFreqBins = numFrequencyBins_,
    .samplingResolution = static_cast<float>(sampleRate_) / numFrequencyBins_,
  });
  melFilterWeights_.addMultipleRows(melFilterBanks);
}

}  // namespace specto_impl

namespace specto {

MelFilterBands makeMelFilterBands(MelFilterBandsOptions opts) {
  return std::make_unique<specto_impl::MelFilterBandsImpl>(opts);
}

}  // namespace specto
