# ball_sorting_puzzle_solver
This is a solver for the mobile game, ball sorting puzzle

Requirements:
Cpp compiler, Matlab with Image Processing Toolbox

To compile:
run this command in the folder
clang++ Source.cpp puzzle.cpp -o solver.exe -std=c++17

Afterwards, add the cropped screenshot of the desired level, similar to bsp_level_4.jpg or bsp_level_29.jpg, into the screesnhots folder.
Run the ./solver.exe, and give the name of the screenshot in the folder when prompted. after a few seconds, the solution of the puzzle will be printed out,
It takes a few seconds to run, because the program calls matlab to open and analyze the image.
