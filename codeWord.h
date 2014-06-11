#ifndef CODEWORD_H
#define CODEWORD_H

#include <vector>
#include <string>
#include <sstream>
#include <iterator>

class CodeWord
{
 public:
	 std::vector<int> Q;
	 std::vector<std::vector<int>> S;
	 int n, k;

	 CodeWord(std::vector<int> Q, std::vector<std::vector<int>> S);
  ~CodeWord();

	 std::string toString();
	 std::string SToString();
	 std::string QToString();

  int assertS(const std::vector<std::vector<int>> S);
};

CodeWord::CodeWord(std::vector<int> Q, std::vector<std::vector<int>> S)
{
 k = Q.size();
 n = S.size() + k + 2;

#ifdef DEBUG
	if(assertS(S)) exit(1);
#endif

 this->Q = Q;
 this->S = S;
}

CodeWord::~CodeWord()
{
}

std::string CodeWord::toString()
{
	std::stringstream CWStream;
 CWStream << "(" << QToString() << "," << SToString() << ")" << std::endl;
 return CWStream.str();
}

std::string CodeWord::SToString()
{
	std::stringstream SStream;
	std::string SString;
 std::vector<std::vector<int>>::iterator it;
 
 SStream << "(";
 for(it = S.begin(); it != S.end(); ++it)
  SStream << "(" << (*it)[0] << "," << (*it)[1] << ")" << ",";
 SStream << ")";
 
 SString = SStream.str();
 SString.erase(SString.end()-2);
 return SString;
}

std::string CodeWord::QToString()
{
	std::stringstream QStream;
	std::string QString;

 QStream << "(";
	std::copy(Q.begin(), Q.end(), std::ostream_iterator<int>(QStream, ","));
 QStream << ")";
 
 QString = QStream.str();
 QString.erase(QString.end()-2);
 return QString;
}

int CodeWord::assertS(std::vector<std::vector<int>> S)
{
	std::vector<std::vector<int>>::iterator it;
 int error = 0;
 
 for(it = S.begin(); it != S.end(); ++it)
 {
  if((*it).size() != 2)
  {
			std::cerr << "Error: Each element of S must be a pair (node, label)." << std::endl;
   error = 1;
   break;
		}

  if((*it)[0] != 0 && (*it)[1] == -1)
  {
			std::cerr << "Error: Node 0 must only be associated with label -1." << std::endl;
   error = 1;
   break;
		}

		if((*it)[0] > (n - k))
  {
			std::cerr << "Error: Nodes in S cannot exceed n - k." << std::endl;
   error = 1;
   break;	
		}

		if((*it)[1] > k)
  {
			std::cerr << "Error: Labels in S cannot exceed k." << std::endl;
   error = 1;
   break;	
		}
	}

 return error;
}

#endif /* CODEWORD_H */
