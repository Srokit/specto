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
#include "mel_convert.h"

namespace specto_impl {

// TODO(Stan): Make this configurable
SpectogramImpl::SpectogramImpl(const specto::SpectogramOptions&) {}

bool SpectogramImpl::loadFile(const std::string& filePath) {
  // TODO(Stan): Load file into AudioFile

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

void SpectogramImpl::calcSpectorgramFromAudioFile_(
    const AudioFile<float>& audioFile) {
  int numSamples = audioFile.getNumSamplesPerChannel();
  int numChannels = audioFile.getNumChannels();
  int sampleRate = audioFile.getSampleRate();

}
  

}  // namespace specto_impl

namespace specto {

Spectogram makeSpectogram(SpectogramOptions options) {
  return std::make_unique<specto_impl::SpectogramImpl>(options);
}

}  // namespace specto
