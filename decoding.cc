#include <iostream>

#include "codeWord.h"

int main()
{
	std::vector<int> Q ({1, 2, 3});
	std::vector<std::vector<int>> S ({{1, 2}, {1, 4}});
 
	CodeWord cw(Q, S);

 std::cout << cw.toString() << std::endl;
 return 1;
}
