function [ imout ] = normalize( imorig, newmin, newmax )
%NORMALIZE The function normalizes the image
%   The image is normalized between the two values introduced.

    mn = min(imorig(:));
    mx = max(imorig(:));

    imout = (imorig-mn) * uint8((newmax-newmin)/(mx-mn)) + newmin;

end
