//Binary Expression Tree implementation
//
//

#include "bet.h"
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <sstream>

using namespace std;

BET::BET() {
   root = nullptr;
}

BET::BET(const string& postfix) {
   if( checkPostfix(postfix) ){
      stack< BinaryNode*, vector<BinaryNode*> > Stack;
      stringstream ss(postfix);
      string read;

      while(ss >> read){
         if( !isoperator(read) ){
            BinaryNode* t = new BinaryNode{ read, nullptr, nullptr };
            Stack.push(t);
         } else{
            BinaryNode* rightChild = Stack.top();
            Stack.pop();
            BinaryNode* leftChild = Stack.top();
            Stack.pop();
            BinaryNode* op = new BinaryNode{ read, leftChild, rightChild };
            Stack.push(op);
         }
      }//end while
      root = Stack.top();

   } else{
      std::cout << "Error: invalid postfix expression." << endl;
   }
}

BET::BET(const BET& x) : root{nullptr} {
   root = clone( x.root );
}

BET::~BET() {
   makeEmpty( root ); 
}

bool BET::buildFromPostfix(const string& postfix) {
   if( checkPostfix(postfix) ){
      if( !empty() )
         makeEmpty( root );
     
      stack< BinaryNode*, vector<BinaryNode*> > Stack;
      stringstream ss(postfix);
      string read;

      while(ss >> read){
         if( !isoperator(read) ){
            BinaryNode* t = new BinaryNode{ read, nullptr, nullptr };
            Stack.push(t);
         } else{
            BinaryNode* rightChild = Stack.top();
            Stack.pop();
            BinaryNode* leftChild = Stack.top();
            Stack.pop();
            BinaryNode* op = new BinaryNode{ read, leftChild, rightChild };
            Stack.push(op);
         }
      }//end while
      root = Stack.top();
      return true;
   } else{
      std::cout << "Error: invalid postfix expression." << endl;
      return false;
   }
}

const BET & BET::operator= (const BET& x) {
   if( this != &x ){
      makeEmpty( this->root );
      this->root = clone( x.root );
      return *this;
   }
   return *this;
}

void BET::printInfixExpression() const {
   printInfixExpression( root );
}

void BET::printPostfixExpression() const {
   printPostfixExpression( root );
}

size_t BET::size() const {
   size( root );
}

size_t BET::leaf_nodes() const {
   leaf_nodes( root );
}

bool BET::empty() const {
   if( root == nullptr )
      return true;
   return false;
}

//PRIVATE HELPER FUNCTIONS
//
//

void BET::printInfixExpression(BinaryNode *n) const {
   bool check = false;								//check when to add parenthesis

   if( n != nullptr ) {
      if( n->left != nullptr && isoperator( n->left->element ) ){
         if( precedenceLeft(n->element, n->left->element) ){			//if precedence of parent op is higher
            std::cout << "( ";
            check = true;
         }
      }
      printInfixExpression(n->left);

      if(check == true){
         std::cout << ") ";
         check = false;
      }

      std::cout << n->element << " ";
      if( n->right != nullptr && isoperator( n->right->element ) ){
         if( precedenceRight(n->element, n->right->element) ){
            std::cout << "( ";
            check = true;
         }
      }
      printInfixExpression(n->right);

      if(check == true){
         std::cout << ") ";
         check = false;
      }
   }
}

void BET::makeEmpty(BinaryNode* &t) {
   if( t != nullptr )
   {
      makeEmpty( t->left );
      makeEmpty( t->right );
      delete t;
   }
   t = nullptr;
}

BET::BinaryNode* BET::clone(BinaryNode *t) {
   if( t == nullptr )
      return nullptr;
   else
      return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
}

void BET::printPostfixExpression(BinaryNode *n) const {
   if( n != nullptr ) {
      printPostfixExpression(n->left);
      printPostfixExpression(n->right);
      std::cout << n->element << " ";
   }
}

size_t BET::size(BinaryNode *t) const {
   if( t == nullptr )									
      return 0;
   else {
      return( size(t->left) + size(t->right) + 1 );					//get size of left and right subtrees + 1 for the parent node
   }
}

size_t BET::leaf_nodes(BinaryNode *t) const {
   size_t number = 0;
   if( t->left == nullptr && 
      t->right == nullptr )
      return 1;										//node has no children
   else{
      if( t->left != nullptr )   
         number = number + leaf_nodes(t->left);
      if( t->right != nullptr )
         number = number + leaf_nodes(t->right);
   }
   return number;   
}

bool BET::checkPostfix(const string& postfix) const {
   stringstream ss(postfix);
   string read;
   int stackCount = 0;
   while(ss >> read){
      char c = read[0];
      if( isalnum(c) )
         stackCount = stackCount + 1;								//operands are pushed to stack
      else{
         stackCount = stackCount - 2;								//operands popped from stack
         if(stackCount < 0 )
            return false;									//not enough operands
         else
            stackCount = stackCount + 1;							//push result onto stack
      }
   }
   if( stackCount == 1 )
      return true;
   else
      return false;										//too many or too few arguments
}

bool BET::isoperator(const string& x) const {
   if(x == "+" || x == "-" || x == "*"
      || x == "/")
      return true;
   return false;
}  

//parent op is x, child op is y
bool BET::precedenceLeft(const string& x, const string& y) const {
   if(x == "+" || x == "-")
      return false;
  
   if(x == "*" || x == "/"){
      if(y == "+" || y == "-")
         return true;
      if(y == "*" || y == "/")
         return false;
   }      
}

//parent op is x, child op is y
bool BET::precedenceRight(const string& x, const string& y) const {
   if(x == "+" || x == "-"){
      if(y == "+" || y =="-")
         return true;
      return false;
   }

   if(x == "*" || x == "/")
      return true;
}
