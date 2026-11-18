#include <foodcalc.h>
#include <iostream>
#include <cstring>

int main()
{
	fc::Student s("Иванов Иван Иванович");

	std::cout << s.get_name() << std::endl;
	std::cout << strlen(s.get_name()) << std::endl;
}