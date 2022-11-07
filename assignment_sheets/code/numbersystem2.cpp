#include<iostream>
#include<list>
#include<string>
#include<math.h>
#include<iomanip>


double decode(std::string number, std::string code)
{
    double ret = 0;
   int radix = code.size();
   // find the exponent of the first character
   int radixpoint = number.find('.');
   if (radixpoint == std::string::npos) radixpoint = number.size();
   radixpoint --;
   double valuation = std::pow(radix, radixpoint);

   for (unsigned char ch: number)
   {
       auto value = code.find(ch);
       if (value == std::string::npos)
         continue;

	ret += value * valuation;
	valuation /= radix;
   }
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
	
/*    number = std::atof(argv[1]);   
    std::cout << "Hex:\t" << encode(number, "0123456789ABCDEF") << std::endl;
    std::cout << "Octal:\t" << encode(number, "01234567") << std::endl;
    std::cout << "Binary:\t" << encode(number, "01") << std::endl;*/
    std::cout << std::fixed << std::setprecision(19);
    std::cout << decode(argv[1],"0123456789ABCDEF") << std::endl;
    return 0;
}
