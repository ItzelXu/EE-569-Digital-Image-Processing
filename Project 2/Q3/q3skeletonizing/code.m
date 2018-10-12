BW = imread('jigsaw_2.png');
% imshow(BW);
BW3 = bwmorph(BW,'skel',25);
figure
imshow(BW3)