#include<iostream>
class A
{
   public:
      int v,w;
};
class B: public A
{
   private:
     int x;
   public:
     B(): x(0){std::cout << "B's default constructor called"<<std::endl;};
     B(int _v) {v = _v; std::cout << "B's (int) constructor called"<<std::endl;};
};
int main()
{
   B* instance = new B(42); 
   std::cout << instance->x << std::endl;
   return 0;
}
