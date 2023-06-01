
#include "specto.h"

#include "spectogram.h"
#include "sdl_drawer.h"

void drawSpectogramOfFileWithHopDurationAndNumFreqBins(
    const std::string& filename, float hopDurationSec, int numFreqBins) {
  Spectogram spectogram(hopDurationSec, numFreqBins);
  spectogram.loadFile(filename);
  SDLDrawer drawer;
  drawer.drawFromSpectogram(spectogram);
}