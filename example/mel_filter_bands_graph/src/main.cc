/**
 * File: example/mel_filter_bands_graph/src/main.cc
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Main file for the mel filter bands graph example.
 * Version: 0.1
 * Date: 2023-06-08
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#include "ui.h"

#include "specto/mel_filter_bands.h"

int main() {
  auto mfb = specto::makeMelFilterBands({
    .numMelBands = 30,
    .numFrequencyBins = 4096,
    .sampleRate = 44100,
  });
  example_ui::drawUi(mfb);
  return 0;
}
