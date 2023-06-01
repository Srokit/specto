
#include "spectogram.h"

#include <cmath>

#include "AudioFile.h"

#include "fft.h"

#include <iostream>

Spectogram::Spectogram(float hopDurationSec, int numFreqBins)
    : hopDurationSec_(hopDurationSec),
      numFreqBins_(numFreqBins) {}

void Spectogram::loadFile(const std::string& filename) {
  AudioFile<float> audioFile;
  audioFile.load(filename);

  // Calc hop duration in samples
  int hopDurationSamples = static_cast<int>(
      audioFile.getSampleRate() * hopDurationSec_);

  // Calc num hops
  int numHops = static_cast<int>(
      std::ceil(audioFile.getNumSamplesPerChannel() / hopDurationSamples));
  data_.reserve(numHops);

  // FFT audiofile data
  for (int i = 0;
       i < audioFile.getNumSamplesPerChannel();
       i += hopDurationSamples) {
    // Do not go over the end of the file
    int numSamples = std::min(hopDurationSamples,
                              audioFile.getNumSamplesPerChannel() - i);
    std::vector<float> fftData =
        fft(&(audioFile.samples[0][i]), numSamples);
    // Not concerned with frequencies above the nyquist frequency
    fftData.resize(numSamples / 2);
    numSamples /= 2;
    // Average into bins
    std::vector<float> freqBins(numFreqBins_, 0);
    std::vector<int> freqBinCounts(numFreqBins_, 0);
    for (int j = 0; j < numSamples; j++) {
      int bin = static_cast<int>(
          static_cast<float>(j) * numFreqBins_ / numSamples);
      freqBins[bin] += fftData[j];
      freqBinCounts[bin]++;
    }
    for (int j = 0; j < numFreqBins_; j++) {
      freqBins[j] /= freqBinCounts[j];
    }
    data_.push_back(freqBins);
  }
  normalize_();
  printInfo_();
}

void Spectogram::normalize_() {
  // Find max
  float max = 0;
  for (auto& v : data_) {
    for (float v2 : v) {
      v2 = std::log10(v2) * 20;
      max = std::max(max, v2);
    }
  }
  // Normalize
  for (auto& v : data_) {
    for (auto& v2 : v) {
      v2 /= max;
    }
  }
}

void Spectogram::printInfo_() {
  std::cout << "Spectogram:" << std::endl;
  std:: cout << "Num hops: " << getNumHops() << std::endl;
  std::cout << "Num freq bins: " << getNumFreqBins() << std::endl;
}
