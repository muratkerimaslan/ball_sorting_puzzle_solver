function output = bucket_identifier(num_buckets,centers,radii,img)

%%
average_radius = mean(radii,'all'); %
num_balls = size(centers,1);

% for i=1:1:num_balls
%     x_cor = uint32(centers(i,1));
%     y_cor = uint32(centers(i,2));
%     if x_cor == 0 
%         % do nothing
%     else
%         curr__bucket = zeros(1,4);
%         num_below = 0
%         num_above = 0
%         curr_color = img(y_cor,x_cor);
%     end
% end
output = zeros(num_buckets,4);
% find top left bucket,
% count the 3 balls under it,
% remove all 4 indices from corners by marking them as 9999
my_centers = centers;
for i = 1:1:num_buckets
    %curr_bucket = zeros(1,4); % cur_bucket = output(i);
    [lowest_x, lowest_y,center_ind] = find_smallest_x_y(my_centers); 
    my_centers(center_ind,1) = intmax;
    my_centers(center_ind,2) = intmax;
    if lowest_x ~= intmax
        output(i,1) = img(lowest_y,lowest_x);
        x_level_low = lowest_x - 10;
        x_level_high = lowest_x + 10;
        for j = 1:1:num_balls  % count the 3 balls below to form this bucket
            x_cor = uint32(my_centers(j,1));
            y_cor = uint32(my_centers(j,2));
            % if close to 2 radii then 2nd
            % if close to 4 radii then 3rd, if close to 6 radii then 4th
            if x_level_low <= x_cor && x_cor <= x_level_high
                difference  = round(  (y_cor - lowest_y)  /  (average_radius*2)  );
                ball_index = difference + 1;
                if ball_index <= 4
                    %output(i,ball_index) = j;
                    output(i,ball_index) = img(y_cor,x_cor);
                    my_centers(j,1) = intmax;
                    my_centers(j,2) = intmax;
                end
            end
        end
    end
end
end