#include <iostream>
#include <fstream>

int main()
{
  int read_it;
  std::string read_str;
  std::ifstream in_file;
  in_file.open("ppmediumCodes.dat");
  while ( in_file >> read_it >> read_str ) std::cout << read_it << " " << read_str << std::endl;

  return 0;
}
