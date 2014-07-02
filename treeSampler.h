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
  ~TreeSampler();
 
  CodeWord* SampleCodeWord();
  KTree* SampleKTree();
};

TreeSampler::TreeSampler(int n, int k)
{
	this->n = n;
 this->k = k;
}

TreeSampler::~TreeSampler()
{
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
	std::uniform_int_distribution<int> *QDist;
	std::uniform_int_distribution<int> SDistNode(0, n-k);
	std::uniform_int_distribution<int> SDistLabel(1, k);

 for(i = 1; i <= n; i++)
  v[i-1] = i;

 for(i = 0; i < k; i++)
 {
  QDist = new std::uniform_int_distribution<int>(0, n-i-1);
  r = (*QDist)(gen);
  Q[i] = v[r];
  v.erase(v.begin() + r);
	}
 
 for(i = 0; i < n-k-2; i++)
	{
		r = SDistNode(gen);
  if(r == 0)
  {
   S[i][0] = 0;
			S[i][1] = -1;
		}
  else
  {
   S[i][0] = r;
   r = SDistLabel(gen);
		 S[i][1] = r;
 	}
 }

	cw = new CodeWord(Q, S);
 return cw;
}

KTree* TreeSampler::SampleKTree()
{
 return new KTree(*SampleCodeWord());
}

#endif /*TREESAMPLER_H*/
