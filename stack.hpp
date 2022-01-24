//Stack implementation file
//
//

template < typename T >
Stack< T >::Stack() {

}

template < typename T >
Stack< T >::~Stack() {
	v.clear();	
}

template < typename T >
Stack< T >::Stack(const Stack<T>& x) {
	if( !x.empty() ) {
		auto itr = x.v.cbegin();
		while( itr != x.v.cend() ) {
			v.push_back(*itr);
			itr++;
		}
	}
}

template < typename T >
Stack< T >::Stack(Stack<T> && x) {
	v.swap(x.v);
	x.clear();
}

template < typename T >
Stack<T>& Stack< T >::operator=(const Stack<T>& x) {
	if(this != &x) {
		this->clear();
		if( !x.empty() ) {
                	auto itr = x.v.cbegin();
                	while( itr != x.v.cend() ) {
                        	v.push_back(*itr);
                        	itr++;
                	}
        	}
	}
	return *this;
}

template < typename T >
Stack<T>& Stack< T >::operator=(Stack<T> && x) {
	v.swap(x.v);
	return *this;
}

template < typename T >
bool Stack< T >::empty() const {
	return v.empty();
}

template < typename T >
void Stack< T >::clear() {
	v.clear();
}

template < typename T >
void Stack< T >::push(const T& x) {
	v.push_back(x);
}

template < typename T >
void Stack< T >::push(T && x) {
	v.push_back(std::move(x));
}

template < typename T >
void Stack< T >::pop() {
	v.pop_back();
}

template < typename T >
T& Stack< T >::top() {
	v.back();
}

template < typename T >
const T& Stack< T >::top() const {
	v.back();
}

template < typename T >
int Stack< T >::size() const {
	return v.size();
}

template < typename T >
void Stack< T >::print(std::ostream& os, char ofc) const {
	if(!empty()){
		for(int i = 0; i < size(); i++)
			os << v[i] << ofc;
	}
}

template < typename T >
std::ostream& operator<< (std::ostream& os, const Stack<T>& a) {
	a.print(os);
	return os;
}

template < typename Object >
bool operator== (const Stack<Object>& x, const Stack <Object>& y) {
	if( x.size() == y.size() ) {
		auto xitr = x.v.cbegin();
		auto yitr = y.v.cbegin();
		while( xitr != x.v.cend() && yitr != y.v.cend() ){
			if( *xitr != *yitr )
				return false;
			xitr++;
			yitr++;
		}
		return true;
	}
	return false;
}

template < typename Object >
bool operator!= (const Stack<Object>& x, const Stack <Object>& y) {
	return !(x == y);
}

template < typename Object >
bool operator<= (const Stack<Object>& a, const Stack <Object>& b) {
	if( a.size() > b.size() )
		return false;
	auto aitr = a.v.cbegin();
	auto bitr = b.v.cbegin();
	while( aitr != a.v.cend() ) {
		if( *aitr > *bitr )
			return false;
		aitr++;
		bitr++;
	}
	return true;
}
