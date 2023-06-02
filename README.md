# Specto

A C++ library which creates a data representation of a spectogram given a wav file.

You could draw this data using a UI lib. This lib just handles all the annoying
algorithmic stuff (i.e. STFT, Frequency to Mel scale, Spectral Power to dBFS, etc.)

# Setup

1. Install [cmake](https://cmake.org/install/)
```
$ brew install cmake
```

2. Install [conan](https://docs.conan.io/2/installation.html)
```
$ pip install conan
```

# Building and Running

Build (libs end up in ./build/out/lib)
```
$ ./buildit.sh
```
Run example
```
$ ./runexample.sh
```
Run unit tests
```
$ ./testit.sh
```

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

# In the works
Will upload to conancenter so that you can include this lib in your own conanfile.txt