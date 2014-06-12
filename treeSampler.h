#ifndef TREESAMPLER_H
#define TREESAMPLER_H

#include "codeWord.h"
#include "kTree.h"

class TreeSampler
{
 public:
  int n, k;

	TreeSampler(int n, int k);
 
 CodeWord SampleCodeWord();
 KTree SampleKTree();
}

TreeSampler::TreeSampler(int n, int k);
{
	this->n = n;
 this->k = k;
}

CodeWord SampleCodeWord()
{
	CodeWord *cw;

  

 return cw;
}

KTree SampleKTree()
{
	return new KTree(SampleCodeWord());
}
#endif /*TREESAMPLER_H*/
