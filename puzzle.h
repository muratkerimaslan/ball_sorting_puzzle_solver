

#include <vector>
#include <string>
#include <set>
using namespace std;



class puzzle

{
public:
	puzzle(int nTube);
	puzzle(int nTube, vector<vector<char>> tube_vectors);
	vector<string> get_tubes();
	void moveFromTo(int from,int to);
	void recursive_solve(int & counter);

	vector<string> queue_solve(int & counter); // this solver alone is enough actually

	void printTubes();

	void bfsSolve(); //// bfs doesn't work nicely with higher number of tubes because even with a 5 tube puzzle
	///number of nodes visited are following 2,8,40,184,816,3396,13430,52156,203824;  and memory usage maxes out and termiantes before it can find a solution to the 5 tube puzzle
	// so I use it to minimize the latest steps; but that doesn't matter too much as the solution becomes clear already when I do half the moves.

private:
	vector<string> tubes;
	int number_of_tubes;
	bool check_correct_combination();
	bool helper_tube_mini_solution_exists(vector<int>  & sol_vec,const vector<string> & search_tubes);
	void helper_recursive_solve(vector<string> & search_tubes ,set<  vector<string> > &  ,bool & found,vector<string> ,int & counter);
	void search_tube_move_from_to(int from, int to, vector<string> & search_tubes);
	
	void helper_print_path(vector<string>,int s);
	bool helper_tube_is_completed(const string & search_tube);
	bool move_is_legal(int from,int to, const vector<string> & );
};
bool isSolved(const vector<string> &);

// each color must be stacked on a different container
// only SAME COLOR balls can be placed on top of each other
// there are 4 balls per stack