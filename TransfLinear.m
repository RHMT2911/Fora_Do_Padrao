img = imread('lena.jpg');

red = img(:,:,1);
green = img(:,:,2);
blue = img(:,:,3);

red = red*0.299;
green = green*0.587;
blue = blue*0.114;

gray = red+green+blue;

figure(1)
imshow(img);
figure(2)
imshow(gray);
