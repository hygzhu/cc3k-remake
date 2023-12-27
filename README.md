## Build 
```
brew install SDL2
mkdir build && cd build
cmake ..
make
```

## Cmake with custom dependencies
```
cmake -G "MinGW Makefiles"   -DSDL2_LIBRARY="C:/Users/Laggy/Downloads/SDL2-devel-2.28.5-mingw.tar/SDL2-devel-2.28.5-mingw/SDL2-2.28.5/x86_64-w64-mingw32/bin/SDL2.dll"   -DSDL2_INCLUDE_DIR="C:/Users/Laggy/Downloads/SDL2-devel-2.28.5-mingw.tar/SDL2-devel-2.28.5-mingw/SDL2-2.28.5/x86_64-w64-mingw32/include/SDL2"   -DSDL2_IMAGE_LIBRARY="C:/Users/Laggy/Downloads/SDL2_image-devel-2.8.1-mingw/SDL2_image-2.8.1/x86_64-w64-mingw32/bin/SDL2_image.dll"   -DSDL2_IMAGE_INCLUDE_DIR="C:/Users/Laggy/Downloads/SDL2_image-devel-2.8.1-mingw/SDL2_image-2.8.1/x86_64-w64-mingw32/include/SDL2"   ..
```

## MinGW windows
```
SDL2MAIN_LIBRARY Error:
The error indicates that SDL2MAIN_LIBRARY is not found. In CMake, this variable is used to link SDL2 with main function (WinMain or main). For MinGW, you usually don't need this library. You can try removing the reference to SDL2MAIN_LIBRARY from your CMake configuration.
```

## Test and run (non windows)
```
make test
./src/CC3K
```

## Windows
```
export PATH="/c/Users/Laggy/Downloads/SDL2_image-devel-2.8.1-mingw/SDL2_image-2.8.1/x86_64-w64-mingw32/bin:$PATH"
export PATH="/c/Users/Laggy/Downloads/SDL2-devel-2.28.5-mingw.tar/SDL2-devel-2.28.5-mingw/SDL2-2.28.5/x86_64-w64-mingw32/bin:$PATH"


make test
./build/src/CC3K.exe
```

## Format
```
find . -iname '*.h' -o -iname '*.cpp' | xargs clang-format -i  
```

## Notes

If you add a new file, make sure to run cmake .. so it picks up the new source files

