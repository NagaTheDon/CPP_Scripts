#include <iostream>

using namespace std;

class Container {
public:
	Container(int aDenomination) : mDenomination(aDenomination), 
								   mValue(0), 
								   mNumber(0),
								   mRemainder(0) {}

	int GetDenomination(void) {
		return mDenomination;
	}

	int GetValue(void) {
		return mValue;
	}

	int GetNumber(void) {
		return mNumber;
	}

	int GetRemainder(void) {
		return mRemainder;
	}

	void SetRemainderToZero(void) {
		mRemainder = 0;
	}

	void SetValueToZero() {
	mValue = 0;
	}

	void DecrementNumber() 
	{
	mNumber--;
	}

	void ContainerCalculation(int aGivenValue) {
		mValue += aGivenValue;
		mNumber = mValue / mDenomination;
		mRemainder = mValue % mDenomination;
	}

	void ReportStatus(void) //Just for debugging purposes
	{
		cout << "Denomination: " <<mDenomination << endl;
		cout << "Value Given: " << mValue << endl;
		cout << "Number: " << mNumber << endl;
		cout << "mRemainder: " << mRemainder << endl;
		cout << "=============" << endl;
	}

	void ReportNumber(void)
	{
		cout << "Number of " << mDenomination << "s : " << mNumber << endl;
	}

private:
	int mDenomination;
	int mValue;
	int mNumber;
	int mRemainder;

};

void TransferValueToNextContainer(int aStartIndex, Container** ContainerObject, int mNumberOfDenominations){
		int mTakenValue = ContainerObject[aStartIndex]->GetRemainder();
 		ContainerObject[aStartIndex]->SetRemainderToZero();
		ContainerObject[aStartIndex+1]->ContainerCalculation(mTakenValue);

    if(mNumberOfDenominations-1 > aStartIndex )
    {
      ContainerObject[aStartIndex]->SetValueToZero();
    }
}

void TransferTopDenomToBotDenom(int aStartIndex, Container** ContainerObject)
{
  ContainerObject[aStartIndex]->DecrementNumber();
  ContainerObject[aStartIndex+1]->ContainerCalculation(ContainerObject[aStartIndex]->GetDenomination());
}

bool IsItDone(Container** ContainerObject, int mNumOfDenominations, bool& mImpossible)
{

	if(ContainerObject[mNumOfDenominations - 1]->GetRemainder() == 0)
	{ 
		return true; 
	}

		else 
	{
		mImpossible = true;
		for(int i = mNumOfDenominations-2; i >=0; i--)
		{
			if(ContainerObject[i]->GetNumber() != 0)
			{
				mImpossible = false;
				return false;
			}
		}

		if(mImpossible)
		{
			return true;
		}

    else
    {
      return false;
    }
	}
}

int FindStartIndex(Container** ContainerObject, int aNumberOfDenominations)
{
	int mBottomIndex = aNumberOfDenominations - 2;
	int mStartIndex = 255; // Because ZERO could be an index of a container
	for(int i = mBottomIndex; i >= 0; i--)
	{
		if(ContainerObject[i]->GetNumber() > 0)
		{
			mStartIndex = i; 
			break;
		}
	}
  return mStartIndex;
}

int main()
{
	cout << "Please enter the number of denominations: " << endl;

 
	int mNumOfDenominations;
	cin >> mNumOfDenominations;
	Container** ContainerObject = new Container*[mNumOfDenominations]();

	cout << "Please enter the denominations" << endl;

	int mEnteredDenomination;
	for(int i = 0; i < mNumOfDenominations; i++)
	{
		cout << " > " ;
		cin >> mEnteredDenomination;
		ContainerObject[i] = new Container(mEnteredDenomination);
		cout << endl;
	}
 
 	int mTotalAmount = 0;
 	cout << "Please enter the total amount you wish to get a change for: ";
 	cin >> mTotalAmount;

 	int StartCalculationIndex = 0;

 	ContainerObject[0]->ContainerCalculation(mTotalAmount);

 	for(int i = 0; i < mNumOfDenominations-1; i++) {
 		TransferValueToNextContainer(i, ContainerObject, mNumOfDenominations);
 	}

 	bool mImpossible = false; 
	bool mEarlyFinish = false;

 	while(IsItDone(ContainerObject, mNumOfDenominations, mImpossible) == false)
 	{

    	int mStartIndex = FindStartIndex(ContainerObject, mNumOfDenominations); 

 		for(int i = mStartIndex; i < mNumOfDenominations-1; i++)
 		{
	       if(i == mStartIndex)
	       {
	         TransferTopDenomToBotDenom(i, ContainerObject);
	       }

	       else
	       {
	 	        TransferValueToNextContainer(i,ContainerObject, mNumOfDenominations);
				
				if(IsItDone(ContainerObject, mNumOfDenominations, mImpossible) == true)
				{
					mEarlyFinish = true;
					break;
				} 
	       }
	   
		   if(mEarlyFinish)
		   {
			   break;
		   }
 
 		}
 	}

   if(mImpossible)
   {
     cout << "It is impossible!" << endl;
   }

   else
   {
     for(int i = 0; i < mNumOfDenominations; i++)
     {
       ContainerObject[i]->ReportNumber();
     }
   }

	return 0;
}