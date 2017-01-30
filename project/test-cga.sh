#!/bin/bash
# Script to test all the functions

mkdir -p img/cga/out
echo "Starting all tests..."
echo "Executing average filter"
./bin/avgfilter img/cga/lena_grey_noisy.pgm img/cga/out/lenaGray-avgfilter-3.pgm 3
./bin/avgfilter_color img/cga/lena_std_noisy.ppm img/cga/out/lenaColor-avgfilter-3.ppm 3
echo "Executing pixelwise filter"
./bin/pixelwisefilter img/cga/lena_grey_noisy.pgm img/cga/out/lenaGray-pixelwisefilter-10.pgm 10
./bin/pixelwisefilter img/cga/lena_grey_noisy.pgm img/cga/out/lenaGray-pixelwisefilter-40.pgm 40
./bin/pixelwisefilter_color img/cga/lena_std_noisy.ppm img/cga/out/lenaColor-pixelwisefilter-10.ppm 10
./bin/pixelwisefilter_color img/cga/lena_std_noisy.ppm img/cga/out/lenaColor-pixelwisefilter-40.ppm 40
echo "Executing windowswise filter"
#./bin/windowwisefilter img/cga/lena_grey_noisy.pgm img/cga/out/lenaGray-windowwisefilter-10.pgm 10
#./bin/windowswisefilter_color img/cga/lena_std_noisy.ppm img/cga/out/lenaColor-windowswisefilter-10.ppm 10
echo "All tests done!"