

#include "puzzle.h"
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
using namespace std;

//5
//ybrb
//byrr
//rbyy
//empty
//empty
vector<vector<int>> transform_path_to_integer(vector<string> path);
vector<vector<int>> transform_path_to_integer2 (vector<string> path);
vector<vector<char>> bucket_reader_from_image (string filename);
bool check_filename_exists(string fname);
int main()
{


	int number_of_tubes;
	cout<<"welcome"<<endl;
	// cout<<"enter the number of tubes in the puzzle: ";
	// cin>>number_of_tubes;

	// puzzle myPuzzle(number_of_tubes);
	string ss_filename;
	cout<<"Enter the name of the uploaded and cropped screenshot inside the screenshots folder"<<endl;
	cin>> ss_filename;
	// if filename doesn't exist quit
	bool filename_exists = false;
	filename_exists = check_filename_exists(ss_filename);
	if (filename_exists == false)
	{
		cout<<"filename doesn't exist "<<endl;
		return 0;
	}
	cout<<"Wait a few seconds... "<<endl;
	vector<vector<char>> my_tubes = bucket_reader_from_image (ss_filename);
	number_of_tubes = my_tubes.size();
	puzzle myPuzzle(number_of_tubes,my_tubes);

	cout<<isSolved(myPuzzle.get_tubes())<<endl;
	int counter = 0;
	/*myPuzzle.recursive_solve(counter);
	cout<<"number of times helper_solve is called"<<counter<<endl;*/


	vector<string> initial_path = myPuzzle.queue_solve(counter); //  make this function return the path (not done yet);
	///*while (true)*/{
		puzzle myPuzzle2 = myPuzzle;
		int steps_back;
		cout << "Length of intial_path =  "<<initial_path.size()<<endl;
		// cout<< "How many steps do you want to go back? :" ;
		// cin>> steps_back;
		// for (int i = 0; i < steps_back; i++)
		// {
		// 	initial_path.pop_back();
		// }
	
		vector<vector<int>> transformed_path = transform_path_to_integer ( initial_path);
		// vector<vector<int>> transformed_path2= transform_path_to_integer2 (initial_path);
		// if (transformed_path== transformed_path2)
		// {
		// 	cout<<"asdasdasdas"<<endl;
		// }
		
		for (int i = 0; i < transformed_path.size(); i++)
		{
			myPuzzle2.moveFromTo((transformed_path[i][0]-1),(transformed_path[i][1]-1) ); // -1 because we vector starts from index 0 but our path starts from 1 to;
		}

	

		/*cout<<"number of times element added to queue is : "<< counter;*/
		// cout<<"Path with last "<<steps_back <<" steps missing "<<endl;
		cout<<"Path is "<<endl;
		for (int i = 0; i < transformed_path.size(); i++)
		{
			cout<<"step "<<i<<" :"<<transformed_path[i][0]<<" "<<transformed_path[i][1]<<endl;
		} // print truncated path (initial path taken back number of int (steps_back)

		// myPuzzle2.bfsSolve(); // doesn't work, can't handle the branching factor even at simple 5 tube puzzles;
							  // so i try to use it after calculating path with dfs, and then substracting the last few steps to get a shorter path

	//}
	myPuzzle.printTubes();
	cout<<endl<<"Solved puzzle is :"<<endl;
	myPuzzle2.printTubes();





	cout<<endl<<"program ended "<<endl;
	
	
	
	
	
	return 0;
}

//
//11
//kpmt
//grkp
//poyl
//yllt
//rmtg
//grmo
//mpgk
//tyor
//yolk
//empty
//empty

//9
//gpyg
//pmkl
//lltk
//typt
//yykt
//kgmm
//glmp
//empty
//empty

//5
//ltkl
//ttkl
//kltk
//empty
//empty


vector<vector<char>> bucket_reader_from_image (string filename)
{
	string system_call_string =  "/Applications/MATLAB_R2021b.app/bin/matlab -batch \"filenamearg = \\\"" +
	filename +
	"\\\";bsp_main;exit;\" >hh.txt 2> /dev/null";
	system(system_call_string.c_str());
    ifstream my_bucket_file;
    string my_filename = "hh.txt";
    my_bucket_file.open(my_filename.c_str());
    int dummy;
    vector<int> ball_stream;
    while(my_bucket_file>>dummy)
    {
        ball_stream.push_back(dummy);
    }
    unordered_map<int,char> index_to_char;
    int counter = 0;
    index_to_char.emplace(0,'A'); // empty spaces are marked with character A
    for (size_t i = 0; i < ball_stream.size(); i++)
    {
        int curr_ball_value = ball_stream[i];
        if (curr_ball_value != 0)
        {
            if (index_to_char.count(curr_ball_value) == 0) // doesn't exist
               {

                   char corresponding_character = 'B' + counter;
                   index_to_char.emplace(curr_ball_value,corresponding_character);
                   counter++;
               } 
            // if it exists dont do anythinng
        } 
    }
    
    int bucket_count = ball_stream.size()/4;
    vector<vector<char> > my_buckets( bucket_count, vector<char>(4) ); // dimensions = bucketcount x 4
    int bucket_fill_loop_counter = 0;
    for (size_t i = 0; i < bucket_count; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            int curr_ball = ball_stream[bucket_fill_loop_counter];
            my_buckets[i][j] = index_to_char[curr_ball];
            cout<<my_buckets[i][j];
            bucket_fill_loop_counter += 1;
        }
        cout<<endl;
    }
    


    my_bucket_file.close();
	remove("hh.txt");
      
	return my_buckets;

}

bool check_filename_exists(string fname)
{
	// try to open file, if it fails return false;
	ifstream my_file;
	string fpath = "./screenshots/";
	fpath += fname;
	my_file.open(fpath);
	if (my_file)
	{
		return true;
	}
	else
	{
		return false;
	}

}


vector<vector<int>> transform_path_to_integer (vector<string> path)
{
	vector<vector<int>> transformed_path (path.size(),vector<int> (2));
	for (int i = 0; i < path.size(); i++)  // transform path to 
	{
		string first;                // an element of initial path is like the following: 11 13      
		string second;
		bool gap_reached = false;     // gap is the ' ' character, first is 11 second is 13                   
		for (int j= 0; j < path[i].size(); j++)
		{
			if (path[i][j] != ' ')
			{
				if (gap_reached == false)
					first += path[i][j];
				else if (gap_reached == true)
					second+= path[i][j];
			}
			else
				gap_reached = true;
		}
		transformed_path[i][0] = stoi(first);
		transformed_path[i][1] = stoi(second);
	}
	return transformed_path;
}


vector<vector<int>> transform_path_to_integer2 (vector<string> path)
{
	vector<vector<int>> transformed_path (path.size(),vector<int>(2));
	for (int i = 0; i < path.size(); i++)
	{
		stringstream path_step (path[i]);
		int first;
		int second;
		path_step>>first;
		path_step>>second;
		transformed_path[i][0] = first;
		transformed_path[i][1] = second;
	}
		
	return transformed_path;
}




//9
//myly
//ylkt
//pggl
//tmyp
//kplg
//tmpt
//kkmg
//1234567
//1234567

	

	
	
	
	

	
	