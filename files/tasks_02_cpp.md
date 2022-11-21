# Task Sheet 1: Basic C and C++
C and C++ are important imperative programming languages and we are on our way to master these languages. This task sheet is a collection of a wide range of short programs you are supposed to write in order to gain routine in basic structures such as functions, loop, conditions, input and output.

## Task 1: PrettyPrint
In the lecture, we have seen the hello world program. Extend this program to draw a frame around. Examples can be found on https://texteditor.com/ascii-frames/.

Maybe your program should output
```
╔═════════════╗
║ Hello World ║
╚═════════════╝
```

## Task 2: PrettyPrint 2
Now extend your program to print a string into a frame. 
A string in C++ is given as a pointer of type char. `strlen` can be used to find the length of a string. Complete the following program snippet:

```
void pprint(char *what)
{
   printf("╔");
for /*extend this one to print enough of ═ using strlen(what) */
   printf("╗");
 printf("║ ");
 printf("%s",what);
 /*...*/  
}
```
Make sure that your box wraps the text sensibly (one space character before and after your text)

## Task 3: PrettyPrint3
Extend the previous result in the following way:
For all strings shorter than 50 characeters, draw the box as before. For strings longer than 50 characters, compute a new string in which 47 characters are taken from the parameter and the last three characters are manually set to three dots. In this way, arbitrary long things will be printed as abbreviations into your box code. Node that strings shorter than 50 characters must not be abbreviated.

## Task 4: Calculus Primer
As a simple example, consider the logistic curve:
$$ f(x) = \frac{1}{1+e^{-x}}$$
This function plays a crucial role in machine learning, so it is worth having a look at it early in your career.

### Task 4.1 Plot the Function
As data visualization from C++ is challenging, we will rely on a powerful tool known as gnuplot to show our results. As a preparation, download gnuplot and have a look at http://www.gnuplotting.org/plotting-data/

In this example, gnuplot expects a file to contain your data. Remember that we can redirect the output of programs to files? Your task is to write a C/C++ program that generates a plot of the function as a text file in gnuplots format having always the X coordinate in the first column, the Y coordinate in the second column, and then a newline.

Write a program that generates a plot. In a first version, take constants in your program for start, stepsize, and end as to have a simple loop do all the work going over the X coordinates. Run the program with redirecting the output as follows:
`yourprogram > plot.dat`
Then, use gnuplot to inspect the data. Did you do it right? 

## Task 4.2: The Riemann Integral
As you know, one way of computing the integral of simple functions of one variable is to decompose the parameter space (x) into multiple locations ($x_i$) and replace the true function with a staircase function by using supremum or infimum of the function. 
In our case (except at X=0), there are no singularities and the function is monotonous. Hence, we can replace the supremum (resp. infimum) with maximum and minimum of the function values at the left hand side and right hand side of the interval.
Given a distance parameter $\epsilon$, write a function to compute the upper sum and lower sum (e.g., the one based on maximum and the one based on minimum) of the integral
$$\int_1^2 f(x)dx$$
Write this function in a single loop looking similar to
```
double epsilon = 0.15;
double US=0; // upper sum
double LS=0; // lower sum
for (double x = 1; double x < 2; x+=epsilon)
{
  //...
  US += //...
  LS += ...
}
printf("We believe that the integral I follows\n");
printf("%.2f < I <= %.2f\n", LS,US);
```
Learn that two different things (computing the upper sum and the lower sum) that depend on the same intermediate values can often be combined.

## Task 4.3: The Discrete Differential

Given a function 
```
double f(double x){...}
```
approximate the differential at x=1 by creating a series of discrete difference quotients. Therefore, look at 
https://en.wikipedia.org/wiki/Difference_quotient
and use the central difference formula for varying $\Delta P$

Given a real number $q$, can you estimate the value of 
$\frac{\partial f}{\partial x} (q)$

Note that this approach to calculus lies at the heart of discretizations of partial differential equations and is an essential basic concept related to the method of finite elements which you might already know from simulation.

## Task 5: Prime Numbers
Write a function 
```
void print_primes(int max)
```
that outputs all prime numbers smaller or equal than a given parameter `max`. Therefore, first implement a predicate `is_prime` which returns a boolean value if or if not the function is prime. This should be tested by a simple loop. Division can be tested by using the modulo function: an integer value q divies a value p if and only if 
`p % q == 0`
In this expression `%` denotes the modulo operation of taking the remainder of dividing `p` by `q`.

*Remember, that a predicate is always a function in terms of some data which returns a boolean value.*

https://en.wikipedia.org/wiki/Boolean-valued_function

## Task 6: More on prime numbers
The following function is one in which there is still a lot of magic and unknown information. In number theory, the function $\pi(x)$ is the number of prime numbers smaller than $x$. 
Compute this number for $x \in [0,1000]$ and plot it with gnuplot. Look at the staircase pattern, but also at the overall trend. It is growing with a surprising speed, isn't it? This is the heart of the security of current cryptosystems, hence, of all our online payment, communication, finance systems. If there were not enough prime numbers, it would be ridiculously difficult to find some. But as you might know, one needs prime numbers for some encryption algorithms like RSA. Luckily, prime numbers are so common, that we can quickly generate huge ones (even if they are so large, we will not be able to proof that they are prime).

In cryptography, we sometimes use random numbers together with a series of tests to find numbers of which we believe they are prime. They are known industiral-grade prime numbers.

https://en.wikipedia.org/wiki/Industrial-grade_prime




