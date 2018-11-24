#include <iostream>

using namespace std;

class Path
{
public:
	//Default Constructor
	Path() : mStartPos(0), mEndPos(0), mFoolishIndex(0)
	{

	}

	Path(int aStartPos, int aEndPos, int aIndex) :
		mStartPos(aStartPos),
		mEndPos(aEndPos),
		mFoolishIndex(aIndex)
	{

	}

	void SetStart(int aStartPos)
	{
		mStartPos = aStartPos;
	}
	
	void SetEnd(int aEndPos)
	{
		mEndPos = aEndPos;
	}

	void SetIndex(int aIndex)
	{
		mFoolishIndex = aIndex;
	}

private:
	int mStartPos;
	int mEndPos; 
	int mFoolishIndex;

};

int main()
{
	cout << "Enter the number of locations: " << endl;
	
	int NumOfLoc = 0;
	cin >> NumOfLoc;

	cout << "Enter the number of paths: " << endl;

	int NumOfPaths = 0;
	cin >> NumOfPaths;


	Path PathObjects[NumOfPaths];

	for(int i = 0; i < NumOfPaths; i++)
	{
		int StartPos = 0; 
		int EndPos = 0; 
		int Index = 0; 

		cin >> StartPos >> EndPos >> Index; 
		PathObjects[i].SetStart(StartPos);
		PathObjects[i].SetEnd(EndPos);
		PathObjects[i].SetIndex(Index);
	}

	int GameStart = 0;
	int GameEnd = 0;

	cin >> GameStart >> GameEnd;

	//Need to learn Travelling salesman problem


	return 0;
}