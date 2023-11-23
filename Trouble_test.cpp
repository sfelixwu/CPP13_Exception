// Ex15_03.cpp
// Throw an exception object
#include <iostream>
#include "Trouble.h"

// try { some code <throw> <object> or int  } catch(one paramter) { 2nd code }

void foo(char *error_msg)
{
  throw Trouble {error_msg}; // i == 0
}

int main()
{
  for (int i {}; i < 2; ++i)
    {
      try
	{
	  if (i == 0)
	    foo("default i = 0");
	  else                // i == 1
	    foo("Nobody on Piaaza knows the trouble I've experienced...");
	}
      catch(const int t)
	{
	  std::cout << "Exception\n";
	}
    }
}
