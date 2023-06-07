/**
 * File: src/spectogram_impl.cc
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Spectogram implementation.
 * Version: 0.1
 * Date: 2023-06-02
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#include "spectogram_impl.h"

#include <memory>

#include "AudioFile.h"

#include "fft.h"
#include "hanning.h"
#include "mel_convert.h"
#include "mel_filter_banks.h"

namespace specto_impl {

SpectogramImpl::SpectogramImpl(const specto::SpectogramOptions& opts)
    : windowLen_(opts.windowLen), windowHop_(opts.windowHop),
      numMelBins_(opts.numMelBins) {}

bool SpectogramImpl::loadFile(const std::string& filePath) {
  loadAudioFile_(filePath);
  if (didNotLoadFile_) return false;

  calcSpectorgram_();

  return true;
}

void SpectogramImpl::loadDataWithSampleRate(
    const std::vector<float>& data, int sampleRate) {
  audioData_ = data;
  sampleRate_ = sampleRate;
  calcSpectorgram_();
}

int SpectogramImpl::getNumWindows() {
  return numWindows_;
}

int SpectogramImpl::getNumFrequencyBins() {
  return numMelBins_;
}

float SpectogramImpl::getDBFSAtWindowIndexAndFrequencyBinIndex(
    int windowIndex, int frequencyBinIndex) {
  return spectogram_.getVal(frequencyBinIndex, windowIndex);
}

void SpectogramImpl::calcSpectorgram_() {
  calcValues_();
  calcStft_();
  calcMelFilterBanks_();
  multiplyMfbAndStft_();
  normalize_();
  // spectogram_ is now matrix with dims (numMelBins_ x numWindows_)
}

void SpectogramImpl::calcValues_() {
  // Note this will not allocate a window on end if it is not full
  numWindows_ = (audioData_.size() - windowLen_) / windowHop_ + 1;
  numFftBins_ = (windowLen_ % 2 == 0) ? windowLen_ / 2 : windowLen_ / 2 + 1;
  samplingResolution_ = static_cast<float>(sampleRate_) / numFftBins_;
}

void SpectogramImpl::loadAudioFile_(const std::string& filePath) {
  AudioFile<float> audioFile;
  audioFile.load(filePath);
  didNotLoadFile_ = audioFile.getNumSamplesPerChannel() == 0;
  if (didNotLoadFile_) return;
  // Copy float data from first channel to audioData_
  audioData_ = audioFile.samples[0];
  sampleRate_ = static_cast<int>(audioFile.getSampleRate());
}

void SpectogramImpl::calcMelFilterBanks_() {
  // Get the mel filter banks
  melFilterBanks_.addMultipleRows(
    makeMelFilterBanks({
      .numBanks = numMelBins_,
      .numFreqBins = numFftBins_,
      .samplingResolution = samplingResolution_,
    }));
}

void SpectogramImpl::calcStft_() {
  for (int winI = 0; winI < numWindows_; winI++) {
    // Get windowed audio data
    std::vector<float> windowedAudioData(
        audioData_.begin() + winI * windowHop_,
        audioData_.begin() + winI * windowHop_ + windowLen_);
    hanningInPlace(&windowedAudioData);
    std::vector<float> fftData = fft(windowedAudioData);
    stft_.addRow(fftData);
  }
}

void SpectogramImpl::multiplyMfbAndStft_() {
  spectogram_ = melFilterBanks_.multByOther(stft_.transpose());
}

void SpectogramImpl::normalize_() {
  float maxVal = spectogram_.getMax();
  // This can happen if data is odd or configuration is odd
  // Other checks should make this unlikely
  if (maxVal == 0.0f) return;
  spectogram_.multScalarInPlace(1.0f / maxVal);
}

}  // namespace specto_impl

namespace specto {

Spectogram makeSpectogram(SpectogramOptions options) {
  return std::make_unique<specto_impl::SpectogramImpl>(options);
}

}  // namespace specto
