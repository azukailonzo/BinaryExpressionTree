#ifndef _STACK_H
#define _STACK_H
#include <iostream>
#include <vector>

namespace cop4530 {

	template< typename T >
        class Stack {
	  private:
		std::vector< T > v;
	  public:
		Stack();
		~Stack();
		Stack(const Stack<T>&);
		Stack(Stack<T> &&);
		Stack<T>& operator=(const Stack<T>&);
		Stack<T>& operator=(Stack<T> &&);
		bool empty() const;
		void clear();
		void push(const T& x);
		void push(T && x);
		void pop();
		T& top();
		const T& top() const;
		int size() const;
		void print(std::ostream& os, char ofc = ' ') const;

		template < typename Object >
		friend bool operator== (const Stack<Object>&, const Stack <Object>&);

		template < typename Object >
		friend bool operator!= (const Stack<Object>&, const Stack <Object>&);

		template < typename Object >
		friend bool operator<= (const Stack<Object>& a, const Stack <Object>& b);

	};
		template < typename T >
                std::ostream& operator<< (std::ostream& os, const Stack<T>& a);

#include "stack.hpp"

} //end of namespace

#endif
