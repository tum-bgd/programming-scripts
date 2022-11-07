#include<iostream>
int B(int v);

int A(int v)
{
   if (v >4) return B(v+2);
   return A(v*3);
}
int B(int v)
{
   while (v>4) return B(v-4);
   return v-1;
}

int main()
{
   std::cout << "A(" << 4 << ") == " << A(4) << std::endl;
   std::cout << "A(" << 5 << ") == " << A(5) << std::endl;
}
