/**
 * File: example/src/main.cc
 * Author: Stan Rokita <stan@stansa.dev>
 * Desc: Main file for example program using specto.
 * Version: 0.1
 * Date: 2023-06-02
 * 
 * Copyright: Copyright (c) 2023 Stan Rokita
 */

#include <iostream>

#include "AudioFile.h"

#include "specto/spectogram.h"

#include "ui.h"

void printSpecStats(const specto::Spectogram& spectogram) {
  std::cout << "Num Windows: " << spectogram->getNumWindows() << std::endl;
  std::cout << "Num Frequency Bins: " << spectogram->getNumFrequencyBins()
            << std::endl;
}

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cout << "Usage: " << argv[0] <<
        " <filename> <ttf_font_filename>" << std::endl;
    return 1;
  }

  std::string fontPath(argv[2]);
  std::cout << "Using font: " << fontPath << std::endl;

  std::string filename(argv[1]);
  std::cout << "Loading file: " << filename << std::endl;

  // Load audiofile of our own to get duration in S
  AudioFile<float> audioFile;
  audioFile.load(filename);
  float durationInS = static_cast<float>(audioFile.getLengthInSeconds());

  specto::Spectogram spectogram = specto::makeSpectogram();
  spectogram->loadFile(filename);
  printSpecStats(spectogram);
  example_ui::drawSpectogram(spectogram, durationInS, fontPath);
  return 0;
}
