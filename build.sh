#!/bin/bash

rm -rf build
mkdir build && cd build
# cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang
make -j4    
# strace ./build/Debug/vulkan-sample
