
#include <iostream>

#include "specto.h"

constexpr float kHopDurationSec = 10;
constexpr int kNumFreqBins = 128;

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }
  std::string filename(argv[1]);
  std::cout << "Loading file: " << filename << std::endl;
  drawSpectogramOfFileWithHopDurationAndNumFreqBins(filename, kHopDurationSec, kNumFreqBins);

  return 0;
}
