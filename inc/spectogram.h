
#pragma once

#include <string>
#include <vector>

#include "AudioFile.h"

class Spectogram {
 public:
  Spectogram(float hopDurationSec, int numFreqBins);
  void loadFile(const std::string&);
  int getNumHops() const { return data_.size(); }
  int getNumFreqBins() const { return data_[0].size(); }
  float getDataPointAtHopAndFreqBin(int hop, int freqBin) const {
    return data_[hop][freqBin];
  }
 private:
  std::vector<std::vector<float>> data_;
  float hopDurationSec_;
  int numFreqBins_;
  void normalize_();
  void printInfo_();
};
