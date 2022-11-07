#include<iostream>
int B(int v);

int A(int v)
{
   if (v >8) return B(v+2);
   return A(v*2);
}
int B(int v)
{
   while (v>5) return B(v-5);
   return v-2;
}

int main()
{
   std::cout << "A(" << 8 << ") == " << A(8) << std::endl;
   std::cout << "A(" << 12 << ") == " << A(12) << std::endl;
}
