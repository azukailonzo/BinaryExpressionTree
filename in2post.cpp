#include "stack.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
using namespace cop4530;

bool precedence(string x, string y);
bool isoperand(string x);
bool isopenbracket(string x);
bool isoperator(string x);
bool iscbracket(string x);
bool isfloat(string x);
string postEval(float x, float y, string op);
string postEval(int x, int y, string op);

int main() {

        Stack<string> opStack;                                                  	//store operators in this stack
        string read;                                                            	//read each operand/operator
        string line;                                                            	//get the infix expression from input
        string expression;                                                      	//store the postfix expression
        bool op = false;                                                        	//check if last input was an operator
        vector<string> v;                                                       	//to hold tokens in infix expression

	while(!cin.eof()) {

	   cout << "Enter infix expression (\"exit\" to quit):" << endl;
           getline(cin, line);                                                          //get expression
           if(line == "exit")
              break;

           stringstream ss(line);
           if(!v.empty())
              v.clear();                                                                //clear vector
           expression = "";                                                             //clear expression
           op = false;                                                                  //reset bool op

           while(ss >> read)
              v.push_back(read);


	   int i = 0;
           for(; i < v.size(); i++) {
	   //CHECK IF OPERAND
	   if( isoperand(v[i]) )
		expression = expression + " " + v[i];                                	//write down operand

	   //CHECK IF (
	   if( isopenbracket(v[i]) )
	      opStack.push(v[i]);

	   //CHECK IF )
	   if( iscbracket(v[i]) && op == true) {
	      cout << "Error: no operand given before ) " << endl;
	      break;
           }
	   if( iscbracket(v[i]) && op == false) {
	      while( !opStack.empty() && opStack.top() != "(" ) {
                 expression = expression + " " + opStack.top();
                 opStack.pop();
	      }//end while
	      if( !opStack.empty() )
	         opStack.pop();
              else{
                 cout << "Error: no matching ( bracket found " << endl;
		 break;
              }
	   } //end if

	   //CHECK IF OPERATOR
	   if( isoperator(v[i]) ) {
	      while( !opStack.empty() && opStack.top() != "(" ) {
	         if( precedence( opStack.top(), v[i] ) ) {
                         expression = expression + " " + opStack.top();
                         opStack.pop();
                 }
                 else
                    {break;}
	      } //end of while
	      opStack.push(v[i]);
	   } //end of if

	   //CHECK IF LAST INPUT IS OPERATOR
	   if( isoperator(v[i]) )
	      op = true;
	   else
	      op = false;

	} //end of for
	
	//END OF INPUT EXPRESSION
	if( i == v.size() && (op == true || v[v.size()-1] == "(") ) {
           cout << "Error: cannot have an operator or ( as last token in expression " << endl;    
           continue;												//stop processing
        }
        if( i == v.size() && op == false && v[v.size()-1] != "(" ) {
	   while( !opStack.empty() && opStack.top() != "(" ) {
	      expression = expression + " " + opStack.top();
              opStack.pop();
	   } //end while

	   if( !opStack.empty() ) {
	      cout << "Error: missing ) bracket " << endl;							//stop processing
	      continue;
	   } else {
              cout << "Postfix expression: " << expression << endl;
	      
	      //CHECK FOR EVALUATION
	      string temp;
	      bool evaluate = true;
	      stringstream is(expression);
              while(is >> temp) {
                 char c = temp[0];
                 if( isalpha(c) )
		    evaluate = false;
	      }//end of while
	      
              if( evaluate == false ) {
	         cout << "Postfix evaluation: " << expression << " = " << expression << endl;
		 continue;
              }

	      //EVALUATE NUMERIC EXPRESSION
	      string token;
              stringstream os(expression);
              Stack<string> operandStack;
	      vector<string> v2;

              while(os >> token)
	         v2.push_back(token);
	     
              int j = 0;
              for(; j < v2.size(); j++){
                 if( !isoperator(v2[j]) )
                    operandStack.push(v2[j]);
                 if( isoperator(v2[j]) ) {
                    if( operandStack.size() < 2 ){
        	       cout << "Error: " << v2[j] << " is a binary operator " << endl;
        	       break;
		    } else{
		       string string1 = operandStack.top();
		       operandStack.pop();
		       string string2 = operandStack.top();
	               operandStack.pop();
                       bool type = false;       
                        		
                       if( isfloat(string1) )
 		          type = true;
                       if( isfloat(string2) )
			  type = true;

		       if( type == true ){							//at least one operand is float
			  auto value1 = stof(string1);
			  auto value2 = stof(string2);
			  operandStack.push( postEval(value2,value1,v2[j]) );

                       } else{									//both operands are integers
                          auto value1 = stoi(string1);
                          auto value2 = stoi(string2);
			  operandStack.push( postEval(value2,value1,v2[j]) );
                       }
                    }
                 }//end of if     
	      }//end for loop
	     
	      //END OF EVALUATION
	      if( j == v2.size() && operandStack.size() > 1 )
                 cout << "Error: too many operands given " << endl;
              if( j == v2.size() && operandStack.empty() )
		 cout << "Postfix evaluation: " << expression << " = " << "0" << endl;
              if( j == v2.size() && operandStack.size() == 1) {
	         auto eval = operandStack.top();
                 operandStack.pop();
                 cout << "Postfix evaluation: " << expression << " = " << eval << endl;
              }
	   }// end of else

	} //end of if

	} // end of big while

} //end of main

//opStack.top() is x, v[i] is y
//true to remove from stack
bool precedence(string x, string y) {
	if( x == "+" || x == "-" ){
	   if(y == "+" || y == "-")
	      return true;
           if(y == "*" || y == "/")
	      return false;
	}

	if( x == "*" || x == "/" ) {
	   if(y == "+" || y == "-")
	      return true;
	   if(y == "*" || y == "/")
	      return true;
	}
}

//true if an operand
bool isoperand(string x) {
	if( x != "+" && x != "-" && x != "*" && x != "/"
                  && x != "(" && x != ")" )
	   return true;
	return false;
}

//true if (
bool isopenbracket(string x) {
	if( x == "(" )
	   return true;
	return false;
}

//true if operator
bool isoperator(string x) {
	if( x == "+" || x == "-" || x == "*" || x == "/" )
	   return true;
	return false;
}

//true if )
bool iscbracket(string x) {
	if( x == ")" )
	   return true;
	return false;
}

//true if number is float
bool isfloat(string x) {
	auto found = x.find(".");
	if (found != std::string::npos)
		return true;
	else
		return false;
}

//evaluate floats
string postEval(float x, float y, string op) {
	if(op == "+")
           return to_string(x + y);
        else if(op == "-")
	   return to_string(x - y);
        else if(op == "*")
	   return to_string(x * y);
        else
           return to_string(x / y);
}

//evaluate integers
string postEval(int x, int y, string op) {
	if(op == "+")
           return to_string(x + y);
        else if(op == "-")
           return to_string(x - y);
        else if(op == "*")
           return to_string(x * y);
        else
           return to_string(x / y);
}
