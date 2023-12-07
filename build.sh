#!/bin/bash

mkdir build
cd build

cmake -DRTMIDI_API_JACK=OFF RTMIDI_BUILD_TESTING=OFF ..

mkfifo cling-pipe

make

tail -f cling-pipe | cling -std=c++17
