#include <iostream>
#include <string>
using namespace std;

   class BET {
      private:
         struct BinaryNode {
	    string element;
	    BinaryNode *left;
	    BinaryNode *right;

	   BinaryNode(const string& theElement, BinaryNode *lt, BinaryNode *rt)
		: element{theElement}, left{lt}, right{rt} {}

	   BinaryNode(string && theElement, BinaryNode *lt, BinaryNode *rt)
		: element{std::move(theElement)}, left{lt}, right{rt} {}
 
         };

      public:
         BET();
         BET(const string& postfix);
         BET(const BET&);
         ~BET();
         bool buildFromPostfix(const string& postfix);
         const BET & operator= (const BET &);
	 void printInfixExpression() const;
	 void printPostfixExpression() const;
	 size_t size() const;
	 size_t leaf_nodes() const;
	 bool empty() const;

      private:
	 BinaryNode* root;
	 void printInfixExpression(BinaryNode *n) const;
	 void makeEmpty(BinaryNode* &t);
	 BinaryNode* clone(BinaryNode *t);
	 void printPostfixExpression(BinaryNode *n) const;
	 size_t size(BinaryNode *t) const;
	 size_t leaf_nodes(BinaryNode *t) const;
         bool checkPostfix(const string& postfix) const;
         bool isoperator(const string& x) const;
         bool precedenceLeft(const string& x, const string& y) const;
         bool precedenceRight(const string& x, const string& y) const;
   };
