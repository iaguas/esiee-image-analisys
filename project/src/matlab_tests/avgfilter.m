%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%  Average filter image application function                     %%
%%  Project of Image analysis and processing - ESIEE              %%
%%  Iñigo Aguas Ardaiz                                            %%
%%  22th November 2016                                            %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function imout = avgfilter(im, fsize)
    [rs, cs] = size(im);
    a = fix(fsize/2);
    
    im = im2double(im);
    imout = zeros(size(im));
    for i=1:rs
        for j=1:cs
            aux = im(max(1,i-a):min(i+a,rs),max(1,j-a):min(j+a,cs));
            imout(i,j) = mean(aux(:));
        end
    end
end