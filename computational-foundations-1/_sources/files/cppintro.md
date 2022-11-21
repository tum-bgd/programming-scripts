# The C and C++ Language

## Introduction

The C programming language is the earliest form of the C and C++ family of programming languages. Nowadays, plain C
is used in kernel programming (e.g., the Linux kernel), in long-established code bases (e.g. postgresql), and in very resource-constrained situations (e.g., embedded devices). It also presents a subset of modern C++ and (with very few incompatibilities), every modern C++ compiler will compile plain C source code without any issues.

C and C++ are compiled languages and the compilation process is decomposed into a few tasks and translations that
can run independetly from each other. A modern GUI will orchestrate these steps, but it is mandatory to understand
the translation procedure to some extent when learning C++.

To keep things simple, a C project typically contains a bunch of C (extension *.c) or C++ (extension *.cpp) files.
These contain source code which a *compiler* can translate to object code. Object code is a form of machine code which is not executable as it can be incomplete. In a second phase, all object codes are linked together with system libraries such that all missing symbols are either coming from one of the object files of the project (hence, from your source code) or from some libraries (either system or additional libraries).

In order to deal with the situation that your source code depends on functionality that is not available to the compiler, because it is in a different file or coming from the operating system libraries, the C system provides a second type of file in which only the *signature* of functions is defined. In this way, the compiler is able to generate code to understand the libraries contents (it is kind-of a table-of-contents) well enough to compile the object file without looking into the actual implementation.

Summarizing, we have C++ files (*.c, *.cpp) and header files (*.h, *.hpp) and we translate each soure code file (*.c, *.cpp) into an object file (*.o) in order link together all objects with libraries (*.o, *.lib) into an executable (*.exe on Windows, just a name on Linux).

With this theory, we are set to start learning the core language while already understanding a bit the files that we will create.

### Hello World
The following program is the first program you should learn and understand. It just prints out "Hello World" to the screen. We will provide four information aspects in this script: the source code file (C++), a Makefile (which contains the compiler arguments, at the moment just compiling, the output of compiling (could become interesting later) and the output of running the program (note that the first line is the invocation for the case we are later giving arguments). In the HTML version of this book, they are alternative with each other (tabs), in print, they are a bit lengthy, but in this way everything remains complete.

`````{tab-set}
````{tab-item} Source
```cpp
#include<stdio.h>

int main(void)
{
    printf("Hello World!\n");
    return 0;
}
```
````
````{tab-item} Makefile
```
all: 
	g++ -Wall -o 01_oldhelloworld 01_oldhelloworld.cpp
run: 
	./01_oldhelloworld
```
````
````{tab-item} Build Output
```
```
````
````{tab-item} Run Output
```
```
````
````` 

The file (like any other C++ files) first lists a few of header files to include (here stdio.h, defined in the POSIX standards, see <https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/stdio.h.html>.

From this library, we are relying on the printf function to just output a string.

C is an imperative language and instructs a computer step by step, the entry point (where this processing starts) is a special function called main (WinMain for Windows programs). Similar to what we have seen for the shell examples,
the n denotes a special character "new line" and makes sure that the program does not only output Hello World!, but also continues to the next line.

```{note}
There is a very traditional incompatibility between Windows and Linux with respect to new lines: The Linefeed (LF, n) is sufficient on Linux and Unix, but on Windows, lines are typically ending with CR-LF: first a carriage return (CR, r), then a line feed (n).
```

The printf function is a powerful utility you can find in all programming languages and it can format various values
into the output, what we will cover a bit later, but it has also some downsides, mainly with respect to security and
reliability. Hence, printf is not used that much in safety-oriented code.

### Hello C++ World

In contrast to C, C++ has introduced the concept of an iostream which better reflects the nature of the standard input and standard ouput. A stream is an object that can represent a file, a network connection, or just a terminal window and one can stream various information into it. Therefore, an operator << is implemented, which takes variables, strings, or whatever information. In this way, type conversion is safe and automatic.

In order to output data to the user, the C++ libraries define a header iostreams which define cout (C output), cerr (standard error output) and cin (for input, used with a >> stream operator).

Hence, the same program written in idiomatic C++ looks like this:

`````{tab-set}
````{tab-item} Source
```cpp
#include<iostream>

int main(void)
{
   std::cout << "Hello World!" << std::endl;
   return 0;
}
```
````
````{tab-item} Makefile
```
all: 
	g++ -Wall -o 00_helloworld.out 00_helloworld.cpp
run: 
	./00_helloworld.out
```
````
````{tab-item} Build Output
```
```
````
````{tab-item} Run Output
```
```
````
````` 

## Functions and Signature-based Selection

A little bit later, we will introduce many different types, but for now, we will look into how we can write our own functions similar to the printf functions. A function is a unit of code that can be reused in your own code. Let us consider the following already quite involved example:

`````{tab-set}
````{tab-item} Source
```cpp
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
```
````
````{tab-item} Makefile
```
all: 
	g++ -Wall -o 02_functionsignatures 02_functionsignatures.cpp
run: 
	./02_functionsignatures
```
````
````{tab-item} Build Output
```
```
````
````{tab-item} Run Output
```
```
````
````` 

While this example does not look that much more complicated, we introduced many aspects that are difficult to understand. Let us unroll it a bit. In C++, we are allowed to define multiple functions to have the same name. This is particularly wanted, because sometimes, we can implement an algorithm just different if the arguments are of different types. In our example, we define two times a double function, once it takes an integer argument (int, more on types later, it is just an integral number) or a fractional number (float).

The compiler selects the right function in a complex procedure: For the first call, `doubled(4)`, the type of the constant 4 is integer; hence, the system decides that the first function `int doubled(int)` should be called. For the second call, we have a problem: if we remove the f from the argument, the compiler will tell us the call is ambiguous. What the compiler actually means in this situation is that there is no function that strictly fits to the type (4.5 will be considered a double value in the first place, not a float value, more on this later). Hence, the compiler would generate code and covert the double into an integer if only the first function would exist, it would convert the value into a float if only the second variant would exist. But the compiler has no precedence and raises an error. We resolved this by using a literal: for many constants, the type can be influenced by putting a character to the constant: 4.5f just means the value 4.5 as a floating point number of the type `float`.

## Code Libraries

In many situations, we will implement functions that we want to use from multiple programs. For example, we could implement a sort function and use it in many different programs if we need to sort. In this situation, we need to put our implementations into an isolated C++ file, create a header file with the so-called *function prototypes* which are just fixing the name of the function and the type of the return value and of all arguments. In this way, we can include the header in our own program (one which has a main), generate code using the functions in the compilation step, and then link together our program with the library into a proper executable.

More concretely, we could move the two implementations of the `doubled` functions into their own C++ file:

`````{tab-set}
````{tab-item} Library
```

int doubled(int a)
{
   return (a*2);
}

float doubled(float a)
{
   return (a*2);
}
```
````
````` 

This one can now be compiled independently from everything else. Note that we do not even include iostream here, because we are not using anything from iostreams. In order to make this available, we formualte a header

`````{tab-set}
````{tab-item} Header
```
#ifndef DOUBLED_H_INC
#define DOUBLED_H_INC
int doubled(int a);
float doubled(float a);
#endif
```
````
````` 

which contains the signature lines of the functions only (ending with a semicolon). It is valid, but not very widely
used to only give the types of the arguments such as
```
float doubled (float);
```

In order to make sure that these definitions cannot be loaded twice (not really needed here, but problems will be coming) all of this header is protected from double inclusion using the preprocessor. All lines with # are processed even before compiling and in order to avoid a double include (maybe you are including the file directly, but some library you include also includes this header) we check if a symbol specific to the header (it is common to use the capitalized filename as depicted) and if not, we define it (such that it is defined in the sequel) and close with `#endif` at end of file. In modern C++, this can be replaced with a simple `#pragma once` in the beginning, but this is not that widely used today.

The remaining project then looks like this:

`````{tab-set}
````{tab-item} Source
```cpp
#include<iostream>
#include "03_doubled.h"

int main(void)
{
   std::cout << "doubled(4)=" << doubled(4) << std::endl
             << "doubled(4.5)=" << doubled(4.5f) << std::endl;

   return 0;
}
```
````
````{tab-item} Makefile
```
all:
	g++ -c 03_doubled.cpp -o 03_doubled.o
	g++ -c 03_library.cpp -o 03_library.o
	g++ -o 03_library 03_library.o 03_doubled.o
run: 
	./03_library
```
````
````{tab-item} Build Output
```
```
````
````{tab-item} Run Output
```
```
````
````` 

A small thing to note here is that the include uses " instead of < and >. This is an old relict and refers to being able to include from the current directory. Libraries to be included from the compiler default location are included with <> and things local to the project with "".

Especially the Makefile (*.mk) is interesting here as I spelled out all three steps for you: compiling (-c) the library, then compiling the main program part. Afterwards linking together the object files into an executable.




