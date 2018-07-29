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
		// cout << "Demonination :" << mDenomination << " has been set to zero!" << endl;
		mRemainder = 0;
	}

	void ContainerCalculation(int aGivenValue) {
		mValue = aGivenValue;
		mNumber = mValue / mDenomination;
		mRemainder = mValue % mDenomination;
	}

	void ReportStatus(void) {
		cout << "Denomination: " <<mDenomination << endl;
		cout << "Value Given: " << mValue << endl;
		cout << "Number: " << mNumber << endl;
		cout << "mRemainder: " << mRemainder << endl;
		cout << "=============" << endl;
	}

private:
	int mDenomination;
	int mValue;
	int mNumber;
	int mRemainder;

};

void TransferValueToNextContainer(int aStartIndex, Container** ContainerObject){
		// cout << "Index received at TVTNC: " << aStartIndex << endl;
		int mTakenValue = ContainerObject[aStartIndex]->GetRemainder();
		ContainerObject[aStartIndex]->SetRemainderToZero();
		ContainerObject[aStartIndex+1]->ContainerCalculation(mTakenValue);
}

bool IsItDone(Container** ContainerObject, int mNumOfDenominations, bool& mImpossible)
{
	cout << "Is it Done? " << endl;

	if(ContainerObject[mNumOfDenominations - 1]->GetRemainder() == 0)
	{
				return true;
	}

	else 
	{
		mImpossible = true;
		for(int i = mNumOfDenominations-2; i >=0; i--)
		{
			if(ContainerObject[i]->GetValue() != 0)
			{
				mImpossible = false;
				return false;
			}
		}

		if(mImpossible)
		{
			return true;
		}
	}
}

int FindStartIndex(Container** ContainerObject, int aNumberOfDenominations)
{
	int mBottomIndex = aNumberOfDenominations - 2;
	int mStartIndex = 255; // Because ZERO could be an index of a container
	for(int i = mBottomIndex; i >= 0; i--)
	{
		if(ContainerObject[i]->GetValue() > 0)
		{
			mStartIndex = i; 
			return mStartIndex;
			break;
		}
	}
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
 		TransferValueToNextContainer(i, ContainerObject);
 	}

 	// for(int i = 0; i < mNumOfDenominations; i++) {
 	// 	ContainerObject[i]->ReportStatus();
 	// }

 	bool mImpossible = false; 

 	// cout << ""

 	while(IsItDone(ContainerObject, mNumOfDenominations, mImpossible) == false)
 	{
 		cout << "Entered Here!" << endl;
 		for(int i = FindStartIndex(ContainerObject, mNumOfDenominations); 
 			i < mNumOfDenominations; i++)
 		{
 			cout << "i: " << i << endl;
  			TransferValueToNextContainer(i, ContainerObject);
 		}
 	}

 	cout << endl << "Exited the While loop! " << endl;

 	// if(mImpossible)
 	// {
 	// 	cout << "It is impossible!" << endl;
 	// }
 	// else
 	// {
 	// 	cout << "I think it is done! Just Check now! Debug!" << endl;
 	// }

	return 0;
}