/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: marwilc
 *
 * Created on 24 de mayo de 2016, 04:20 PM
 */

#include <cstdlib>
#include "arbnario.h"
//#include <iostream>



//using namespace std;

/*
 * 
 */
int main() {
    
    List<char> lIn, lPre;
    Arbnario<char> arb;
    int num, i;
    char caracter;
    
    cin>>num;
    for(i=1;i<=num;i++)
    {
        cin>>caracter;
        lPre.insert(caracter,i);
    }
    
    for(i=1;i<=num;i++)
    {
        cin>>caracter;
        lIn.insert(caracter,i);
    }
    arb.buildPreIn(lPre,lIn);
    arb.preOrder();
    cout<<endl;
    //node1.print();
    //cout<<"HELLO WORLD BITCHES"<<endl;
    return 0;
}

