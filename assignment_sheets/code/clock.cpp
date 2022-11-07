#include<iostream>
#include<vector>
#include<iterator>
using namespace std;
void print(vector<int> const &input)
{
    std::cout << input[0] << input[1]<< ":" <<input[2]<<input[3] << std::endl;
}

void f(vector<int> &a, int where=3)
{
    a[where] ++;
    switch(where){
       case 1:
       case 3:
         if (a[where] >9)
	    a[where] = 0;
         break;
      case 2:
         if (a[where] >5)
	    a[where] = 0;
	break;
      case 0:
         if (a[where] >2)
	    a[where] = 0;
	break;
    }
    if (a[where] == 0 && where != 0)
       f(a, where-1);
}
int main(void)
{
   vector<int> A {0,8,1,5}; 
   print(A);f(A);
   print(A);f(A);
   while ( A[0] != 1 || A[1] != 2 || A[2] != 0 || A[3] != 0)
   {
     f(A);
   }
   print(A);
}
