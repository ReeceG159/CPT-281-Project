#ifndef ADDITION_OF_TWO_POLNOMIALS
#define ADDITION_OF_TWO_POLNOMIALS

#include <iostream>
#include <string>

using std::exception;
using std::ostream;
using std::to_string;
using namespace std;

// A doubly-linked list with iterators
template<class T>
class Polynomial_Addition {
public:
	// Iterator
	class Iterator;

    // Term
    class Term;

	// Constructors

	// Defaule Constructor
	Polynomial_Addition();
	// Copy Constructor
	Polynomial_Addition(const Polynomial_Addition<T>&);

	// Destructor
	virtual ~Polynomial_Addition();

	// Operators

	// Deep-copy Assignment operator
	const Polynomial_Addition<T>& operator = (const Polynomial_Addition<T>&);

	// Class-member functions
	size_t size() const;  // Returns the size of the list.
	bool empty() const;  // Tests whether the list is empty.
	T& front();  // Returns the first element stored in the list (l-value).
	const T& front() const;  // Returns the first element stored in the list (r-value).
	T& back();  // Returns the last element stored in the list (l-value).
	const T& back() const;  // Returns the last element stored in the list (r-value).
	void push_front(const T&);  // Adds an element to the front end of the list.
	void push_back(const T&);  // Adds an element to the rear end of the list.
	void pop_front();  // Deletes the element at the front end of the list.
	void pop_back();  // Deletes the element at the rear end of the list.
	void clear();  // Deletes all the elements in the list.
    void Sort();   // Sorts the double linked list

    Polynomial_Addition<T> operator + (const Polynomial_Addition<T>&) const; // Adds two polynomials together

	Iterator begin() const;  // Generates an iterator on the first element of the list.
	Iterator end() const;  // Generates an iterator just after the last element of the list.
	Iterator& insert(Iterator&, const T&);  // Inserts an element at iterator position.
	Iterator& erase(Iterator&);  // Deletes the element at iterator position.
	Iterator find(const T&) const;  // Searches for a value in the list.

private:
	// A doubly-linked list node
	struct D_Node;

	// Data fields

    D_Node* head;		    // Stores a pointer to the first node
    D_Node* tail;	        // Stores a pointer to the last node
    size_t num_of_items; 	// Stores the number of elements in the list
    bool combine_terms(const T& item);
};

// Implementation of class "Polnomial_Addition"

// A doubly-linked list node
template<class T>
struct Polynomial_Addition<T>::D_Node {
	// Data fields

	T data;		// Stores some data in the nodes
	D_Node* next;		// A pointer to the next node
	D_Node* prev;		// A pointer to the previous node

	// Constructor
	D_Node(const T&);
};

// Constructor of struct "Node"
template<class T>
Polynomial_Addition<T>::D_Node::D_Node(const T& data) : data(data), next(NULL), prev(NULL) {}

// Default Constructor
template<class T>
Polynomial_Addition<T>::Polynomial_Addition() : head(NULL), tail(NULL), num_of_items(0) {}

// Copy Constructor
template<class T>
Polynomial_Addition<T>::Polynomial_Addition(const Polynomial_Addition<T>& other) {
	head = tail = NULL;
	*this = other;
}

// Destructor
template<class T>
Polynomial_Addition<T>::~Polynomial_Addition() { clear(); }

// Deep-copy assignment operator
template<class T>
const Polynomial_Addition<T>& Polynomial_Addition<T>::operator = (const Polynomial_Addition<T>& rhs) {
	if (this != &rhs) {
		clear();
		num_of_items = rhs.num_of_items;
		if (num_of_items) {
			head = tail = new D_Node(rhs.head->data);
			D_Node* q = rhs.head->next;
			while (q) {
				tail->next = new D_Node(q->data);
				tail->next->prev = tail;
				tail = tail->next;
				q = q->next;
			}
		}
	}
	return *this;
}

// Returns the size of the list.
template<class T>
size_t Polynomial_Addition<T>::size() const { return num_of_items; }  

// Tests whether the list is empty.
template<class T>
bool Polynomial_Addition<T>::empty() const { return !size(); }  

// Returns the first element in the list (l-value).
template<class T>
T& Polynomial_Addition<T>::front() {
    if (empty()) { throw exception("Accessing empty list"); }
    return head->data;
}  

// Returns the first element in the list (r-value).
template<class T>
const T& Polynomial_Addition<T>::front() const {
    if (empty()) { throw exception("Accessing empty list"); }
    return head->data;
}  

// Returns the last element in the list (l-value).
template<class T>
T& Polynomial_Addition<T>::back() {
    if (empty()) { throw exception("Accessing empty list"); }
    return tail->data;
}  

// Returns the last element in the list (r-value).
template<class T>
const T& Polynomial_Addition<T>::back() const {
    if (empty()) { throw exception("Accessing empty list"); }
    return tail->data;
}  

// Adds an element to the front end of the list.
template<class T>
void Polynomial_Addition<T>::push_front(const T& item) {
    if (!(num_of_items++)) { head = tail = new D_Node(item); }
    else {
        head->prev = new D_Node(item);
        head->prev->next = head;
        head = head->prev;
    }
}  

// Adds an element to the rear end of the list.
template<class T>
void Polynomial_Addition<T>::push_back(const T& item) {
    bool combined = false;
    combined = combine_terms(item);
    if (combined == false) {
        if (!(num_of_items++)) { head = tail = new D_Node(item); }
        else {
            tail->next = new D_Node(item);
            tail->next->prev = tail;
            tail = tail->next;
        }
    }
}

// Combines term if possible
template<class T>
bool Polynomial_Addition<T>::combine_terms(const T& item) {
    bool combined = false;
    D_Node* q = head;
    while (q) {
       if (q->data->getexpo() == item->getexpo()) {
           //if (q->data->coef + item->coef == 0) {
           if (q->data->getcoef() + item->getcoef() == 0) {
               Iterator it = find(q->data);
               erase(it);
               combined = true;
               break;
           }
           else {
               int m = q->data->getcoef() + item->getcoef();
               q->data->setcoef(m);
               combined = true; 
           }
        }
        q = q->next;
    }
    return combined;
}

// Deletes the element at the front end of the list.
template<class T>
void Polynomial_Addition<T>::pop_front() {
    if (empty()) { throw exception("Accessing empty list"); }
    D_Node* to_be_deleted = head;
    if (num_of_items-- == 1) { head = tail = NULL; }
    else {
        head = head->next;
        head->prev = NULL;
    }
    delete to_be_deleted;
}  

// Deletes the element at the rear end of the list.
template<class T>
void Polynomial_Addition<T>::pop_back() {
    if (empty()) { throw exception("Accessing empty list"); }
    D_Node* to_be_deleted = tail;
    if (num_of_items-- == 1) { head = tail = NULL; }
    else {
        tail = tail->prev;
        tail->next = NULL;
    }
    delete to_be_deleted;
}  

// Deletes all the elements in the list.
template<class T>
void Polynomial_Addition<T>::clear() {
    if (head) {
        D_Node* p = head;
        head = head->next;
        delete p;
    }
    tail = NULL;
    num_of_items = 0;
}  

// Sorts the elements in the list.
// Using a bubble sort algorithm in reverse to sort from greatest to least.
template<class T>
void Polynomial_Addition<T>::Sort() {
    bool swapped;
    struct D_Node* node1 = NULL;
    struct D_Node* lnode = NULL;

    do {
        swapped = false;
        node1 = head;
        while (node1->next != lnode) {
            if (node1->data->getexpo() < node1->next->data->getexpo()) {
                std::swap(node1->data, node1->next->data);
                swapped = true;
                }
            node1 = node1->next;
        }
        lnode = node1;
    }
    while (swapped);
}

// Adds togther two polynomials and inserts the result into a new list
template<class T>
Polynomial_Addition<T> Polynomial_Addition<T>:: operator + (const Polynomial_Addition<T>& rhs) const {
    Polynomial_Addition<T> result;
    if (this != &rhs) {
        if (rhs.num_of_items) {
            D_Node* q = head;
            // Add the rhs to the result list.  Terms are already combined.
            result = rhs;

            // add the lhs to the result list.  push_back combines terms.
            while (q) {
               T data = q->data;
               result.push_back(data);
                q = q->next;
            }
        }
    }
    return result;
}

// Stream insertion operator
template<class T>
ostream& operator << (ostream& out, const Polynomial_Addition<T>& li) {
    bool first = true;
    for (typename Polynomial_Addition<T>::Iterator it = li.begin(); it != li.end(); it++) {
        if (first == false) {
            if ((*it)->getcoef() > 0) {
                out << '+';
            }
        }
        out << (*it)->getcoef();
        if ((*it)->getexpo() != 0) {
            out << 'x';
        }
        if ((*it)->getexpo() != 0 && (*it)->getexpo() != 1) {
            out << '^';
            out << (*it)->getexpo();
        }
        first = false;
    }
    return out;
}

// A list iterator
template<class T>
class Polynomial_Addition<T>::Iterator {
public:
    // Operators
    Iterator operator + (int) const;  // Generates an iterator several positions after current position.
    Iterator& operator += (int);  // Moves the iterator forward for specified positions.
    Iterator operator - (int) const;  // Generates an iterator several positions before current position.
    Iterator& operator -= (int);  // Moves the iterator backward for specified positions.
    Iterator& operator ++ ();  // Moves the iterator forward for one position (prefix).
    Iterator operator ++ (int);  // Moves the iterator forward for one position (postfix).
    Iterator& operator -- ();  // Moves the iterator backward for one position (prefix).
    Iterator operator -- (int);  // Moves the iterator backward for one position (postfix).
    int operator - (const Iterator&) const;  // Finds the position different for two iterators.
    T& operator * ();  // Returns the element at current iterator position (l-value).
    const T& operator * () const;  // Returns the element at current iterator position (r-value).
    T* operator -> ();  // Returns a pointer to the element at current iterator position.
    bool operator == (const Iterator&) const;  // Tests whether two iterators point to the same element.
    bool operator != (const Iterator&) const;  // Tests whether two iterators point to difference elements.

private:
    // Data fields
    const Polynomial_Addition<T>* parent;  // Stores a pointer to the parent linked list.
    D_Node* current;  // Stores a pointer to the node the iterator is on.
    size_t offset;  // Stores the number of elements passed after the first element.

    // Constructor
    Iterator(const Polynomial_Addition<T>*, D_Node*, size_t);

    friend class Polynomial_Addition<T>;
};

// Constructor of iterator
template<class T>
Polynomial_Addition<T>::Iterator::Iterator(const Polynomial_Addition<T>* parent, D_Node* current, size_t offset) :
    parent(parent), current(current), offset(offset) {}  

// Generates an iterator several positions after current position.
template <class T>
typename Polynomial_Addition<T>::Iterator Polynomial_Addition<T>::Iterator::operator + (int num) const {
    if (num < 0) { return *this - -num; }
    typename Polynomial_Addition<T>::Iterator result = *this;
    for (int i = 0; i < num; i++) { result++; }
    return result;
}  

// Moves the iterator forward for specified positions.
template<class T>
typename Polynomial_Addition<T>::Iterator& Polynomial_Addition<T>::Iterator::operator += (int num) {
    if (num < 0) { return *this -= -num; }
    for (int i = 0; i < num; i++) { (*this)++; }
    return *this;
}  

// Generates an iterator several positions before current position.
template<class T>
typename Polynomial_Addition<T>::Iterator Polynomial_Addition<T>::Iterator::operator - (int num) const {
    if (num < 0) { return *this + -num; }
    typename Polynomial_Addition<T>::Iterator result = *this;
    for (int i = 0; i < num; i++) { result--; }
    return result;
}  

// Moves the iterator backward for specified positions.
template<class T>
typename Polynomial_Addition<T>::Iterator& Polynomial_Addition<T>::Iterator::operator -= (int num) {
    if (num < 0) { return *this += -num; }
    for (int i = 0; i < num; i++) { (*this)--; }
    return *this;
}  

// Moves the iterator forward for one position (prefix).
template<class T>
typename Polynomial_Addition<T>::Iterator& Polynomial_Addition<T>::Iterator::operator ++ () {
    if (!current) { throw exception("Iterator out of range"); }
    current = current->next;
    offset++;
    return *this;
} 

// Moves the iterator forward for one position (postfix).
template<class T>
typename Polynomial_Addition<T>::Iterator Polynomial_Addition<T>::Iterator::operator ++ (int) {
    typename Polynomial_Addition<T>::Iterator result = *this;
    ++(*this);
    return result;
} 

// Moves the iterator backward for one position (prefix).
template<class T>
typename Polynomial_Addition<T>::Iterator& Polynomial_Addition<T>::Iterator::operator -- () {
    if (current == parent->head) { throw exception("Iterator out of range"); }
    current = current ? current->prev : parent->tail;
    offset--;
    return *this;
}  

// Moves the iterator backward for one position (postfix).
template<class T>
typename Polynomial_Addition<T>::Iterator Polynomial_Addition<T>::Iterator::operator -- (int) {
    typename Polynomial_Addition<T>::Iterator result = *this;
    --(*this);
    return result;
} 

// Finds the position different for two iterators.
template<class T>
int Polynomial_Addition<T>::Iterator::operator - (const Iterator& other) const {
    return (int)offset - (int)other.offset;
}  

// Returns the element at current iterator position (l-value).
template<class T>
T& Polynomial_Addition<T>::Iterator::operator * () {
    if (!current) { throw exception("Dereferencing NULL pointer"); }
    return current->data;
}  

// Returns the element at current iterator position (r-value).
template<class T>
const T& Polynomial_Addition<T>::Iterator::operator * () const {
    if (!current) { throw exception("Dereferencing NULL pointer"); }
    return current->data;
} 

// Returns a pointer to the element at current iterator position.
template<class T>
T* Polynomial_Addition<T>::Iterator::operator -> () {
    if (!current) { throw exception("Dereferencing NULL pointer"); }
    return &(current->data);
}  

// Tests whether two iterators point to the same element.
template<class T>
bool Polynomial_Addition<T>::Iterator::operator == (const Iterator& other) const {
    return offset == other.offset;
}  

// Tests whether two iterators point to different elements.
template<class T>
bool Polynomial_Addition<T>::Iterator::operator != (const Iterator& other) const {
    return offset != other.offset;
}  

// Generates an iterator on the first element of the list.
template<class T>
typename Polynomial_Addition<T>::Iterator Polynomial_Addition<T>::begin() const {
    return Iterator(this, head, 0);
} 

// Generates an iterator just after the last element of the list.
template<class T>
typename Polynomial_Addition<T>::Iterator Polynomial_Addition<T>::end() const {
    return Iterator(this, NULL, size());
} 

// Inserts an element at iterator position.
template<class T>
typename Polynomial_Addition<T>::Iterator& Polynomial_Addition<T>::insert(Iterator& pos, const T& value) {
    if (pos == begin()) {
        push_front(value);
        pos = ++begin();
    }
    else if (pos == end()) {
        push_back(value);
        pos = end();
    }
    else {
        D_Node* new_node = new D_Node(value);
        new_node->prev = pos.current->prev;
        new_node->prev->next = new_node;
        new_node->next = pos.current;
        new_node->next->prev = new_node;
        num_of_items++;
        pos.offset++;
    }
    return pos;
}  

// Deletes the element at iterator position.
template<class T>
typename Polynomial_Addition<T>::Iterator& Polynomial_Addition<T>::erase(Iterator& pos) {
    if (pos == end()) { throw exception("Dereferencing NULL pointer"); }
    if (pos == begin()) {
        pop_front();
        pos = begin();
    }
    else if (pos == --end()) {
        pop_back();
        pos = end();
    }
    else {
        D_Node* to_be_deleted = pos.current;
        pos.current->prev->next = pos.current->next;
        pos.current->next->prev = pos.current->prev;
        pos.current = pos.current->next;
        num_of_items--;
        delete to_be_deleted;
    }
    return pos;
}  

// Searches for a value in the list.
template<class T>
typename Polynomial_Addition<T>::Iterator Polynomial_Addition<T>::find(const T& value) const {
    for (Iterator it = begin(); it != end(); it++) {
        if (*it == value) { return it; }
    }
    return end();
} 

// A Term class
//template<class T>
class /*Polynomial_Addition<T>::*/Term {
public:
    bool operator < (const Term&) const; // Tests to see if the right exponent is greater
    bool operator == (const Term&) const; // Tests to see if exponents are equal
    bool operator > (const Term&) const; // Tests to see if the left exponent is greater
    bool operator != (const Term&) const; // Tests to see if exponents not are equal

    // Constructor
    Term(int c, int e) {
        coef = c;
        expo = e;
    }

    // Getters
    int getcoef();
    int getexpo();

    // Setters
    void setcoef(int);
    void setexpo(int);

private:
    // Data fields
    int coef; // coefficient
    int expo; // exponent
};

// Tests to see if the right exponent is greater
bool Term:: operator < (const Term& other) const {
    return expo < other.expo;
}

// Tests to see if the left exponent is greater
bool Term:: operator > (const Term& other) const {
    return expo > other.expo;
}

// Tests to see if exponents not equal
bool Term:: operator != (const Term& other) const {
    return expo != other.expo;
}


// Tests to see if exponents are equal
bool Term:: operator == (const Term& other) const {
    return expo == other.expo;
}

// Gets the coef
int Term::getcoef() {
    return coef;
}

// Gets the expo
int Term::getexpo() {
    return expo;
}

// Sets the coef
void Term::setcoef(int c) {
    coef = c;
}

// Sets the expo
void Term::setexpo(int e) {
    expo = e;
}
#endif