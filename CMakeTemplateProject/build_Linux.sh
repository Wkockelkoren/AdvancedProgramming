#!/bin/bash
cd ext
git clone --recurse-submodules https://github.com/wjakob/nanogui
cd ..
mkdir build
cd build
cmake ..
make -j$(nproc)
cd ..
