%clc;clear;

filepath = "/Users/murataslan/Desktop/uni/solo_proje/ball_sorting_puzzle/screenshots/";
abs_filename = filepath + filenamearg;
my_ss = imread(abs_filename);
[centers, radii,metric] = imfindcircles(rgb2gray(my_ss) , [50 75]);
my_ss_bw = rgb2gray(my_ss);
my_ss_bw2 = my_ss_bw;

%%
% imshow(my_ss_bw2);
% 
% viscircles(centers, radii ,'EdgeColor','r');
%%
BW = edge(my_ss_bw,'canny');
[H,T,R] = hough(BW);
P  = houghpeaks(H,80,'threshold',ceil(0.1*max(H(:))));
lines = houghlines(BW,T,R,P,'FillGap',10,'MinLength',100);

num_buckets = size(lines,2)/4;
num_balls = size(centers,1);


%%
buckets_and_colors = bucket_identifier(num_buckets,centers,radii,my_ss_bw);
%%

%%
for i=1:1:num_balls
    x_cor = uint32(centers(i,1));
    y_cor = uint32(centers(i,2));
    my_ss_bw2(y_cor,x_cor) = 255;
    curr_color = my_ss_bw(y_cor,x_cor);
end
%%

%%
[top_left_ball_x, top_left_ball_y] = find_smallest_x_y(centers);
%disp(my_ss_bw(top_left_ball_y,top_left_ball_x));
%%


% figure, imshow(my_ss_bw2), hold on
% max_len = 0;
% for k = 1:length(lines)
%    xy = [lines(k).point1; lines(k).point2];
%    plot(xy(:,1),xy(:,2),'LineWidth',2,'Color','green');
% 
%    % Plot beginnings and ends of lines
%    plot(xy(1,1),xy(1,2),'x','LineWidth',2,'Color','yellow');
%    plot(xy(2,1),xy(2,2),'x','LineWidth',2,'Color','red');
% 
%    % Determine the endpoints of the longest line segment
%    len = norm(lines(k).point1 - lines(k).point2);
%    if ( len > max_len)
%       max_len = len;
%       xy_long = xy;
%    end
% end
%%
for i=1:1:size(buckets_and_colors,1)
    for j=1:1:size(buckets_and_colors,2)
        disp(buckets_and_colors(i,j))
    end
end
