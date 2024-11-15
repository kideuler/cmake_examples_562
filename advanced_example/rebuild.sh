#!/bin/bash

# This script is used to rebuild the project and run tests

# Delete build and install directories
rm -rf build
rm -rf install

# Recreate them
mkdir build
mkdir install

# export locations for openmp and install directories
export OMP=/opt/homebrew/opt/libomp # substitute this with location of opemp libraries
export INSTALL_DIR=$PWD/install

# building cmake
cd build
cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR -DCMAKE_PREFIX_PATH=$OMP ..
make -j
make install
make test
cd ..

# appending python files to pythonpath
export PYTHONPATH=$INSTALL_DIR/lib:$PYTHONPATH
python3 tests/MatrixTest.py