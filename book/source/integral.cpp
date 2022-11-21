#include<iostream>
#include<math.h>

/** 
*   @brief  The primitive integral function for f(x) = x^2
*  
*   @param  x is any float
*   @return float; F(x) = 1/3 x^3
*/  
double F(double x)
{
   return (1.0/3.0)*(x*x*x);
}

/** 
*   @brief  The function f(x) = x^2
*  
*   @param  x is any float
*   @return float; f(x) = x^2
*/  
double f(double x)
{
    return x*x; // f(x) = x²
}



/** 
*   @brief  The integral as a sum over a barplot representation, equdistant left version
*
*   We take an equidistant discretization of the integration domain and build bars with a height
*   taken from the *left* of the discretization integral. The contribution to the integral is thus
*   width divided by the number of intervals.
*
*   For f(x) = x^2 and x > 0, this is a lower bound as the value at the left of an interval
*   represents the infimum of all values in the interval. Hence, the staircase function is nowhere larger
*   than the true function with equality in all discretization points.
*  
*   @param  x is any float
*   @return float; lower bound to \int_low^high f(x) dx 
*/  
double left_barsum(double low, double high, size_t N)
{
   double ret = 0;
   for (size_t i=0; i<N; i++)
   {
       double x = low + i*(high-low) / N;
       
       ret += f(x);
   }

   return ret * (high-low) / N;
}

/** 
*   @brief  The integral as a sum over a barplot representation, equdistant right version
*
*   We take an equidistant discretization of the integration domain and build bars with a height
*   taken from the *right* of the discretization integral. The contribution to the integral is thus
*   width divided by the number of intervals.
*
*   For  f(x) = x^2, x>=0 , this is an upper bound as the value at the left of an interval
*   represents the supremum of all values in the interval. Hence, the staircase function is nowhere smaller
*   than the true function with equality in all discretization points.
*  
*   @param  x is any float
*   @return float; upper bound to \int_low^high f(x) dx 
*/  

double right_barsum(double low, double high, size_t N)
{
   double ret = 0;
   for (size_t i=1; i<=N; i++)
   {
       double x = low + i*(high-low) / N;
       
       ret += f(x);
   }

   return ret *(high-low)/ N;
}




int main(void)
{
   std::cout << "Integral of f(x) = x^2" << std::endl;
   std::cout << "1/3 x^3 in bounds" << std::endl;
   const double left=2;
   const double right=3;
   printf("Symbolic: F(%.2f)-F(%.2f) = %.2f\n", right, left, F(right)-F(left));
   printf("Numeric Solution (left_barsum)\n");
   for (int N=2; N <1000000; N+= 5000)
   {
      double value = left_barsum(left, right, N);
      double value2 = right_barsum(left,right,N);
      
      double relE = value / (F(right) - F(left));
      double relE2 = value2 / (F(right) - F(left));
       printf("For %06d:\t %.10f \t rel=%f\%\t %.10f \t rel=%f\%\n",
	   N,value, relE*100, value2, relE2*100);
      double absE = fabs(value2 - value);
      printf("Absolute Uncertainty: %f\n", absE);
      printf("Error of the center: %g\n", ((F(right)-F(left))- ((value2 + value)/2)));
    }

return 0;
}
