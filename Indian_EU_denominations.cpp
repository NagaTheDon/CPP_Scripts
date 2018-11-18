#include <iostream>
#include <string.h>
#include <bits/stdc++.h>

using namespace std;
template<typename T>
void convert_num(T aNum, bool aIsEU)
{
  T Remaining_Num = aNum;
  string StrWithComma;

  int CommaNum = 0;
  int CheckNum = 3;

  while(Remaining_Num > 0)
  {
    int digit = Remaining_Num % 10;
    Remaining_Num = Remaining_Num / 10;

    if(CommaNum != 0)
    {
      if(CommaNum == CheckNum)
      {
        StrWithComma += ',';
        aIsEU ? CheckNum += 3 : CheckNum += 2;
      }
      
    }
    
    CommaNum++;
    StrWithComma += digit + '0';
  }
  reverse(StrWithComma.begin(), StrWithComma.end()); 
  cout <<StrWithComma << endl;
}

int main() {
  
  convert_num(1234, true);
}