#include <iostream> 
#include<fstream>
#include<cstring>
#include<string>
#include<queue>
#include <stdlib.h>     
#include <time.h>
using namespace std;
char DIRECTION[8][2] = { {1,0}, {1,-1}, {1,1}, {0,-1}, {0,1}, {-1,0}, {-1,-1}, {-1,1} }; //All eight directions in a 2d Array
  


bool finding_free_space_at_that_index(char **grid, string word, int i, int j, int direction_index,const int size)
{
	int k = 0;
	int i2 = i;
	int j2 = j;
	for (; i < size && j < size && i >= 0 && j >= 0 && word[k] != '\0'; i = i + DIRECTION[direction_index][0], j = j + DIRECTION[direction_index][1], k++)
	{
		if (grid[i][j] != '*')
			return false;
	}

	if (word[k] == '\0')
	{
		for (int i = i2, k = 0, j = j2; k < word.size();)
		{
			if (word[k] != ' ')    //for dealing with space between a two word word
			{
				grid[i][j] = word[k];
				i = i + DIRECTION[direction_index][0];
				j = j + DIRECTION[direction_index][1];
			}
			k++;
		}
		return true;
	}

	return false;
}
bool find_index_of_free_space(char **grid, string word,const int size)
{   
	int i;
	int j;
	while (1)
	{ 
		i = rand() % size;
		j = rand() % size;
		if (grid[i][j] == '*')
		break;
	}
	for (int k = 0; k < 8; k++)
	{
		if (finding_free_space_at_that_index(grid, word, i, j, k,size)) //sending that index in which a free space is found to check in all eight directions and to put it in the first avaible space found
		{
			return true;
		}
	}

	return false;
}

queue<string> words;   //The list of the words
int main()
{
	srand(time(0));   //For thr random numbers to change 
	string W;
	int count = 0;
	int size = 0;
	ifstream txtfile;

	txtfile.open("WordList.txt");

	for (count = 0; !txtfile.eof(); count++)  //input the grid from the file
	{
		getline(txtfile, W);   
	
		words.push(W);
		if (W.size() > size)      //finding the maximum word to intialize the size of the grid
		{
			size = W.size();
		}
	}
	txtfile.close();
	if (size < words.size())      //Comparing the size with the number of words which ever is greater size is equal to that
	{
		size = words.size();
	}
	size = size+3;      //increasing the size by 3 to decrease the time complexity of the program
	char** grid = 0;
	grid = new char* [size];   //Making of the grid
	for (int i = 0; i < size; i++)
	{
		grid[i] = new char[size];
	}
	cout << endl;
	for (int i = 0; i < size; i++)    //intializing the grid to *
	{
		for (int j = 0; j < size; j++)
		{
			grid[i][j] = '*';
		}
	}
	while (!words.empty())     //Putting the words in the grid
	{
		string temp = words.front();
		bool check = find_index_of_free_space(grid,temp,size);
		if (check == true)
		{
			words.pop();
		}
		else
		{
			continue;
		}
	}

	//for adding random alphabets
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (grid[i][j] == '*')
			{
				int r = rand() % 26;   // generate a random number
				char c = 'A' + r;            // Convert to a character from a-z
				grid[i][j] = c;
			}
		}
   }
	//for converting every alphabet to a upper case

	for (int i = 0; i < size; i++)     
	{
		for (int j = 0; j < size; j++)
		{
			grid[i][j] = toupper(grid[i][j]);
		}
	}
	//for printing the grid in output.txt
	ofstream fout;
	fout.open("output.txt");
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			fout << grid[i][j] << " ";
		}
		fout << endl;
	}

	fout.close();

	return 0;
}
