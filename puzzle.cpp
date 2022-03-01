


#include "puzzle.h"
#include <set>
#include <queue>
#include <vector>
#include <iostream>
#include <stack>

using namespace std;


puzzle::puzzle(int nTube)
{
	number_of_tubes = nTube;
	for (int i = 0; i < nTube; i++)
	{
		string tube;
		cout<<"enter the ball colors(starting from bottom)without space for the tube"<< (i+1) <<endl;
		cin>>tube;
		if (tube.length() == 4)
		{
			tubes.push_back(tube);
		}
		else
			tubes.push_back("");
			
	}
	if (check_correct_combination() == false)
	{
		cout<<"balls are in false order"<<endl;
		for (int i = 0; i < nTube; i++)
		{
			tubes[i] = "aaaa";
		}
	}
	
}
puzzle::puzzle(int nTube, vector<vector<char>> tube_vectors){ 
	//we need to enter the ball colors(starting from bottom)without space for the tube
	// but our tube vectors define the ball colors starting from top to bottom, so we reverse it;
	number_of_tubes = nTube;
	for (int i = 0; i< nTube; i++)
	{
		string tube;
		for (int j = 3; j>= 0; j--)
		{
			tube += tube_vectors[i][j];
		}
		if ( tube == "AAAA") // if tube is equal to AAAA, then that is an empty tube
		{
			tubes.push_back("");
		}
		else{
			tubes.push_back(tube);
		}
	}
	if (check_correct_combination() == false)
	{
		cout<<"balls are in false order"<<endl;
		for (int i = 0; i < nTube; i++)
		{
			tubes[i] = "aaaa";
		}
	}

}
bool puzzle::check_correct_combination()
{
	string all_balls ="";
	for (int i = 0; i < number_of_tubes; i++)
	{
		all_balls.append(tubes[i]);
	}
	for (int i = 0; i < all_balls.length(); i++)
	{
		int number_of_i = 0;
		for (int j = 0; j < all_balls.length(); j++)
		{
			if (all_balls[i] == all_balls[j])
			{
				number_of_i++;
			}
		}
		if (number_of_i != 4)
		{
			return false;
		}
	}
	return true;
}
void puzzle::printTubes()
{
	for (int i = 0; i < tubes.size(); i++)
	{
		if (tubes[i] == "")
		{
			cout<<"empty tube"<<endl;
		}
		else
		{
			cout<<tubes[i]<<endl;
		}
	}
}


bool isSolved(const vector<string> & current_tubes){

	for (int i = 0; i < current_tubes.size(); i++)
	{
		int tube_length = current_tubes[i].size();
		if (tube_length == 4)
		{
			char tube_color = current_tubes[i].at(0);
			for (int j = 1; j < 4; j++)
			{
				if (current_tubes[i].at(j)  != tube_color)
				{
					return false;
				}
			}
		}
		else if (tube_length != 0)
		{
			return false;
		}
	}
	return true;

}
void puzzle::bfsSolve()
{
	int curr_depth = 0;
	int nodes_visited_counter = 0;
	vector<string> path;
	vector<string> starting_tubes  = tubes;
	vector<vector<string>> starting_state;
	starting_state.push_back(starting_tubes);
	starting_state.push_back(path);
	queue<  vector<vector<string>>  > state_queue;
	set <vector<string>> visited_configurations;

	
	state_queue.push(starting_state);
	while (state_queue.empty() == false)
	{
		vector<vector<string>> current_state = state_queue.front();
		state_queue.pop();
		
		if (isSolved(current_state[0]) )
		{
			helper_print_path(current_state[1],nodes_visited_counter);
		}
		nodes_visited_counter += 1;
		if (current_state[1].size() > curr_depth)
		{
			cout<<"Current depth is :" << curr_depth<<endl;
			cout<<"Number of Nodes visited :" <<nodes_visited_counter<<endl;
			curr_depth +=1;
		}
		for (int i = 0; i < number_of_tubes ; i++)
		{
			for (int j = 0; j < number_of_tubes; j++)
			{
				if (    move_is_legal(i,j,current_state[0]))
				{
					
					vector<string> current_tubes = current_state[0];
					vector<string> current_path = current_state[1];
					search_tube_move_from_to(i,j,current_tubes);
					visited_configurations.insert(current_tubes);
					string next_move;
					next_move += to_string(i+1);
					next_move += " ";
					next_move += to_string(j+1);
					current_path.push_back(next_move);
					vector<vector<string>> new_state;
					new_state.push_back(current_tubes);
					new_state.push_back(current_path);
					state_queue.push(new_state);
						
				}
			}
		}

	}

}
vector<string> puzzle::queue_solve(int & counter)
{
	if (isSolved(tubes))
	{
		cout<<"already solved"<<endl;
		return vector<string>(0);
	}
	vector <string> path;
	vector< vector<string> > current_state;
	vector<string> current_tube_state;

	set <vector<string>> visited_configurations;
	vector<string> starting_tubes = tubes;
	stack<vector< vector<string> > > stack_of_states; // 0th element is tube vectors,  1st element is path;
	vector < vector <string>> starting_state;
	starting_state.push_back(starting_tubes);
	starting_state.push_back(path);
	stack_of_states.push(starting_state);
	bool found = false;
	while (stack_of_states.empty() == false && found == false)
	{
		current_state = stack_of_states.top();// 0th element is tubes, 1st element is the path to solution;
		

		if (isSolved(current_state[0]))
		{
			// helper_print_path(current_state[1],counter);
			return current_state[1]; // returns path string vector
			found = true;
		}
		stack_of_states.pop();
		
		if (visited_configurations.count(current_state[0]) == 0 )
		{
			vector<string> configuration = current_state[0];
			visited_configurations.insert(configuration);
			int tubes_size = current_state[0].size();
			for (int i = (tubes_size-1) ; i >= 0; i--)
			{
				for (int j = (tubes_size-1) ; j >= 0; j--)
				{
					if (move_is_legal(i,j,current_state[0]))
					{
						vector<string> current_tubes = current_state[0];
						vector<string> current_path = current_state[1];
						search_tube_move_from_to(i,j,current_tubes);
						string next_move;
						next_move += to_string(i+1);
						next_move += " ";
						next_move += to_string(j+1);
						current_path.push_back(next_move);
						vector<vector<string>> new_state;
						new_state.push_back(current_tubes);
						new_state.push_back(current_path);
						stack_of_states.push(new_state);
						counter ++;
					}
				}
			}
		}
	}
	cout<<"can't find solution "<<endl;
	return vector<string>(0);


}
void puzzle::recursive_solve(int & counter)
{
	set < vector<string> >  visited_configurations  ;
	vector<string> starting_tubes = tubes;
	bool found = false;
	vector<string> path;
	helper_recursive_solve(tubes, visited_configurations,found,path,counter);

	return;
}


void puzzle::helper_recursive_solve( vector<string>   & search_tubes,  set <vector< string> > & visited_configurations,bool & found, vector<string> path ,int & counter)
{
	if ( found == true)
		return;
	visited_configurations.insert(search_tubes);
	if (isSolved(search_tubes))
	{
		found = true;
		cout<<"SOLVED\nSOLVED\n";
		helper_print_path(path,counter);
		return;
	} // else
	for (int i = 0; i < search_tubes.size(); i++) // for every adjacent positions that isn't visited 
	{
		for (int j = 0; j < search_tubes.size(); j++)
		{
			if (move_is_legal(i,j,search_tubes)    )
			{
				vector <string> current_search_tubes = search_tubes;
				search_tube_move_from_to(i,j,current_search_tubes);
				if (visited_configurations.count(current_search_tubes) == 0 )
				{
					string next_move;
					next_move += to_string(i+1);
					next_move += " ";
					next_move += to_string(j+1);
					path.push_back(next_move);
					counter++;
					helper_recursive_solve(current_search_tubes,visited_configurations,found,path,counter);
				}
			}
	}
	}

}

void puzzle::moveFromTo(int from, int to)
{
	if ( move_is_legal(from,to, tubes )  )
	{
		tubes[to].push_back(tubes[from].back());
		tubes[from].pop_back();
	}
	else
		return;
}


void puzzle::search_tube_move_from_to(int from, int to,vector<string> & search_tubes )
{
	int from_length = search_tubes[from].length();
	search_tubes[to].push_back(search_tubes[from].at((from_length -1)));
	search_tubes[from].pop_back();
}



bool puzzle::move_is_legal(int from, int to , const vector<string> & search_tubes)  
{
	
	if ( (search_tubes[to].size() == 4 ) ||   (search_tubes[from].size() == 0 )   )   // there is no place to move or there is no ball to move
	{ 
		return false;
	}
	else if (helper_tube_is_completed(search_tubes[from]) )
		return false;
	else if (from == to)
		return false;
	//else if (search_tubes[to].length() == 0 )
	//	return true;
	else if ( (search_tubes[to].size() > 0 ) && (search_tubes[from].back() != search_tubes[to].back())  ) // ball isn't same color;
	{            /// first expression is added so that search_tubes[to].back() exists and doesn't give segmentation fault-like error;
		return false;
	}
	else // 
	{  // turns out this doesn't matter, it was a misunderstanding;
		/*vector<int> sol (2,0) ; 
		if (helper_tube_mini_solution_exists(sol,search_tubes))
		{
			if (sol[0] == from && sol[1] == to)
			{
				return true;
			}
			else
			{
				return true;
			}
		}*/
			return true;
	}

}
bool puzzle::helper_tube_mini_solution_exists(vector<int> & mini_solutions,const vector<string> & search_tubes) // if a tube can be completed to 4 (a tube is made of 3 balls and could be completed in this turn)
{
	// if there exists a tube with 3 same balls stacked and 1 of the same color is on top of another color;
	for (int i = 0; i < search_tubes.size(); i++)
	{
		if (search_tubes[i].size() == 3  
			&& (search_tubes[i][0] ==  search_tubes[i][1] && search_tubes[i][1] == search_tubes[i][2])) // 3 same color balls are stacked on top
		{
			for (int j = 0; j < search_tubes.size(); j++)
			{
				if ( (search_tubes[j].size() > 0)  &&   search_tubes[j].back() == search_tubes[i][2]) // there exists a free ball that can be put on these 3 balls
				{ // first condition is needed to make sure search_tubes[j] exists;
					mini_solutions[0] = j; // from 
					mini_solutions[1] = i; // to
					return true;
				}
			}
		}
	}
	return false; // if it survives the for loop there isn't a mini solution
	
}
bool puzzle::helper_tube_is_completed(const string & search_tube)
{
	int search_tube_length = search_tube.size();
	if (search_tube_length == 4)
	{
		char search_tube_color = search_tube[0];
		for (int i = 1; i < 4; i++)
		{
			if (search_tube[i] != search_tube_color)
			{
				return false;
			}
		}
		return true; // must survive the loop so all 4 balls are the same color;
	}
	
	else if (search_tube_length == 3)//this is just to make the solutions shorter by avoiding 
////unncessary movement of tubes with 3 balls (as there is no reason to move a tube with 3 balls already); // i believe this will reduce path length by a lot
	{
		char search_tube_color = search_tube[0];
		for (int i = 0; i < 3; i++)
		{
			if (search_tube[i]!= search_tube_color)
			{
				return false;
			}
		}
		return true;  // survived the for loop, so all 3 balls are the same color;
	}
	else
	{
		return false;
	}

}

vector<string> puzzle::get_tubes()
{
	vector <string> return_tubes = tubes;
	return return_tubes;

}

void puzzle::helper_print_path(vector<string> path, int counter)
{
	cout<<"Length of path is "<< path.size()<<endl;
	char answer;
	cout<<"Do you want to print the path, Y or N ?";
	cin>>answer;
	if (answer == 'Y')
	{
		for (int i = 0; i < path.size(); i++)
		{
			cout<<path[i]<<endl;
		}	
		cout<<"number of nodes check = "<<counter<<endl;

	}
	



}
