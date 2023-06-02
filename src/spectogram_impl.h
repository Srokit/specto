/**
 * File: src/spectogram_impl.h
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Spectogram implementation interface.
 * Version: 0.1
 * Date: 2023-06-02
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#pragma once

#include <string>

#include "specto/spectogram.h"

namespace specto_impl {

class SpectogramImpl : public specto::ISpectogram {
 public:
  explicit SpectogramImpl(const specto::SpectogramOptions&);
  bool loadFile(const std::string&) override;
  int getNumWindows() override;
  int getNumFrequencyBins() override;
  double getDBFSAtWindowIndexAndFrequencyBinIndex(int, int) override;
};

}  // namespace specto_impl
