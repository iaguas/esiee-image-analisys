#!/bin/bash
# Script to test all the functions

mkdir -p img/cga/out
echo "Starting all tests..."
echo "Executing average filter";
./bin/avgfilter img/cga/lena_grey_noisy.pgm img/cga/out/lenaBN-avgfilter.pgm 3
./bin/avgfilter_color img/cga/lena_std_noisy.ppm img/cga/out/lenaColor-avgfilter.ppm 3
./bin/pixelwisefilter img/cga/lena_grey_noisy.pgm img/cga/out/lenaBN-avgfilter.pgm 10
echo "All tests done!"
