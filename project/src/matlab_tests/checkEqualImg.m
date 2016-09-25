function [ boolean ] = checkEqualImg( im1, im2 )
%CHECKEQUALIMG The function checks if both images are equal or not.
%   im1, im2 are two routes to two files where you can discover images or
%           two matrixes with pixeles.

    if ischar(im1)
        im1 = imread(im1);
    end
    if ischar(im2)
        im2 = imread(im2);
    end
    
    boolean = (sum(sum(im1==im2)) == numel(im1));

end