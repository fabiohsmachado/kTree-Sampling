#define DEBUG
#include <iostream>

#include "codeWord.h"
#include "kTree.h"

int main()
{
	std::vector<int> Q ({2, 9, 3});
	std::vector<std::vector<int>> S ({{0, -1}, {2, 1}, {8, 3}, {8, 2}, {1, 3}, {5, 3}});
 
	CodeWord cw(Q, S);
 KTree T(cw);

 std::cout << cw.toString() << std::endl; 
 T.PrintTK();
 return 1;
}
