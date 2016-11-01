function [ imout ] = logtrans( imorig, c )
%LOGTRANS The function makes a log transformation of the image
%   The image is log transformed with constant c.

    imorig = im2double(imorig);
    imout = im2uint8(c .* log(1+imorig));

end