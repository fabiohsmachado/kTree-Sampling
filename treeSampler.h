#ifndef TREESAMPLER_H
#define TREESAMPLER_H

#include <random>
#include <cmath>

#include "codeWord.h"
#include "kTree.h"

class TreeSampler
{
 public:
  int n, k;

	TreeSampler(int n, int k);
 
 CodeWord* SampleCodeWord();
 KTree* SampleKTree();
};

TreeSampler::TreeSampler(int n, int k)
{
	this->n = n;
 this->k = k;
}

CodeWord* TreeSampler::SampleCodeWord()
{
 CodeWord *cw;
	std::vector<int> Q(k, 0);
 std::vector<std::vector<int>> RK(n, std::vector<int>(n, 0));
	std::vector<std::vector<int>> S(n-k-2, std::vector<int>(2, 0));
	std::vector<int> v (n, 0);
 int i, r;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> *QDis;
	std::uniform_int_distribution<> SDisNode(0, n-k);
	std::uniform_int_distribution<> SDisLabel(1, k);

 for(i = 1; i <= n; i++)
  v[i-1] = i;

 for(i = 0; i < k; i++)
 {
  QDis = new std::uniform_int_distribution<>(0, n-i-1);
  r = (*QDis)(gen);
  Q[i] = v[r];
  v.erase(v.begin() + r);
	}
 
 for(i = 0; i < n-k-2; i++)
	{
		r = SDisNode(gen);
  if(r == 0)
  {
   S[i][0] = 0;
			S[i][1] = -1;
		}
  else
   S[i][0] = r;
   r = SDisLabel(gen);
		 S[i][1] = r;
 	}

	std::cout << cw->toString() << std::endl;
	cw = new CodeWord(Q, S);
 return cw;
}

KTree* TreeSampler::SampleKTree()
{
 return new KTree(*SampleCodeWord());
}
#endif /*TREESAMPLER_H*/
