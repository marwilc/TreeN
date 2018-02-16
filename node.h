#ifndef node_h
#define node_h
#include <iostream>

template <class T>
class Node
{
	private:
		T info;
		Node<T> *prev;
		Node<T> *next;
	public:
		//builder
		Node<T>():next(NULL), prev(NULL){};
		Node<T>(const Node<T> &n): info(n.info), next(n.next), prev(n.prev){};
		Node<T>(const T &e, Node<T> *nxt, Node<T> *prv ): info(e), next(nxt), prev(prv){};
		
		//consult
		T get_info() const {return info;};
		T* get_ptr() {return &info;};
		Node<T>* get_prev() {return prev;};
		Node<T>* get_next() {return next;};
		
		//modify
		void set_ptr(T* i) {info = *i;}
		void set_info(const T &e) {info = e;};
		void set_prev(Node<T>* prv) {prev = prv;};
		void set_next(Node<T>* nxt) {next = nxt;};
};
#endif
