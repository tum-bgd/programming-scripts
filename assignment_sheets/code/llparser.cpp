#include<iostream>


using namespace std;

char *ptoken;
int where = 0;
char token()
{
   return *ptoken;
}
bool nexttoken()
{
    ptoken ++;
    where ++;
    if (*ptoken == '\0')
       return false;
    return true;
}

void expression();

void identifier(){
    cout << "Identifier at " << where << std::endl;

   if (token() == 'a' || token() == 'b')
   {
	nexttoken();
	std::cout << "PARSED IDENTIFIER a or b" << std::endl;
   }else
    throw(std::runtime_error("identifier not a or b"));
}

void term()
{
    cout << "Term at " << where << std::endl;
    if (token() == '(')
    {
        nexttoken();
	expression();
	if (token() != ')') throw std::runtime_error("Expected )");
	nexttoken(); 
    }else
       identifier();
}

void expression()
{
// this is an iterative version of the left-recursive rule to avoid infinite loop
// analyze this change
// the modified grammar rule is expression--> Term { + Term}* where {*} denotes that this can happen as often as possible
// more down to Earth, this means we cut off the left-most Term and continue as long as there are some terms.
cout << "Expression at " << where << std::endl;
term(); // this is exactly, where we cut off
while (token() == '+')
{
    nexttoken(); 
    term();
}

}



int main(void){
   string expr;
   cout << "Expression: ";
   cin >> expr;
   ptoken = &expr[0];
   expression();
   return 0;
}
