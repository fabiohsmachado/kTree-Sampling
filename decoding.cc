#define DEBUG
#include <iostream>

#include "codeWord.h"
#include "kTree.h"
#include "treeSampler.h"

int main()
{
 int n = 11;
 int k = 3;
 TreeSampler TS(n, k);
 KTree *TK;

//	std::vector<int> Q ({2, 9, 3});
//	std::vector<std::vector<int>> S ({{0, -1}, {2, 1}, {8, 3}, {8, 2}, {1, 3}, {5, 3}});

	std::vector<int> Q ({4, 8, 1});
	std::vector<std::vector<int>> S ({{1, 1}, {5, 1}, {2, 2}, {7, 1}, {4, 1}, {7, 2}});

	for(int i = 0; i < 500; i++)
//  TK = new KTree(*(new CodeWord(Q, S)));
		TK = TS.SampleKTree();

// std::cout << TK->cw->toString() << std::endl; 
// TK->PrintTK();
 return 1;
}
