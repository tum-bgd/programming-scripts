# Task Sheet 2 (Lectures 4-6)

**Qualification Goal:** In this task sheet, you are expected to develop routine in writing loops and recursions for simple cases. Some of the given formulas are helpful to know.


You can submit your results to Moodle for correction, but preferably as a single C file for all things you want to have corrected.  *We will discuss these tasks in the lecture to some extent. But to develop some routine in programming, you need to solve these tasks yourself, preferably without help from the Internet. It is advisable to do these tasks repeatedly (or Google for different sum formulas) until you are able to do them.*

## Task 1: Loops
Implement the following expressions using loops. If two sides are given, implement one as a loop, the other one as an expression. Put the values of the left hand side into a variable lhs, the right hand side into rhs and compare the two values. Output an error message if they don't fit. 

$$ \sum_{i=1}^{n} i = \frac{n(n+1)}{2}$$
*Example*: 
```
#include<stdio.h>

int main(void){
   int lhs=0;
   for (int i=1; i<= n;i++)
     lhs += i;

   rhs=n*(n+1) / 2;
   print("LHS: %d\nRHS: %d\n", lhs, rhs);
   if (rhs != lhs)
     print("Something is wrong");
};
```
- $$ \sum_{i=1}^{n} i^2 = \frac{n(n+1)(2n+1)}{6}$$
- $$ \prod_{i=1}^{10} n$$
- $$ (a+b)^n = $$
- $$ \sum_{i=1}^{10} i$$
- $$ \sum_{i=1}^{10} (2i+3)$$
- $$ n! = \prod_{i=1}^n i$$



## Task 2
Please implement a factorial function first (you could find one in the script, but it is better to try it on your own). It should have the signature
```
int factorial(int k)
```
Then only implement the expression of the binomial coefficient.

$$\left( \begin{array}{llll}
n\\
k\\
\end{array} \right)= \frac{n!}{k!(n-k)!}
$$

Check it with some known values by hand (create the values and double-check your implementation).

The binomial coefficient is traditionally not defined as such a quotient, but in a recursive manner as follows:

First, we fix base cases

$$\left( \begin{array}{llll}
n\\
0\\
\end{array} \right)= 1 = 
\left( \begin{array}{llll}
n\\
n\\
\end{array}\right)
$$

and then the recurisve relation

$$
\left( \begin{array}{llll}
n+1\\
k+1\\
\end{array}\right)=\left( \begin{array}{llll}
n\\
k\\
\end{array}\right)+\left( \begin{array}{llll}
n\\
k+1\\
\end{array}\right)
$$

Implement a recursive function. Note that you will have to rephrase the reccurence relation such that given $n$ and $k$ you can call the binomial function with certain values.

Create a table how long it takes to compute all coefficients up to $m$, more precisely the set of values:

$$C_m = \left\{\left( \begin{array}{llll}
n\\
k\\
\end{array}\right)
\text{ for which } 0 \le k \le n \le m
\right\} 
$$

Your program is expected to fail (taking too long) for some cases from $C_{65}$.

However, there is a solution to this. And this is a good argument why we need to study *efficient* algorithms and why mathematical definitions are sometimes handy for proofs, but bad for computers.

Construct the algorithm given the following non-recursive definition.

$$\left( \begin{array}{llll}
n\\
k\\
\end{array}\right)=\prod_{i=1}^k\frac{n+1-i}{i}
$$

Give the number of steps for a concrete instance and estimate the complexity for $n\to \infty$ assuming $k\le n$.

Speed up this program by transforming the problem for $2k>n$ using the symmetry setting $k:=n-k$.

Does this change the complexity? Does it change the runtime? Explain.
