#!/bin/bash
# Script to test all the functions

mkdir -p img/cga/out
echo "Starting all tests..."
echo "Executing average filter";
./bin/avgfilter img/cga/lena_grey-noisy.pgm img/cga/out/lenaBN-avgfilter.pgm 3
echo "All tests done!"
