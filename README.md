# Specto

A C++ library which creates a data representation of a spectogram given a wav file.

You could draw this data using a UI lib. This lib just handles all the annoying
algorithmic stuff (i.e. STFT, Frequency to Mel scale, Spectral Power to dBFS, etc.)

# API Example

```
specto::Spectogram spec = specto::makeSpectogram();
for (int i = 0; i < spec->getNumWindows(); ++i) {
  for (int j = 0; j < spec->getNumFrequencyBins(); ++j) {
    int x = YOUR_calcX(spec->getNumWindows());
    int y = YOUR_calcY(spec->getNumFrequencyBins());
    int dBFSVal = spec->getDBFSAtWindowIndexAndFrequencyBinIndex(i, j);
    YOUR_drawSpectoSquareUsingDBFS(x, y, dBFSVal);
  }
}
```
