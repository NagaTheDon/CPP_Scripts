#include <iostream>


using namespace std;

class Booth
{

public:
	//Default Constructor
	Booth() : mETA(0), mNumGroups(0), mIsAvaiable(true), mNumOfPeople(0)
	{

	}

	//Setters

	void SetTime(int aTime)
	{
		mETA = aTime;
	}

	void SetGroups(int aNum)
	{
		mNumGroups++;
		mNumOfPeople += aNum;
		SetTime(aNum);
	}

	void SetAvailable(bool aAvai)
	{
		mIsAvaiable = aAvai;
	}

	void OnBreak(bool aBreak)
	{
		mIsOnBreak = aBreak;

		if(aBreak)
		{
			SetAvailable(false);
		}

		else
		{
			SetAvailable(true);
		}
	}

	//Getters

	int GetNumGroups(void)
	{
		return mNumGroups;
	}

	bool IsAvaiable(void)
	{
		return mIsAvaiable;
	}

	int GetNumPeople(void)
	{
		return mNumOfPeople;
	}

	bool IsOnBreak(void)
	{
		return mIsOnBreak;
	}

	//Report Status
	void ReportStatus(void)
	{
		cout << "Num Of Groups: " << mNumGroups << endl;
		cout << "Num Of People: " << mNumOfPeople << endl;
		cout << "Is Available? " << mIsAvaiable << endl;
		cout << "Is On Break? " << mIsOnBreak << endl;
	}
private:
	int mETA; 
	int mNumGroups;
	int mNumOfPeople; 
	bool mIsAvaiable;
	bool mIsOnBreak;
};


int AllGroupsChecked(Booth* aBooths, int aNumOfBooths)
{
	int NumOfChecked = 0;
	for(int i = 0; i < aNumOfBooths; i++)
	{
		NumOfChecked += aBooths[i].GetNumGroups();
	}

	cout << NumOfChecked << endl;
	return NumOfChecked;
}

void ResetBooths(long aTime, Booth* aBooths, int aNumOfBooths)
{
	for(int i = 0; i < aNumOfBooths; i++)
	{
		if(aBooths[i].GetNumPeople() % 10 == 0) // So, if a booth has checked 10 passengers
		{
			aBooths[i].OnBreak(true);
		}

		else
		{
			if(aBooths[i].IsOnBreak()) // If a booth is on break
			{
				aBooths[i].OnBreak(false); //The break finishes
			}

			else 
			{
				if(aTime > aBooths[i].GetNumPeople()) //If the booth has finished checking the group
				{
					aBooths[i].SetAvailable(true);
				}
			}
		}
	}
}


int* AllocateGroups(long aTime, Booth* aBooths, int aNumOfBooths, int* aGroupPtr)
{

	ResetBooths(aTime, aBooths, aNumOfBooths);
	int GroupNum = 0;

	for(int i = 0; i < aNumOfBooths; i++)
	{
		if(aBooths[i].IsAvaiable())
		{
			aBooths[i].SetGroups(aGroupPtr[GroupNum]);
			GroupNum++;
		}
	}

	return aGroupPtr + GroupNum;
}

int main()
{
	cout << "Enter the number of booths : " << endl;
	int NumOfBooths = 0; 
	cin >> NumOfBooths; 


	//Gathering the number of groups
	cout << "Enter the number of groups : " << endl ;
	int NumOfGroups; 
	cin >> NumOfGroups;

	Booth Booths[NumOfBooths]; 
	int GroupArr[NumOfGroups]; 

	for(int i = 0; i < NumOfGroups; i++)
	{
		cin >> GroupArr[i]; 
	}

	cout << "Done taking inputs " << endl;
	long time = 0; 
	int* ArrayPtr = &GroupArr[0];

	while(AllGroupsChecked(Booths, NumOfBooths) < 6)
	{
		time++;
		ArrayPtr = AllocateGroups(time, Booths, NumOfBooths, ArrayPtr);

		if(time == 10)
			break;
	}

	return 0;
}