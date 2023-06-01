
#include "spectogram.h"

#include <vector>

/*
 * Draws the window using SDL API based on spectogram data
 */
class SDLDrawer {
 public:
  void drawFromSpectogram(const Spectogram&);
 private:
  static constexpr int WINDOW_WIDTH = 1024;
  static constexpr int WINDOW_HEIGHT = 512;

  std::vector<std::vector<double>> data;
};