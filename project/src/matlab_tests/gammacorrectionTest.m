imorig = imread('../../img/blobs.pgm');
imend = imread('../../img/blobsGamma0.5.pgm');
imout = imread('../../img/out/outGamma0.5.pgm');

checkEqualImg(imend, imout)

imout2 = gammacorrection(imorig,1,0.5);

checkEqualImg(imend, imout2)

checkEqualImg(imout2,imout)

imshow(imout2);