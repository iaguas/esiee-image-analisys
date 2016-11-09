#!/bin/bash
# Script to test all the functions

mkdir -p img/out
echo "Starting all tests..."
echo "Executing difference image function";
./bin/diffimage img/blobs.pgm img/blobsEqualize.pgm img/out/outDiffimage.pgm
echo "Executing threshold image function";
./bin/threshold img/blobs.pgm 10 40 img/out/outThreshold.pgm img/blobsThreshold-10-40.pgm
echo "Executing normalize image function";
./bin/normalize img/blobs.pgm 0 255 img/out/outNormalize.pgm img/blobsNormalize.pgm
echo "Executing equalize image function";
./bin/equalize img/blobs.pgm img/out/outEqualize.pgm img/blobsEqualize.pgm
echo "Executing gamma correction image function";
./bin/gammac img/blobs.pgm img/out/outGamma0.5.pgm img/blobsGamma0.5.pgm
echo "Executing log transformation image function";
./bin/log img/blobs.pgm 1 img/out/outLog.pgm
echo "Executing power transformation image function";
./bin/power img/blobs.pgm 1 2 img/out/outPower.pgm img/blobsPower2.pgm
echo "Executing average filter function";
./bin/weightavg img/blobs.pgm 3 img/out/outAvgFilter.pgm
echo "Executing laplacian filter function";
./bin/laplacian img/blobs.pgm img/out/outLaplacianFilter.pgm
echo "All tests done!"
