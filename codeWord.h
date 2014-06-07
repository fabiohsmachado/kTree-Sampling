#ifndef CODEWORD_H
#define CODEWORD_H

#include <vector>

class CodeWord
{
 public:
	 std::vector<int> *Q;
	 std::vector<std::vector<int>> S;
	 int n, k;

	 CodeWord(const std::vector<int>& Q, const std::vector<std::vector<int>>& S);
  CodeWord(int n, int k);
  ~CodeWord();

	 std::string toString();
	 std::string SToString();
	 std::string QToString();
};

#endif /* CODEWORD_H */
