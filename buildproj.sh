#!/bin/bash

cmake -S . -B build -D CMAKE_BUILD_TYPE=Release && \
cmake --build build && \
cd build && \
chmod +x installscriptrunner && \
./installscriptrunner && \
cd .. \
