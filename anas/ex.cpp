#include <iostream>
#include "NuMIana.h"

int main()
{
  NuMIana my_ana("test_file.root");
  std::vector<double> test_vector = my_ana.vtxx();
  int counter = 0;
  std::vector<double>::iterator myitr = test_vector.begin();
  while ( counter < 20 ) {
    std::cout << (*myitr) << std::endl;
    myitr++;
    counter++;
  }
  return 0;
}
