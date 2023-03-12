# Build 
```
brew install SDL2
mkdir build && cd build
cmake ..
make
```

# Test and run
```
make test
./src/CC3K
```

# Notes

If you add a new file, make sure to run cmake .. so it picks up the new source files