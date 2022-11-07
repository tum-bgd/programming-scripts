#include<iostream>
#include<list>
#include<string>
#include<math.h>


std::string encode(double number, std::string code,int maxIter = 10)
{
   int radix = code.size();
   int integer_part  = static_cast<int> (number);
   double fractional_part = number - integer_part;
   std::list<unsigned char> numerals;
   // integer part encoding
   int remainder=-1;
   while (true)
   {
       int division = integer_part / radix;
       remainder = integer_part % radix;
       integer_part = division;
       // emit to front
       if (integer_part == 0 and remainder == 0)
	   break;
       numerals.push_front(code[remainder]);
   }

   numerals.push_back('.');
   // fractional part encoding
   int numeral = -1;
   while (maxIter -- > 0)
   {
   
	fractional_part *= radix;
         numeral = (int) fractional_part;
	if (fabs(fractional_part) <0.00001 and numeral == 0)
	    break;
	fractional_part -= numeral;
	numerals.push_back(code[numeral]);
   }
   std::string ret;
   std::copy(numerals.begin(), numerals.end(), std::back_inserter(ret));
   return ret;
}


int main(int argc, char **argv)
{
    int radix;
    double number;
    if (argc != 2) {
	std::cerr << "Usage: ./ns <number>" << std::endl;
	return -1;
    }
	
    number = std::atof(argv[1]);   
    std::cout << "Hex:\t" << encode(number, "0123456789ABCDEF") << std::endl;
    std::cout << "Octal:\t" << encode(number, "01234567") << std::endl;
    std::cout << "Binary:\t" << encode(number, "01") << std::endl;
    return 0;
}
