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
Run spectogram example
```
$ ./run_spectogram_example.sh
```
Run unit tests
```
$ ./testit.sh
```

# API Example

To load a file:
```
spec->loadFile(filePath)
```

To load float vector data:
```
vector<float> samples = makeData();
spec->loadDataWithSampleRate(samples, sampleRate)
```

After this data has been loaded...

To get the num windows and num frequency (mel) bins generated:
```
int nw = spec->getNumWindows();
int nf = spec->getNumFrequencyBins();
```

To get the loudness factor for a freq bin, window bin combo:
Note this factor will be a float between 0 and 1
```
float val = spec->getLoudnessFactorAtWindowAndFreqBin(windowI, freqI);
```

Example of how to use with your own UI API:
```
specto::Spectogram spec = specto::makeSpectogram();
spec->loadFile(YOUR_filePath);
for (int i = 0; i < spec->getNumWindows(); ++i) {
  for (int j = 0; j < spec->getNumFrequencyBins(); ++j) {
    int x = YOUR_calcX(spec->getNumWindows());
    int y = YOUR_calcY(spec->getNumFrequencyBins());
    int loudFac = spec->getLoudnessFactorAtWindowAndFreqBin(i, j);
    YOUR_drawSpectoSquareUsingLoudnessFac(x, y, loudFac);
  }
}
```

# In the works
Will upload to conancenter so that you can include this lib in your own conanfile.txt
