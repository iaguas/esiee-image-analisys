imorig = imread('../../img/blobs.pgm');
imout = imread('../../img/out/outLog.pgm');

imout2 = logtrans(imorig,1);

checkEqualImg(imout2,imout)

imshow(imout2);