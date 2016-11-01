function [ imout ] = gammacorrection( imorig, c, gamma )
%GAMMACORRECTION The function makes gamma correction of the image
%   The image is made a gama correction with power introduced

    imorig = im2double(imorig);
    imout = im2uint8(c .* imorig.^gamma);
    
end