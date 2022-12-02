#include<stdio.h>
#include<math.h>


double x;
double y;
double angle; /// in degrees

FILE *f;

/*
A simple visualization of recursion: 

The following function initiated with a line will output points to our
GNUplot file. It is called with two 2D points: start and end. 

But instead of just drawing the line, the line will be cut into four parts
1/4 of the line horizontal, continuing diagonal up to the middle,
continuing diagonal down to the base line continuing to the end. 

We implement this as turtle graphics, as we recurse this process for a certain depth. 
Let us try to do it
*/

void move(double );
void turn(double by);

void fractal( double length, int depth)
{
   // non-recursive first
   if (depth <= 0){
      //draw
      move (length/4);
      turn (45);
      move ( (length/4)* sqrt(2)); // diagonal
      turn(-90);
      move ( (length/4)* sqrt(2)); // diagonal
      turn (45);
      move(length/4);
  }else{

      //draw
      fractal (length/4, depth-1);
      turn (45);
      fractal ( (length/4)* sqrt(2), depth -1); // diagonal
      turn(-90);
      fractal ( (length/4)* sqrt(2),depth -1); // diagonal
      turn (45);
      fractal(length/4, depth-1);
  }

  
}

/*
This is obviously not efficient as two times the same structure is there (redundancy).

C++11 provides lambdas to the resque.

A lambda is a local function that can
- be assigned to a variable
- be called like a function
- return a value
- capture data from the current scope (by reference or by value, we don't need it now)

Modern C++ fractal is therefore:

*/
#include<functional> // for std::function to declare the variable f holding our function
void fractal2( double length, int depth)
{
   // default is to call ourselves
   std::function<void(double,int)> f = fractal2;
   // but if depth is zero, we call move instead
   if (depth <=0)
      f = [](double length, int depth) { move(length); };
  // now call f
  f (length/4, depth -1);
  turn (45);
  f ( (length/4)* sqrt(2), depth -1); // diagonal
  turn(-90);
  f ( (length/4)* sqrt(2), depth -1); // diagonal
  turn (45);
  f(length/4, depth -1);
}


void move(double len=1)
{
    x = x + len * cos(angle / 180.0 * M_PI);
    y += len * sin(angle / 180.0 * M_PI);
    if (f != NULL)
       fprintf(f, "%f %f\n",x,y);
}
void init()
{
   x = y=angle=0;
   move(0); // this will just output
}

void turn(double by)
{
    angle += by;
    // this is completely unneeded, but might be nice for debugging and is a common pattern
    // it is only efficient when you are doing moderate turns. For massive turns (e.g., angle=10e9) this
    // will be long loops.
    while(angle >= 360.0) angle -= 360;
    while (angle < 0) angle += 360; 
}


int main()
{
   f = fopen("plot.dat","w"); // this will overwrite
   if (f == 0) {
      perror("File Problem: ");
      exit(-1);
   }

   // init the turtle
   init();
   // do some turtle graphics (this is a star, is it?)
   for (size_t i=0; i < 8; i++)
   {
       fractal2(1,1); // x y --> x2 y2, depth of recursion
       turn(360 / 8);
   }
   printf("%f\n",angle);
   return 0;

}
