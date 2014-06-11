#ifndef KTREE_H
#define KTREE_H

#include <iterator>
#include <algorithm>

#include "codeWord.h"

class KTree
{
 public:
  CodeWord *cw;
		std::vector<std::vector<int>> T;
		std::vector<int> *phi, *phi_1;
  int n, k, qBar, lM;
	 
  KTree(int n, int k);
  KTree(CodeWord& cw);
  KTree(std::vector<std::vector<int>> T, int k);
  ~KTree();

  int Decode(CodeWord *cw);
  CodeWord* Encode();

  int setQBar(std::vector<int> Q);
		std::vector<int> *ComputePhi(std::vector<int> Q);
		std::vector<int> *ComputePhi_1(std::vector<int>* phi);
  int setLM(std::vector<std::vector<int>> S, std::vector<int> *phi_1);
  std::vector<std::vector<int>> DandelionDecoding(std::vector<std::vector<int>> S, int r, int x);
  std::vector<int>  analyze(std::vector<std::vector<int>> G, std::vector<int> mI, std::vector<int> status, int v);

  bool operator() (std::vector<int> A, std::vector<int> B)
  {
	  return A[0] < B[0];
  }
};

KTree::KTree(int n, int k)
{
	this->n = n;
 this->k = k;
}

KTree::KTree(CodeWord& cw)
{
 this->cw = &cw;
 this->n = cw.n;
 this->k = cw.k;

 Decode(this->cw);
}

KTree::KTree(std::vector<std::vector<int>> T, int k)
{
	this->n = T.size();
 this->k = k;
 this->T = T;

 this->cw = Encode();
}

KTree::~KTree()
{
 
}

CodeWord* KTree::Encode()
{
	std::vector<int> Q;
 unsigned	int i, j;
 
 for(i = j = T.size() - 1; i >= 0; i--, j--)
		if(T[i][j] == k)
			lM = i;

 for(i = 0; i < T.size(); i++)
  if(T[i][lM] == -1)
   Q.push_back(i + 1);

 phi = ComputePhi(Q);
}

int KTree::Decode(CodeWord *cw)
{
 int position;
 std::vector<std::vector<int>> T;

 std::sort(cw->Q.begin(), cw->Q.end());

 qBar = setQBar(cw->Q);
 phi = ComputePhi(cw->Q);
 phi_1 = ComputePhi_1(phi);
 lM = setLM(cw->S, phi_1);

	position = (*phi)[lM - 1];
 if(position > qBar) position--;
 cw->S.insert(cw->S.begin() + position - 1, {0, -1});	

 T = DandelionDecoding(cw->S, 0, (*phi)[qBar - 1]);
 
//	std::cout << "****" << T[0][1] << T[7][1] << "****" << std::endl;
 return 1;
}

/*
Compute the relabeling process phi, to transform a k-tree into a Renyi k-tree
Q must be in increasing order
*/
std::vector<int> *KTree::ComputePhi(std::vector<int> Q)
{
	std::vector<int> *phi;
	std::vector<int>::iterator it;
 int i, j;

 phi = new std::vector<int> (n, 0);

 i = 1;
 for(it = Q.begin(); it != Q.end(); ++it)
		(*phi)[*it - 1] = n - k + i++;

 for(i = 1; i <= n-k; i++)
 {
  j = i;
		while((*phi)[j - 1] != 0)
   j = (*phi)[j  - 1];
  (*phi)[j - 1] = i;
	}
  
 return phi;
}

std::vector<int>* KTree::ComputePhi_1(std::vector<int>* phi)
{
	std::vector<int> *phi_1;
	std::vector<int>::iterator it;
 int i;

 phi_1 = new std::vector<int> (n, 0); 

 i = 1;
 for(it = phi->begin(); it != phi->end(); ++it)
		(*phi_1)[*it - 1] = i++;
 
 return phi_1;
}

int KTree::setQBar(std::vector<int> Q)
{
 int qBar;
 std::vector<int>::iterator it;

 qBar = 1;
 for(it = Q.begin(); it != Q.end(); ++it)
 {
  if(qBar < *it) break;
   qBar++;
 }

 return qBar;
}

int KTree::setLM(std::vector<std::vector<int>> S, std::vector<int> *phi_1)
{
	std::vector<int> L;
 std::vector<int>::iterator itVI;
 std::vector<std::vector<int>>::iterator itVVI;
 int i, kLeaf, lM;

 for(itVVI = cw->S.begin(); itVVI != cw->S.end(); ++itVVI)
  L.push_back((*itVVI)[0]);

	std::sort(L.begin(), L.end());

 i = 1;
 lM = 0;
 for(itVI = L.begin() + 1; itVI != L.end(); ++itVI)
 {
		if(i < *itVI)
  {
   kLeaf = (*phi_1)[i- 1];
   if(lM < kLeaf)
    lM = kLeaf;
   i++;
		}
  else
  {
			i++;
   while((itVI != L.end()) && (*itVI == *itVI + 1))
    itVI++;
		}
 }
 
 return lM;
}

std::vector<std::vector<int>>  KTree::DandelionDecoding(std::vector<std::vector<int>> S, int r, int x)
{
	std::vector<int> status(n-1, 0);
	std::vector<int> mI;
	std::vector<int>::iterator it;
 int i, j, swap;

 i = j = 0;
 for(i = 0; i < n-2; i++)
		if(i != r && i != x)
		{
			 S[j].insert(S[j].begin(), i);
   j++;
		}
 S.insert(S.begin() + x - 1, {0, -1});
 S[0].insert(S[0].begin(), x);

	std::sort(S.begin(), S.end(), *this);
   
/* for(i = 0; i < n-1; i++)
  status = analyze(S, mI, status, i);

 if(!mI.empty())
 {
 	std::sort(mI.begin(), mI.end());
  for(it = mI.begin(); it != mI.end(); ++it)
  {
   swap = S[*it][2];
   S[*it][2] = S[x][2];
   S[x][2] = swap;
   
   swap = S[*it][1];
   S[*it][1] = S[x][1];
   S[x][1] = swap;
		}
	}
*/
 return S;
}

/*
  Not Processed == 0;
  In Progress == 1;
  Processed == 2;
*/
std::vector<int>  KTree::analyze(std::vector<std::vector<int>> G, std::vector<int> mI, std::vector<int> status, int v)
{
 int target, max;

 if(status[v - 1] != 2)
 {
  status[v - 1] = 1;
  if(status[G[v - 1][1]] == 1)
  {
   max = v;
   target = v;
   while(G[target - 1][1] != v)
   {
    target = G[target - 1][1];
    if(max < target) max = target;				
			}
   mI.push_back(max);
		}
  else
			analyze(G, mI, status, G[v-1][1]);
 
  status[v] = 2;
	}
 return status;
}

#endif /* KTREE_H */
