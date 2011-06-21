#!/bin/bash

cd /var/tmp
mkdir programming
cd programming
mkdir PasskeyChanger
cd PasskeyChanger

mkdir build_unix_release
cd build_unix_release
cmake -D CMAKE_BUILD_TYPE=Release ~/programming/PasskeyChanger
cd ..

mkdir build_unix_debug
cd build_unix_debug
cmake -D CMAKE_BUILD_TYPE=Debug ~/programming/PasskeyChanger
cd ..

