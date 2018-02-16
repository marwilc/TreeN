/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tail.h
 * Author: marwilc
 *
 * Created on 8 de marzo de 2016, 05:40 PM
 */

#ifndef TAIL_H
#define TAIL_H
#include "node.h"
#include "stack.h"
#include <iostream>

using namespace std;

template <class T>
class Stack;

template <class T>
class Tail;
template<class T> istream& operator>> (istream& os, Tail<T>& lx);
template<class T> ostream& operator<< (ostream& os, const Tail<T>& lx);

template <class T>
class Tail
{
    private:
        Node <T> *front, *end;
        int length;
    public:
        Tail<T>();
        Tail<T>(const Tail<T> &c);
        ~Tail<T>();
        
        bool isEmpty()const {return (length== 0);};
        int getLength() const {return length;};
        T getFront() const { return (this->front->get_info());}
        
        void addTail(const T &element);
        void unTail();
        
        Node<T>* ptrFront() const {return front;}
	Node<T>* ptrEnd() const {return end;}
        void emptyingTail();
        void settingStack(const Stack<T> &p);
        void printTail();
        
        bool operator==(const Tail<T>& l2) const;
	bool operator!=(const Tail<T>& l2) const;
	void operator=(const Tail<T>& l2);
        Tail<T> operator+(const Tail<T>& l2) const;
	friend istream& operator>> <>(istream& is, Tail<T>& lx);
	friend ostream& operator<< <>(ostream& os, const Tail<T>& lx);
        
};

//(cpp) desarrollo

template<class T>
istream& operator>> (istream& is, Tail<T>& lx)
{
    int n;
    T e;
		
    is>> n;
    for (int i = 1; i <= n; i++)
    {	
	is>> e;
        lx.addTail(e);
    }
    return is;
}

template <class T>
ostream& operator<< (ostream& os, const Tail<T>& lx)
{
    Node<T>* aux;
    if (lx.getLength()> 0)
    {
	aux= lx.ptrFront();
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
Tail<T>::Tail()
{
    length=0;
    front=NULL;
    end=NULL;
    
}

template <class T>
Tail<T>:: Tail(const Tail<T> &c)
{
    Node<T> *aux;

    this->emptyingTail();
    aux= c.front;

    while(aux!= NULL)
    {
	this->addTail(aux->get_info());
	aux= aux->get_next();
    }
}

template <class T>
void Tail<T>:: settingStack(const Stack<T>& p)
{
    Node<T> *aux;
		
    this->emptyingTail();
    aux= p.ptrDown();

    while (aux!=NULL)
    {
        this->addTail(aux->get_info());
        aux=aux->get_prev();
    }
}

template <class T>
void Tail<T>::addTail(const T &element)
{
    Node<T> *newPtr;
    
    newPtr= new Node<T>;
    newPtr->set_info(element);
 
    if(this->length==0)
    {
        newPtr->set_next(end);
        newPtr->set_prev(front);
        this->front=newPtr;
        this->end=newPtr;
    }
    else
    {
        newPtr->set_next(NULL);
        newPtr->set_prev(this->end);
        this->end->set_next(newPtr);
        this->end=newPtr;
    }
    
    this->length++;
}

template <class T>
void Tail<T>::unTail()
{
    Node <T> *aux;
    
    if(this->length > 0)
    {
        if(this->length==1)
        {
            delete(front);
            this->front=NULL;
            this->end=NULL;
            
           
        }
        else
        {
            aux=front;
            this->front=aux->get_next();
            delete(aux);
            this->front->set_prev(NULL);
        }
        this->length--;
    }
}

template <class T>
Tail<T>:: ~Tail()
{
    int i, n;
    Node<T> *aux, *sig;
		
    aux=this->front;
    n=this->length;
    for (i = 0; i < n; i++)
    {
        sig= aux->get_next();
        //cout<<"deleteAux/"<<endl;
        ///liberar nodo
        aux->set_next(NULL);
        aux->set_prev(NULL);
        delete (aux);
        //cout<<"deleteAux--SucessFull/"<<endl;
        this->length--;
        aux= sig;
    }
    this->front= NULL;
    this->end= NULL;
    //cout<<"destroy cola";
}

template <class T>
void Tail<T>:: emptyingTail()
{
    int i, n;
    Node<T> *aux, *sig;
		
    aux=this->front;
    n=this->length;
    for (i = 0; i < n; i++)
    {
        sig= aux->get_next();
        //cout<<"deleteAux/"<<endl;
        ///liberar nodo
        aux->set_next(NULL);
        aux->set_prev(NULL);
        delete (aux);
        //cout<<"deleteAux--SucessFull/"<<endl;
        this->length--;
        aux= sig;
    }
    this->front= NULL;
    this->end= NULL;
    //cout<<"destroy cola";
}

template <class T>
bool Tail<T>:: operator==(const Tail<T>& l2) const
{
    Node<T> *aux1, *aux2;
    bool igual;
		
    aux1= this->front;
    aux2= l2.front;
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
bool Tail<T>:: operator!=(const Tail<T>& l2) const
{
    return (!(*this==l2));

}

template<class T>
Tail<T> Tail<T>::operator+(const Tail<T>& l2) const
{
    Node<T> *aux, *aux2;
    Tail<T> lr;
		
    aux2= l2.front;
    aux=this->front;

    while(aux!= NULL)
    {
	lr.addTail(aux->get_info());
	aux= aux->get_next();
    }
    while(aux2!= NULL)
    {
	lr.addTail(aux2->get_info());
	aux2= aux2->get_next();
    }
    return lr;
}

template<class T>
void Tail<T>::operator=(const Tail<T>& l2)
{
    Node<T> *aux;

    this->emptyingTail();
    aux= l2.front;
    while(aux!= NULL)
    {
	this->addTail(aux->get_info());
	aux= aux->get_next();
    }

}

template <class T>
void Tail<T>::printTail()
{   
    while(!this->isEmpty())
    {
        cout<<this->getFront()<<" ";
        this->unTail();
    }
    
}

#endif /* TAIL_H */

