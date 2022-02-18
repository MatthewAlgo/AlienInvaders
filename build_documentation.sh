#!/bin/bash

cmake -S documentation -B build/doc
cmake --build build/doc --target GenerateDocs
# view the docs
firefox build/doc/doxygen/html/index.html