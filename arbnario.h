/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   arbnario.h
 * Author: marwilc
 *
 * Created on 16 de mayo de 2016, 07:37 PM
 */

#ifndef ARBNARIO_H
#define ARBNARIO_H
//#include <iostream>
#include "nodenario.h"
#include "list.h"
#include "stack.h"
#include "tail.h"

//using namespace std;

template <class T>
class Arbnario
{
    private:
        Nodenario<T> *nodeRoot;
        int dim;
        
        static Nodenario<T>* copyNodeN(Nodenario<T> *ptr);
        static void destroyNode(Nodenario<T> *ptr);
        static void routePreOrder(Nodenario<T> *ptrRoot);
        static void routeInOrder(Nodenario<T> *ptrRoot);
        static void routePostOrder(Nodenario<T> *ptrRoot);
    
    public:
        //destroyer
        ~Arbnario<T>();
        void emptyNarioTree();
        
        //builders
        Arbnario<T>(): nodeRoot(NULL), dim(0){};
        Arbnario<T>(const T &e){nodeRoot= new Nodenario<T> (e), dim=1;}
        Arbnario(const T &e, const Arbnario &a1, const Arbnario &a2);
        Arbnario(const T &e, const List<Arbnario > list);
        
        //consultors
        bool isNull() const{return(nodeRoot==NULL);}
        T getRoot()const {return(nodeRoot->getInfo());};
        //List<Arbnario<T> > sons() const;
        void print();
        
        //modifiers
        void copyTreeNario(const Arbnario<T> &Ab);
        void insertSubTreeNario(const Arbnario<T> &tree);
        void buildPreIn(List<T> &pre,List<T> &in);
        
        //routes
        void preOrder();
        void inOrder();
        void postOrder();
       
};
//statics
template<class T>
Nodenario<T>* Arbnario<T>:: copyNodeN(Nodenario<T> *ptr)
{
    Nodenario<T>* nvo;
    if (ptr== NULL)
        nvo= NULL;
    else
	nvo= new Nodenario<T>(ptr->getInfo(), copyNodeN(ptr->getSonLeft()), copyNodeN(ptr->getBroRight()));
    return nvo;
}

template<class T>
void Arbnario<T>:: destroyNode(Nodenario<T> *ptr)
{
    if(ptr!=NULL)
    {
        if(ptr->getBroRight()!=NULL)
        {
            destroyNode(ptr->getBroRight());
        }
        
        if(ptr->getSonLeft()!=NULL)
        {
            destroyNode(ptr->getSonLeft());
        }
        delete(ptr);
        ptr=NULL;
    }
}

template<class T>
void Arbnario<T>:: routePreOrder(Nodenario<T> *ptrRoot)
{
    Nodenario<T> *aux;
    
    if(ptrRoot!=NULL)
    {
        ptrRoot->print();
        aux=ptrRoot->getSonLeft();
        while(aux!=NULL)
        {
            routePreOrder(aux);
            aux=aux->getBroRight();
        }
    }
}

template<class T>
void Arbnario<T>:: routeInOrder(Nodenario<T> *ptrRoot)
{
    Nodenario<T> *aux;
    
    if(ptrRoot!=NULL)
    {
        routeInOrder(ptrRoot->getSonLeft());
        ptrRoot->print();
        aux=ptrRoot->getSonLeft()->getBroRight();
        while(aux!=NULL)
        {
            routeInOrder(aux);
            aux=aux->getBroRight();
        }
    }
}

template<class T>
void Arbnario<T>:: routePostOrder(Nodenario<T> *ptrRoot)
{
    Nodenario<T> *aux;
    
    if(ptrRoot!=NULL)
    {
        aux=ptrRoot->getSonLeft();
        while(aux!=NULL)
        {
            routePostOrder(aux);
            aux=aux->getBroRight();
        }
        ptrRoot->print();
    }
}

//destroyer
template<class T>
Arbnario<T>:: ~Arbnario<T>()
{
    Stack<Nodenario<T>* > P;
    Nodenario<T> *aux;
    if(this->nodeRoot!=NULL)
    {
        P.Stacking(this->nodeRoot);
        while(!P.isEmpty())
        {
            aux=P.getTop();
            P.unStacking();
            
            if(aux->getSonLeft()!= NULL)
                P.Stacking(aux->getSonLeft());				
            if(aux->getBroRight() != NULL)
                P.Stacking(aux->getBroRight());
            
            //liberar nodo arbolB
            aux->setSonLeft(NULL);
            aux->setBroRight(NULL);
            delete(aux);
        }
    }
    this->nodeRoot=NULL;
    dim=0;
}

template<class T>
void Arbnario<T>:: emptyNarioTree()
{
    Stack<Nodenario<T>* > P;
    Nodenario<T> *aux;
    if(this->nodeRoot!=NULL)
    {
        P.Stacking(this->nodeRoot);
        while(!P.isEmpty())
        {
            aux=P.getTop();
            P.unStacking();
            
            if(aux->getSonLeft()!= NULL)
                P.Stacking(aux->getSonLeft());				
            if(aux->getBroRight() != NULL)
                P.Stacking(aux->getBroRight());
            
            //liberar nodo arbolB
            aux->setSonLeft(NULL);
            aux->setBroRight(NULL);
            delete(aux);
        }
    }
    this->nodeRoot=NULL;
    dim=0;
}

//builders
template<class T>
Arbnario<T>:: Arbnario(const T &e, const Arbnario &A1, const Arbnario &A2)
{
    Arbnario arbolaux;
		
    nodeRoot= new Nodenario<T>(e);
    arbolaux.copyTreeNario(A1);
    this->nodeRoot->setSonLeft(arbolaux.nodeRoot);
    arbolaux.copyTreeNario(A2);
    this->nodeRoot->setBroRight(arbolaux.nodeRoot);
    arbolaux.nodeRoot= NULL;
    dim= (A1.dim)+ (A2.dim) +1;
}

template<class T>
Arbnario<T>:: Arbnario(const T &e, const List<Arbnario > list)
{
    Nodenario<T> *aux;
    
    nodeRoot=new Nodenario<T>(e,NULL,NULL);
    if(!list.isEmpty())
    {
        nodeRoot->setSonLeft(copyNodeN(list.consult(1).nodeRoot));
        list.erase(1);
        aux=nodeRoot->getSonLeft();
        while(!list.isEmpty())
        {
            aux->setBroRight(copyNodeN(list.consult(1).nodeRoot));
            list.erase(1);
            aux=aux->getBroRight();
        }
    }   
}

//consultors
/*template<class T>
List<Arbnario<T> > Arbnario<T>:: sons()
{
    Nodenario<T> *aux;
    Arbnario<T> arbAux;
    List<Arbnario<T> > list;
    int i=0;
    
    aux=nodeRoot->getSonLeft();
    while(aux!=NULL)
    {
        arbAux.nodeRoot=copyNodeN(aux);
        list.insert(arbAux,i++);
        aux=aux->getBroRight();
    }
    return(list);
}*/

//set-ups
template<class T>
void Arbnario<T>:: copyTreeNario(const Arbnario<T> &Ab)
{
    this->nodeRoot= copyNodeN(Ab.nodeRoot);
    this->dim= Ab.dim;
}
template<class T>
void Arbnario<T>:: insertSubTreeNario(const Arbnario<T> &tree)
{
    Nodenario<T> *aux;
    
    if(nodeRoot->getSonLeft()==NULL)
    {
        nodeRoot->setSonLeft(copyNodeN(tree.nodeRoot));
    }
    else
    {
        aux=nodeRoot->getSonLeft();
        while(aux->getBroRight()!=NULL)
        {
            aux=aux->getBroRight();
        }
        aux->setBroRight(copyNodeN(tree.nodeRoot));
    }
}

template <class T>
void Arbnario<T>:: buildPreIn(List<T> &pre,List<T> &in)
{
    Arbnario<T> Aizq, Ader;
    List<T> listD, listI;
    T e;
    int n;

    if ((!pre.isEmpty())&&(!in.isEmpty()))
    {
        e= pre.consult(1);
	pre.erase(1);
	n= in.itsFound(e);///OBERVACION: que pasa si hay elementos repetidos?...
	nodeRoot=new Nodenario<T>(e);
        dim++;
	listI= in.generarSLint(1,n-1);
        listD= in.generarSLint(n+1,in.length());
	Aizq.buildPreIn(pre, listI);
	nodeRoot->setSonLeft(Aizq.nodeRoot);
	dim=dim+Aizq.dim;
	Ader.buildPreIn(pre, listD);
	nodeRoot->setBroRight(Ader.nodeRoot);
	dim=dim+Ader.dim;
	Ader.nodeRoot=NULL;
	Aizq.nodeRoot=NULL;
    }
}

//routes
template<class T>
void Arbnario<T>:: preOrder()
{
    routePreOrder(nodeRoot);
}

template<class T>
void Arbnario<T>:: inOrder()
{
    routeInOrder(nodeRoot);
}

template<class T>
void Arbnario<T>:: postOrder()
{
    routePostOrder(nodeRoot);
}
#endif /* ARBNARIO_H */

