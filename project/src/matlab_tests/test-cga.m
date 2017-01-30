%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%  Tests of CGA filter project                                   %%
%%  Project of Image analysis and processing - ESIEE              %%
%%  Iñigo Aguas Ardaiz                                            %%
%%  22th November 2016                                            %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

lenaBN_noisy = imread('../../img/cga/lena_grey-noisy.pgm');

imout=avgfilter(lenaBN_noisy,21);