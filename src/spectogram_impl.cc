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

namespace specto_impl {

// TODO(Stan): Make this configurable
SpectogramImpl::SpectogramImpl(const specto::SpectogramOptions& opts)
    : windowLen_(opts.windowLen), windowHop_(opts.windowHop),
      numMelBins_(opts.numMelBins) {}

bool SpectogramImpl::loadFile(const std::string& filePath) {
  loadAudioFile_(filePath);
  if (didNotLoadFile_) return false;

  calcSpectorgram_();

  return true;
}

int SpectogramImpl::getNumWindows() {
  // TODO(Stan): Implement
  return 0;
}

int SpectogramImpl::getNumFrequencyBins() {
  // TODO(Stan): Implement
  return 0;
}

double SpectogramImpl::getDBFSAtWindowIndexAndFrequencyBinIndex(
    int windowIndex, int frequencyBinIndex) {
  // TODO(Stan): Implement
  return 0;
}

void SpectogramImpl::calcSpectorgram_() {
  int numWindows = calcNumWindows_();
  for (int winI = 0; winI < numWindows; winI++) {
    // Get windowed audio data
    std::vector<float> windowedAudioData(
        audioData_.begin() + winI * windowHop_,
        audioData_.begin() + winI * windowHop_ + windowLen_);
    hanningInPlace(&windowedAudioData);
    std::vector<float> fftData = fft(windowedAudioData);
    stft_.addRow(fftData);
  }
}

int SpectogramImpl::calcNumWindows_() {
  // Note this will not allocate a window on end if it is not full
  return (audioData_.size() - windowLen_) / windowHop_ + 1;
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

}  // namespace specto_impl

namespace specto {

Spectogram makeSpectogram(SpectogramOptions options) {
  return std::make_unique<specto_impl::SpectogramImpl>(options);
}

}  // namespace specto
