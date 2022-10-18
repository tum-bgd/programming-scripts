#include<iostream>

int doubled(int a)
{
   return (a*2);
}

float doubled(float a)
{
   return (a*2);
}

int main(void)
{
   std::cout << "doubled(4)=" << doubled(4) << std::endl
             << "doubled(4.5)=" << doubled(4.5f) << std::endl;
   return 0;
}
