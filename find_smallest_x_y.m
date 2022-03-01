function [x,y,c_index] = find_smallest_x_y(centers)
c_index = 1;
x  = intmax;
y = intmax;
y_level_low = intmax;
% first find the y level;
% then find smallest x in that y level;
for i=1:1:size(centers,1) 
    curr_y = centers(i,2);
    if curr_y < y_level_low
        y_level_low = curr_y;
    end
end
y_level_high = y_level_low + 15;
for i=1:1:size(centers,1)
    curr_x = centers(i,1);
    curr_y = centers(i,2);
    if y_level_low <= curr_y && curr_y <= y_level_high
        if curr_x < x
            x = curr_x;
            y = curr_y;
            c_index = i;
        end
    end
end
x = uint32(x);
y = uint32(y);
end