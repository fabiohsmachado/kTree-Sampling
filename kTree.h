#ifndef KTREE_H
#define KTREE_H

#include <iterator>
#include <algorithm>
#include <iostream>

#include "codeWord.h"

class KTree
{
 public:
  CodeWord *cw;
		std::vector<std::vector<int>> *TK;
		std::vector<std::vector<int>> *RK;
		std::vector<std::vector<int>> *T;
		std::vector<int> *phi, *phi_1;
  int n, k, qBar, lM;
	 
  KTree(CodeWord cw);
  KTree(std::vector<std::vector<int>> TK, int k);
  ~KTree();

  std::vector<std::vector<int>>* Decode (CodeWord cw);
  CodeWord* Encode ();
  int setQBar (std::vector<int> Q);
		std::vector<int>* ComputePhi (std::vector<int> Q);
		std::vector<int>* ComputePhi_1 (std::vector<int>* phi);
  int setLM (std::vector<std::vector<int>> S, std::vector<int> *phi_1);
  std::vector<std::vector<int>> DandelionDecoding (std::vector<std::vector<int>> G, int r, int x);
  std::vector<int> Analyze (std::vector<std::vector<int>> G, std::vector<int> *mI, std::vector<int> status, int v);
  std::vector<std::vector<int>>* RebuildRK (std::vector<std::vector<int>>* T);
  std::vector<int> BreadthFirstOrder (std::vector<std::vector<int>>* T);
  std::vector<std::vector<int>>* ApplyPhi_1 (std::vector<std::vector<int>>* RK);
  std::vector<std::vector<int>>* ApplyPhi (std::vector<std::vector<int>>* TK);
  void PrintTK();
  void PrintRK();

  bool operator() (std::vector<int> A, std::vector<int> B)
  {
	  return A[0] < B[0];
  }
};

KTree::KTree (std::vector<std::vector<int>> TK, int k)
{
	this->n = TK.size();
 this->k = k;
 this->TK = &TK;

 this->cw = Encode();
}

KTree::KTree (CodeWord cw)
{
 Decode(cw);
}

KTree::~KTree()
{
 
}

CodeWord* KTree::Encode ()
{
	std::vector<int> Q;
 unsigned	int i, j;
 
 for(i = j = T->size() - 1; i != 0; i--, j--)
		if((*T)[i][j] == k)
			lM = i;

 for(i = 0; i < T->size(); i++)
  if((*T)[i][lM] == -1)
   Q.push_back(i + 1);

 phi = ComputePhi(Q);

 return NULL;
}

std::vector<std::vector<int>>* KTree::Decode (CodeWord codeword)
{
 int position;
 std::vector<std::vector<int>> *TK, T;

	std::cout << "Decoding: " << codeword.toString() << std::endl;

 this->cw = &codeword;
 this->n = cw->n;
 this->k = cw->k;
 std::sort(cw->Q.begin(), cw->Q.end());

 this->qBar = setQBar(cw->Q);
 this->phi = ComputePhi(cw->Q);
 this->phi_1 = ComputePhi_1(phi);
 this->lM = setLM(cw->S, phi_1);

	position = (*phi)[lM - 1];
 if(position > qBar) position--;
 cw->S.insert(cw->S.begin() + position - 1, std::vector<int>({0, -1}));	

 T = DandelionDecoding(cw->S, 0, (*phi)[qBar - 1]);
 this->T = &T;

 this->RK = RebuildRK(this->T);
 this->TK = ApplyPhi_1(RK);
 
 return TK;
}

/*
Compute the relabeling process phi, to transform a k-tree into a Renyi k-tree
Q must be in increasing order
*/
std::vector<int> *KTree::ComputePhi (std::vector<int> Q)
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

std::vector<int>* KTree::ComputePhi_1 (std::vector<int>* phi)
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
  else qBar++;
 }

 return qBar;
}

int KTree::setLM (std::vector<std::vector<int>> S, std::vector<int> *phi_1)
{
	std::vector<int> L(n-k+1, 0);
 std::vector<int>::iterator itVI;
 std::vector<std::vector<int>>::iterator itVVI;
 int i, lM;

 for(itVVI = S.begin(); itVVI != S.end(); ++itVVI)
  L[(*itVVI)[0]] = -1;

 lM = 0;
 for(itVI = L.begin() + 1; itVI != L.end(); ++itVI)
  if((*itVI == 0) && (lM < (*phi_1)[*itVI]))
   lM = (*phi_1)[*itVI];

 return lM;
}

std::vector<std::vector<int>> KTree::DandelionDecoding (std::vector<std::vector<int>> G, int r, int x)
{
	std::vector<int> status(n-k+1, 0);
	std::vector<int> *mI;
	std::vector<int>::iterator it;
 int i, j, swap;

 i = j = 0;
 for(i = 0; i < n-k+1; i++)
		if(i != r && i != x)
		{
			G[j].insert(G[j].begin(), i);
   j++;
		}
 G.insert(G.begin(), {x, r, -1});
	std::sort(G.begin(), G.end(), *this);

 mI = new std::vector<int>;
 status[0] = 2;
 for(i = 1; i < n-k+1; i++)
  status = Analyze(G, mI, status, i);

 if(!mI->empty())
 {
 	std::sort(mI->begin(), mI->end());
  for(it = mI->begin(); it != mI->end(); ++it)
  {
   swap = G[*it - 1][2];
   G[*it - 1][2] = G[x - 1][2];
   G[x - 1][2] = swap;
   
   swap = G[*it - 1][1];
   G[*it - 1][1] = G[x - 1][1];
   G[x - 1][1] = swap;
		}
	}

 return G;
}

/*
  Not Processed == 0;
  In Progress == 1;
  Processed == 2;
*/
std::vector<int> KTree::Analyze (std::vector<std::vector<int>> G, std::vector<int> *mI, std::vector<int> status, int v)
{
 int target, max;

 if(status[v] != 2)
 {
  status[v] = 1;
		if(status[G[v-1][1]] == 1)
  {
   max = v;
   target = v;
   while(G[target - 1][1] != v)
   {
    target = G[target - 1][1];
    if(max < target) max = target;				
			}
   mI->push_back(max);
		}
  else
   if(status[G[v-1][1]] != 2)
 			status = Analyze(G, mI, status, G[v-1][1]);
		
  status[v] = 2;
	}
 return status;
}

std::vector<std::vector<int>>* KTree::RebuildRK (std::vector<std::vector<int>>* T)
{
 std::vector<std::vector<int>>* RK;
 std::vector<std::vector<int>>* KV;
 std::vector<int> R(k+1, 0);
 std::vector<int> bfs;
 std::vector<int>::iterator itI, itJ;
 int i, j, v;

 RK = new std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
 KV = new std::vector<std::vector<int>>(n-k, std::vector<int>(k+1, 0));

 bfs = BreadthFirstOrder(T);

 for(i = 0; i < k; i++)
  R[i] = n - k + 1 + i;
 
 for(i = n-k; i < n; i++)
  for(j = i+1; j < n; j++)
  {
   (*RK)[i][j] = -1;
   (*RK)[j][i] = -1;
   (*RK)[i][i]++;
   (*RK)[j][j]++;
		}

 for(itI = bfs.begin(); itI != bfs.end(); itI++)
 {
		if((*T)[*itI-1][1] == 0)
  {
			(*KV)[*itI-1] = R;
   (*KV)[*itI-1].erase((*KV)[*itI-1].end() - 1);
		}
		else
  {
			(*KV)[*itI-1] = (*KV)[(*T)[*itI-1][1] - 1];
   (*KV)[*itI-1].erase((*KV)[*itI-1].begin() + (*T)[*itI-1][2] - 1);
			std::sort((*KV)[*itI-1].begin(), (*KV)[*itI-1].end());
		}

		(*KV)[*itI-1].push_back(*itI);
  for(itJ = (*KV)[*itI-1].begin(); itJ != (*KV)[*itI-1].end() - 1; ++itJ)
		{
   v = *((*KV)[*itI-1].end() - 1) - 1;
			(*RK)[v][*itJ-1] = -1;
   (*RK)[*itJ-1][v] = -1;
   (*RK)[v][v]++;
   (*RK)[*itJ-1][*itJ-1]++;
		}
	}

	return RK;
}

std::vector<int> KTree::BreadthFirstOrder (std::vector<std::vector<int>>* T)
{
 std::vector<std::vector<int>> TAdj(n-k+1, std::vector<int>(n-k+1, 0));
	std::vector<int> bfs;
	std::vector<int>::iterator it;
 int i, j, distance;

 for(i = 1; i <= n-k; i++)
		TAdj[i][(*T)[i - 1][1]] = 1;

 bfs.push_back(0);
 for(it = bfs.begin(); it != bfs.end(); ++it)
  for(j = 0; j <= n-k; j++)
   if(TAdj[j][*it] == 1)
	  {
    distance = std::distance(bfs.begin(), it);
 			bfs.push_back(j);
    it = bfs.begin() + distance;
 		}

	bfs.erase(bfs.begin());

 return bfs;
}

std::vector<std::vector<int>>* KTree::ApplyPhi_1 (std::vector<std::vector<int>>* RK)
{
 int i, j;
 std::vector<std::vector<int>>* TK;

 TK = new std::vector<std::vector<int>>(n, std::vector<int>(n, 0));

 for(i = 0; i < n; i++)
  for(j = 0; j < n; j++)
   (*TK)[(*phi_1)[i]-1][(*phi_1)[j]-1] = (*RK)[i][j];

 return TK;
}

std::vector<std::vector<int>>* KTree::ApplyPhi (std::vector<std::vector<int>>* TK)
{
 int i, j;
 std::vector<std::vector<int>>* RK;

 RK = new std::vector<std::vector<int>>(n, std::vector<int>(n, 0));

 for(i = 0; i < n; i++)
  for(j = 0; j < n; j++)
   (*RK)[(*phi)[i]-1][(*phi)[j]-1] = (*TK)[i][j];

 return RK;
}

void KTree::PrintTK()
{
 int i, j;

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
			std::cout << abs((*TK)[i][j]) << " ";
		std::cout << std::endl;
	}
}

void KTree::PrintRK()
{
 int i, j;

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
			std::cout << abs((*RK)[i][j]) << " ";
		std::cout << std::endl;
	}
}
#endif /* KTREE_H */
