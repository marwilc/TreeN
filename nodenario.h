/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   nodenario.h
 * Author: marwilc
 *
 * Created on 16 de mayo de 2016, 07:38 PM
 */

#ifndef NODENARIO_H
#define NODENARIO_H
#include <iostream>

using namespace std;

template <class T>
class Nodenario
{
    private:
        T info;
        Nodenario<T> *sonLeft, *brotherRight;
        
        
    public:
        //builders
        Nodenario<T>(): sonLeft(NULL), brotherRight(NULL){};
        Nodenario<T>(const T &e): info(e), sonLeft(NULL), brotherRight(NULL){};
        Nodenario<T>(const T &e, Nodenario<T> *sLeft, Nodenario<T> *bRight): info(e), sonLeft(sLeft), brotherRight(bRight){};
        
        //consultors
        T getInfo() const {return(info);}
        Nodenario<T> *getSonLeft(){return(sonLeft);}
        Nodenario<T> *getBroRight(){return(brotherRight);}
        bool nodeLeaf()const {return((this->sonLeft==NULL)&&(this->brotherRight==NULL));}
        void print(){cout<<info;}
        
        //set-ups
        void setInfo(const T&e) {this->info=e;}
        void setSonLeft(Nodenario<T> *sLeft){sonLeft=sLeft;}
        void setBroRight(Nodenario<T> *bRight){brotherRight=bRight;}
};


#endif /* NODENARIO_H */

