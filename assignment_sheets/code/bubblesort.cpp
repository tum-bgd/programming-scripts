#include<iostream>
#include<vector>
#include<iterator>
using namespace std;
void print(vector<int> const &input)
{
    copy(input.begin(),input.end(),ostream_iterator<int>(cout, " "));
}

int main(void)
{
   vector<int> A {9,2,6,3,7,4};
   cout << "start; A=";  print(A); cout << endl;

   for (size_t n=A.size(); n>1; n--)
   {
      for (size_t i=0; i<n-1; i++){
          if (A[i] > A[i+1]){
              auto tmp = A[i];
              A[i] = A[i+1];
              A[i+1] = tmp;
          } 
     }
     cout << "n: " << n << "; A=";
     print(A);
     cout << endl;
  } 
}
