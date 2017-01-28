#!/bin/bash
# Script to test all the functions

mkdir -p img/tp1/out
echo "Starting all tests..."
echo "Executing difference image function";
./bin/diffimage img/tp1/blobs.pgm img/tp1/blobsEqualize.pgm img/tp1/out/outDiffimage.pgm
echo "Executing threshold image function";
./bin/threshold img/tp1/blobs.pgm 10 40 img/tp1/out/outThreshold.pgm img/tp1/blobsThreshold-10-40.pgm
echo "Executing normalize image function";
./bin/normalize img/tp1/blobs.pgm 0 255 img/tp1/out/outNormalize.pgm img/tp1/blobsNormalize.pgm
echo "Executing equalize image function";
./bin/equalize img/tp1/blobs.pgm img/tp1/out/outEqualize.pgm img/tp1/blobsEqualize.pgm
echo "Executing gamma correction image function";
./bin/gammac img/tp1/blobs.pgm img/tp1/out/outGamma0.5.pgm img/tp1/blobsGamma0.5.pgm
echo "Executing log transformation image function";
./bin/log img/tp1/blobs.pgm 1 img/tp1/out/outLog.pgm
echo "Executing power transformation image function";
./bin/power img/tp1/blobs.pgm 1 2 img/tp1/out/outPower.pgm img/tp1/blobsPower2.pgm
echo "Executing average filter function";
./bin/weightavg img/tp1/blobs.pgm 17 img/tp1/out/outAvgFilter.pgm
echo "Executing laplacian filter function";
./bin/laplacian img/tp1/blobs.pgm img/tp1/out/outLaplacianFilter.pgm
echo "All tests done!"
