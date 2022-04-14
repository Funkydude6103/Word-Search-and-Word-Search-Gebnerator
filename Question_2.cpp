#include<iostream>
#include<string>   //For string Functions
#include<fstream>  //For file inputing
#include<queue>    //For loading the words to find in the Grid
using namespace std;

char DIRECTIONS[8][2] = { {1,0}, {1,-1}, {1,1}, {0,-1}, {0,1}, {-1,0}, {-1,-1}, {-1,1} }; // All eight directions
ofstream fout;

bool checking(string *grid, string word, int i, int j, int dir_index,const int n, const int m)
{
	int k = 0;
	int start1 = i;  // word starting index of the grid
	int end1 = j;    
	int start2=0;    // ending starting index of the grid
	int end2=0;
	
	for (; i < n && j < m && i >= 0 && j >= 0 && word[k] != '\0'; i = i + DIRECTIONS[dir_index][0], j = j + DIRECTIONS[dir_index][1], k++)
	{
		if (toupper(word[k]) != toupper(grid[i][j]))   // touper is used for converting all the alphabets to Upper case
			return false;
		start2 = i;
		end2 = j;

	}
	if (word[k] == '\0')
	{
		fout << "(" << start1 << "," << end1 << ")" << " " << "(" << start2 << "," << end2 << ")" << " " <<"\n";
		return true;
	}

	return false;
}
void finding_firstindex(string *grid, string word,const int n,const int m) //The task of this functions is to find the first index of word in the grid and then check that in all eight directions
{
	for (int i = 0; i < n;i++)
		for (int j = 0; j < m; j++)
			if (toupper(grid[i][j]) == toupper(word[0]))    // touper is used for converting all the alphabets to Upper case
				for (int k = 0; k < 8; k++)      //all eight directions
					if (checking(grid, word, i, j, k,n,m))
					{

						return;
					}
					
	fout <<"Not Found" << "\n";

}


int main()
{
	ifstream txtfile;
	int n = 0; // No of Rows
	int m = 0; // No of Cols
	int no_words = 0; //No of words

	cout << "Enter the number of rows and cols :";
	cin >> n >> m;

	//intializing the grid
	string* grid= new string[n];  
	txtfile.open("input.txt");
	//Loading the Grid file into the Grid
	for (int i = 0;i<n;i++)
	{
		getline(txtfile, grid[i]);
		//For removing the space 
		int count = 0;
		for (int j = 0; j<m+(m-1); j++)
			if (grid[i][j] != ' ')
				grid[i][count++] = grid[i][j]; 
									   
		grid[i][count+1] = '\0';

	}
	txtfile.close();
	
	//Now loading the words to find in the grid into a queue
	
	cout << "Enter the number of words : \n";
	cin >> no_words;
	string word;
	fout.open("output.txt");
	for (int j = 0; j < no_words; j++)
	{
		cout << "Enter the word :";
		cin >> word;
		cout << endl;
		finding_firstindex(grid, word,n,m);
	}
	fout.close();

	return 0;
	
}
