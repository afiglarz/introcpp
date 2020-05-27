#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>

int main( int argc, char **argv )
{
  uint64_t aflag = 0;
  uint64_t bflag = 0;
  std::string cvalue = "Hello";
  
  static const char options[] {"abc:"};
  int c{};
  
  while ((c = getopt(argc, argv, options)) != -1) 
    switch (c)
      {
      case 'a':
	aflag = 1;
	break;
      case 'b':
	bflag = 1;
	break;
      case 'c':
	cvalue = optarg;
	break;
      case '?':
	std::cout <<
	  "Please only use the '-a, -b or -c' flags \n";
	return 1;
      default:
	abort();
      }

  //Print flag values 0 if unchanged, 1 if flag was used
  //Print the string given to c flag, print "Hello" if unused

  std::cout << "aflag is " << aflag << std::endl;
  std::cout << "bflag is " << bflag << std::endl;
  std::cout << "cflag is " << cvalue << std::endl;

  return 0;
}

