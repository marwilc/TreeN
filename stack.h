/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   stack.h
 * Author: marwilc
 *
 * Created on 8 de marzo de 2016, 05:41 PM
 */

#ifndef STACK_H
#define STACK_H
#include "node.h"
#include "tail.h"
#include <iostream>

using namespace std;

template <class T>
class Tail;

template <class T>
class Stack;
template<class T> istream& operator>> (istream& os, Stack<T>& lx);
template<class T> ostream& operator<< (ostream& os, const Stack<T>& lx);

template <class T>
class Stack
{
    private: 
        Node<T> *top, *down; // 
        int length;
        
        void addDown(const T& e);
        
    public:
        Stack<T>();
        Stack<T>(const Stack<T>& p);
        ~Stack<T>(); 
        
        bool isEmpty() const {return (length== 0);};
        int getLength() const {return length;};
        T getTop()const { return (this->top->get_info());};
        
        void Stacking(const T& element);
        void unStacking();
        
        Node<T>* ptrTop() const {return top;}
	Node<T>* ptrDown() const {return down;}
        void emptyingStack();
        void settingTail(const Tail<T> &c);
        
        bool operator==(const Stack<T>& l2) const;
	bool operator!=(const Stack<T>& l2) const;
	void operator=(const Stack<T>& l2);
	Stack<T> operator+(const Stack<T>& l2) const;
	friend istream& operator>> <>(istream& is, Stack<T>& lx);
	friend ostream& operator<< <>(ostream& os, const Stack<T>& lx);
    
};

template<class T>
istream& operator>> (istream& is, Stack<T>& lx)
{
    int n;
    T e;
		
    is>> n;
    for (int i = 1; i <= n; i++)
    {	
	is>> e;
	lx.Stacking(e);
    }
    return is;
}

template <class T>
ostream& operator<< (ostream& os, const Stack<T>& lx)
{
    Node<T>* aux;
    if (lx.getLength()> 0)
    {
	aux= lx.ptrTop();
	while (aux->get_next()!=NULL)
	{
            os<<aux->get_info()<<" ";
            aux= aux->get_next();
	}
	os<<aux->get_info();
    }
    return os;
}

template <class T>
Stack<T>:: Stack(const Stack<T>& p)
{
///- cout<<"sobrecarga(= ... <<pila>>)/";
    Node<T> *aux;

    this->emptyingStack();
    aux= p.top;
    while(aux!= NULL)
    {
	this->addDown(aux->get_info());
	aux= aux->get_next();
    }
}
template <class T>
Stack<T>::Stack()
{
    this->length=0;
    this->top=NULL;
    this->down=NULL;
}

template <class T>
void Stack<T>::Stacking(const T& element)
{
    Node<T> *newPtr;
    newPtr= new Node<T>;
    newPtr->set_info(element);
    if(this->length==0)
    {
        newPtr->set_next(down);
        newPtr->set_prev(top);
        this->top=newPtr;
        this->down=newPtr;   
    }
    else
    {
        
        newPtr->set_next(this->top);
        newPtr->set_prev(NULL);
        this->top->set_prev(newPtr);
        this->top=newPtr;
    }
    this->length++;
}

template <class T>
void Stack<T>::unStacking()
{
    Node<T> *aux;
    if(this->length>0)
    {
        if(this->length==1)
        {   
            
            delete (top);
            top= NULL;
            down= NULL;

        }
        else
        {
            aux=top;
            this->top=aux->get_next();
            delete(aux);
            top->set_prev(NULL);
        }
        this->length--;
    }
}

template <class T>
Stack<T>:: ~Stack()
{
    int i, n;
    Node<T> *aux;
		
    aux= this->top;
    n=this->length;
    for (i = 0; i < n; i++)
    {
	this->top= aux->get_next();
	//cout<<"deleteAux/"<<endl;
	///liberar nodo
	aux->set_next(NULL);
	aux->set_prev(NULL);
	delete (aux);
	//cout<<"deleteAux--SucessFull/"<<endl;
	this->length--;
	aux=this->top;
    }
    this->top= NULL;
    this->down= NULL;
}

template <class T>
void Stack<T>:: emptyingStack()
{
    int i, n;
    Node<T> *aux, *nxt;
		
    aux= this->top;
    n=this->length;
    for (i = 0; i < n; i++)
    {
	nxt= aux->get_next();
	//cout<<"deleteAux/"<<endl;
	///liberar nodo
	aux->set_next(NULL);
	aux->set_prev(NULL);
	delete (aux);
	//cout<<"deleteAux--SucessFull/"<<endl;
	this->length--;
	aux=nxt;
    }
    this->top= NULL;
    this->down= NULL;
}

template <class T>
void Stack<T>:: addDown(const T& e)
{
    Node<T> *nvo;

    nvo= new Node<T>;//crea o reserva la memoria para el nodo nvo
    nvo->set_info(e);//le asigna el elemento al nvo nodo
    if(length== 0)//si es el unico elemento
    {
	nvo->set_next(down);//coloca el nvo nodo apuntando al primer elemento
        nvo->set_prev(top);//y como no tiene un nodo anterior, se le coloca apuntando a NULL
	top= nvo;//luego, coloca al apuntador prim a apuntar al nvo nodo
	down= nvo;
    }
    else
    {
	nvo->set_next(NULL);//como no tiene un nodo proximo, se le coloca apuntando a NULL
	nvo->set_prev(down);//coloca el nvo nodo apuntando al que era el ultimo elemento
	down->set_next(nvo);//luego, coloca al apuntador de elq era el ultimo elemento a apuntar al nvo nodo
	down=nvo; 
    }
       length++;
}

template <class T>
void Stack<T>:: settingTail(const Tail<T>& c)
{
    Node<T> *aux;
		
    this->emptyingStack();
    aux= c.ptrEnd();

    while (aux!=NULL)
    {
	this->Stacking(aux->get_info());
	aux=aux->get_prev();
    }
}

template <class T>
bool Stack<T>:: operator==(const Stack<T>& l2) const
{
    Node<T> *aux1, *aux2;
    bool igual;
		
    aux1= this->top;
    aux2= l2.top;
    igual= true;
		
    if (this->length!= l2.length)
    igual= false;
		 
    else
    {
        while( (aux1!=NULL)&&(aux2!=NULL) && (igual))//mientras no se acaben los elementos de ambas listas
        {
            if(aux1->get_info()== aux2->get_info())//si los elementos son iguales
            {
		aux1=aux1->get_next();//compara el sig
		aux2=aux2->get_next();//compara el sig
            }
            else
		igual= false;//le dice que no son iguales
        }
    }

    return igual;
}

template <class T>
bool Stack<T>:: operator!=(const Stack<T>& l2) const
{
    return (!(*this==l2));
}

template<class T>
Stack<T> Stack<T>::operator+(const Stack<T>& l2) const
{
    Node<T> *aux, *aux2;
    Stack<T> lr;
    
    aux2= l2.top;
    aux=this->top;

    while(aux!= NULL)
    {
	lr.addDown(aux->get_info());
	aux= aux->get_next();
    }
    while(aux2!= NULL)
    {
	lr.addDown(aux2->get_info());
	aux2= aux2->get_next();
    }
    return lr;
}

template<class T>
void Stack<T>::operator=(const Stack<T>& l2)
{
    Node<T> *aux;

    this->emptyingStack();
    aux= l2.top;
    while(aux!= NULL)
    {
	this->addDown(aux->get_info());
	aux= aux->get_next();
    }
}
	
#endif /* STACK_H */


