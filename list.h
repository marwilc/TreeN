#ifndef list_h
#define list_h

#include "node.h"
#include <iostream>

using namespace std;

template <class T>
class List;
template<class T> istream& operator>> (istream& os, List<T>& li);
template<class T> ostream& operator<< (ostream& os, const List<T>& li);

//double-linked list 
template <class T>
class List
{
	private:
		Node<T> *first, *last;
		int dim;
                
                void QuickSort(int izq, int der);
                static void mayoRecursivo(Node<T>* aux,T *e, int *n);
		
	public:
		void deletePtr(Node<T>* x);
                Node<T>* thisPtr(const T& e) const;
                Node<T>* consultPtr(int pos) const;
                Node<T>* first_n()const {return first;}
                Node<T>* last_n()const {return last;}
                void insertPtr(Node<T>* x, const T& e);	//recibe un apuntador al elemento que esta en la posicion donde se va a inserta
        
        public:
                List<T>();
                List<T>(const List<T>& l);
                ~List<T>();
                
		bool isEmpty() const;
		int length()const {return dim;};
		T consult(int pos) const;
                int itsFound(const T& e) const;
                
                void insert(const T& e, int pos);
                void erase(int pos);
                void emptying();
                
                List<T> copy()const{List<T> aux; aux=*this;return (aux);}     
                void Set_info(int pos, const T& e);	
		void insert(const T& e); //insertar ordenado
		void invest();
                void invertirSubL(const T& a, const T& b);
		void invertSubLint(int a, int b);
                int esSubL(const List<T> &x)const;
                int ocurrencia(const List<T> &listB)const;
                void imprimir() const ;
                void eliminarSL(const List<T> &x);
                List<T> generarSL(const T& a, const T& b);
                List<T> generarSLint(int x, int y);
                int estaOrdenada() const;
                T menorElem() const;
                int menorPos() const;
                T mayorElem() const;
                int mayorPos() const;
                List<T> intersection(const List<T> &li);
                void mezclarL(const List<T> &l1, const List<T> &l2);//retorna una lista con los elementos de ambas listas ordenados
                void swap(int i1, int i2)const;
                //extensiones
                
                void ordenar();
                List<T> codification(); 
		
		///overload of operators input-output
		bool operator==(const List<T>& li) const;
                bool operator!=(const List<T>& li) const;
		List<T> operator+(const List<T>& li) const;
		List<T> operator-(const List<T>& li) const;
                void operator=(const List<T>& li);
		friend istream& operator>> <>(istream& is, List<T>& li);
		friend ostream& operator<< <>(ostream& os, const List<T>& li);
               
		void mayorElem(T *mayor,int *n);
                void mezclarL2(const List<T> &l1, const List<T> &l2);
};

template <class T>
istream& operator>> (istream& is, List<T>& li)
{
		int n;
		T e;
		
		is>> n;
		for (int i = 1; i <= n; i++)
		{	
			is>> e;
			li.insert(e, i);
		}
		return is;
}

template <class T>
ostream& operator<< (ostream& os, const List<T>& li)
{
		Node<T>* aux;
		if (li.length()>0)
		{
			aux= li.first_n();
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
List<T>::List()
{
	this->dim=0;
        this->first=NULL;
	this->last=NULL;
	
}

template<class T>
	List<T>::List(const List<T>& l2)
	{
		///- cout<<"sobrecarga(= ... <<lista>>)/";
		Node<T> *aux;

		this->emptying();
		aux= l2.first;

		while(aux!= NULL)
		{
			this->insert(aux->get_info(), this->dim+1);
			aux= aux->get_next();
		}

	}

template <class T>
bool List<T>::isEmpty() const
{
	return (this->dim==0);
}

template <class T>
T List<T>::consult(int pos) const
{
	Node<T> *current;
	int i;
        T r;
	
	if((pos > 0) && (pos<=this->dim ))
	{
		if(pos==1)
		{
			current=first;
		}
		else if(pos == dim)
			 {
				current=last;
			 }
			 else
			 {
				current=first->get_next();
				for (i = 2; i < pos; i++)
				{
					current=current->get_next();
				}			 
			 }
                r=current->get_info();
	}
	return (r);
} 

template<class T>
int List<T>::itsFound(const T& e) const
{	
    int i;
    Node<T>* aux;
    bool found;	

    aux= first;
    i=1;
    found= 0;
    while ((!found) && (aux!= NULL))
    {
	if (aux->get_info()== e)
            found= 1;		
	else
	{
            aux= aux->get_next();
            i++;	
	}		
    }
    if (found== 0)
        i= -1;//un valor negativo que indica que no esta el elemento
			
    return (i);
}

template<class T>
void List<T>::Set_info(int pos, const T& e)
{
		Node<T> *q;
		q=this->consultPtr(pos);
		q->set_info(e);
}

template <class T>
void List<T>::insert(const T& e, int pos)
{
	Node<T> *newn, *ant;
	int i;
	
	newn = new Node<T>;
	newn->set_info(e);
	
	if (pos > 0 && this->dim+1 >= pos)
	{
		if(this->dim == 0)
		{
			
			newn->set_next(last);
			newn->set_prev(first);
                        this->first=newn;
			this->last=newn;
		}
		else if (pos == 1)
			{
				newn->set_next(this->first);
				newn->set_prev(NULL);
                                this->first->set_prev(newn);
				this->first=newn;
				
			}
			else if (pos == this->dim+1)			// inserta despues de la ultima posicion existente
				{
					newn->set_next(NULL);
                                        newn->set_prev(this->last);
                                        this->last->set_next(newn);
					this->last=newn;
					
				}
				else if(pos <=((dim/2)+(dim%2)))       //inserta en la ultima posicion
					{
						ant=first;
                                                for(i=1;i<pos-1;i++)
                                                {
                                                    ant=ant->get_next();
                                                }
                                                ant->get_next()->set_prev(newn);
                                                newn->set_next(ant->get_next());//ahora nvo apunta al siguien del anterior
                                                newn->set_prev(ant);//ahora, coloca al nvo nodo a apuntar a su anterior (ant)
                                                ant->set_next(newn);
					} 
					else
					{
                                                ant=last;
						for (i = dim; i > pos; i--)
						{
							ant=ant->get_prev();
						}
						newn->set_next(ant);
						newn->set_prev(ant->get_prev());
						ant->get_prev()->set_next(newn);
						ant->set_prev(newn);
					}
		this->dim++;
	}
}

template <class T>
void List<T>::erase(int pos)
{
	Node<T> *current, *enl;
	int i;
	
	if((dim> 0)&&((pos<=dim) && (pos>=1)))
	{
		if(dim==1)
		{
			delete(first);
			this->first=NULL;
			this->last=NULL;
		}
		else if(pos==1)
		{
			enl=first->get_next();
			delete(this->first);
			this->first=enl;
			this->first->set_prev(NULL);	
		}
		else if(pos ==dim)
		{
                        enl= last->get_prev();
			delete (last);
                        last= enl;
			last->set_next(NULL);
                                
		}
                else if(pos<=(dim/ 2))
                {
                        enl=first;
			for (i = 1; i < pos-1; i++)
			{
				enl=enl->get_next();
			}
                        current=enl->get_next();
			enl->set_next(current->get_next());
                        current->get_next()->set_prev(enl);
			delete(current);
		}
                else
                {
                        enl= last;
                        for (i = dim; i > pos+1; i--)//termina en pos-1 xq ya el apuntador aux esta en el primer nodo antes de entrar al ciclo
			{
                            enl= enl->get_prev();
			}		
			current= enl->get_prev();
			enl->set_prev(current->get_prev());
			current->get_prev()->set_next(enl);
			delete(current);
                }
		dim--;	
	}
}

template <class T>
void List<T>:: emptying()
{
		int i, n;
		Node<T> *aux, *nxt;
		
		aux= first;
		n= dim;
		if(aux!=NULL)
		{
			for (i = 0; i < n; i++)
			{
				nxt= aux->get_next();
				delete (aux);
				dim--;
				aux= nxt;
			}

			first= NULL;
			last= NULL;
		 }
}

template <class T>
List<T>::~List()
{
	Node<T> *current, *nxt;
	int i, n;
	
	current=first;
	n=dim;
	
	if (current!=NULL)
	{
		for (i = 0; i < n; i++)
		{
			nxt=current->get_next();
			current->set_next(NULL);
                        current->set_prev(NULL);
			delete(current);
			dim--;
			current=nxt;
		}
		first=NULL;
		last=NULL;
	}	
}

template<class T>
void List<T>::insert(const T& e)//insertOrdenado
	{
	//	cout << "\ninsertar ordenado:\n";
		Node<T> *newn, *q;
		int pos;
		
		newn= new Node<T>;//crea o reserva la memoria para el nodo nvo
		newn->set_info(e);//le asigna el elemento al nvo nodo

		
			if(dim== 0)//si es el unico elemento
			{
			//	cout << "no hay elementos\n";
				newn->set_next(NULL);//coloca el nvo nodo apuntando al primer elemento
				newn->set_prev(NULL);//y como no tiene un nodo anterior, se le coloca apuntando a NULL
				first= newn;//luego, coloca al apuntador prim a apuntar al nvo nodo
				last= newn;
			}
			
			else// sino, si es una posicion intermedia
			{
			//	cout << "si hay elemento\n";

				q= first;//coloca al aux a apuntar a la primera posicion
				pos= 1;//indica que el aux esta en la primera posicion
				while ((q!= NULL) && (e> (q->get_info() )) )
				{
					q= q->get_next();
					pos++;
				}
//cout<<"posicion:"<< pos<<"\n";
				if (pos== 1)//si es en la primera posicion
				{
				//	cout << "va a ingrsar en la primera pos\n";
					first= newn;
					newn->set_next(q);
					q->set_prev(newn);
				}

				else if(pos== dim+1)//si es la ultima posicion
				{
			//		cout << "va a ingrsar en la ultima pos\n";
					q= last;// lo pone en la ultima posicion hasta ahora(antes estaba en null)

					last= newn;
					newn->set_prev(q);
					q->set_next(newn);
				}
				
				else//si es una posicion intermedia
				{
			//		cout << "va a ingrsar en la pos intermedia\n";
					newn->set_next(q);
					newn->set_prev(q->get_prev());
					q->get_prev()->set_next(newn);
					q->set_prev(newn);
				}


			}

			dim++;//aunmenta la cantidad de elementos

}

template <class T>
void List<T>::invest()          //invertir
{
	Node<T> *current, *prv, *nxt;
	int i;
			
	prv=NULL;
	current=first;
	while (current !=NULL)
	{
		nxt=current->get_next();
		current->set_next(prv);
		current->set_prev(nxt);
		prv=current;
		current=nxt;
	}
	last=first;
	first=prv;	
}		

template<class T>
	void List<T>:: invertirSubL(const T& a, const T& b)
	{
		Node<T> *ant, *act, *sig, *aux, *aux2;
		bool band;
		int na, nb;

		aux= first;
		band= false;

		na= this->itsFound(a);
		nb= this->itsFound(b);

		if ( (dim>1) &&(nb>na)&& ((na>0)&&(na<dim)) && ((nb>1)&&(nb<=dim)) )
		{
		
			while (aux->get_info()!= a)
					aux=aux->get_next();
			
			act= aux;
			aux2= aux;
			ant= aux->get_prev();
			aux= ant;
			while(!band)
			{
				if(act->get_info()== b)
					band=true;
				
				sig= act->get_next();
				act->set_next(ant);
				act->set_prev(sig);
				ant= act;
				act= sig;
			}
			
			//aux->ObtSig()->ModifSig(act);
			//act->ModifAnt(aux->ObtSig());
			aux2->set_next(act);
			if(act!=NULL)
				act->set_prev(aux2);
			else
				last= aux2;

			ant->set_prev(aux);
			if(aux!=NULL)
				aux->set_next(ant);
			else
				first= ant;
		}
		
		
		
	}

template<class T>
	void List<T>:: invertSubLint(int a, int b)
	{
		Node<T> *ant, *act, *sig, *aux, *aux2, *bptr;
		bool band;
		int i;

		
		aux= first;
		band= false;
		


		if ( (dim>1) &&(b>a)&& ((a>0)&&(a<dim)) && ((b>1)&&(b<=dim)) )
		{
			aux	=this->consultPtr(a);
			if (aux!=NULL)
			{
				band= true;
			}
			
			
			act= aux;
			aux2= aux;
			ant= aux->get_prev();
			aux= ant;


			bptr= this->consultPtr(b);
			//cout<<endl<<"::::::::::break"<<endl;
			i=1;
			while(band)
			{
				if(act==bptr)
				{
					band=false;
			//		cout<<endl<<"::::::::::TRUE"<<endl;
				}
			//	cout<<endl<<"::::::::::"<<i<<"{ "<<endl;
				sig= act->get_next();
				act->set_next(ant);
				act->set_prev(sig);
				ant= act;
				act= sig;
			//	cout<<endl<<"::::::::::"<<i<<" }"<<endl;
				i++;
			}
			

			aux2->set_next(act);
			if(act!=NULL)
				act->set_prev(aux2);
			else
				last= aux2;

			
			ant->set_prev(aux);
			if(aux!=NULL)
				aux->set_next(ant);
			else
				first= ant;
		}
				
	}


	template<class T>
	void List<T>::imprimir() const 
	{
		Node<T>* aux;
		
		if (this->dim> 0)
		{
			aux= first;
			//cout << "\nlista de ("<<this->longitud()<<") elementos:" << endl;
			while (aux!=NULL)
			{
				cout<<aux->get_info()<<" ";
				//cout << "\tposicion " << i<< ":\t"<< this->consultar(i)<< endl;
				aux= aux->get_next();
			}//cout << "fin de lista, long= "<< this->longitud()<<"\n\n";

		}
		//cout<<endl;
	}
        
        template<class T>
	int List<T>::esSubL(const List &x) const
	{
		Node<T> *aux, *ptr, *pivot;
		bool esSL, band;
		int pos;
		
		pivot= first;
		esSL= false;
		pos= 0;
//cout<<endl;

		if((x.dim== 0)||((this->dim)< (x.dim)))//si la lista x, es mas grande que la lista principal
		{
			pos=-1;//automaticamente NO es sublista
		//	cout<<"::::::::pos= -1"<<endl;
		}
		else//sino
		{
			while ((!esSL)&& (pivot!=NULL))
			{
				ptr= x.first;//pone al ptr en el primer elemento de la lista x
			//	cout<<"::::::::ptr:"<<ptr->ObtElem()<<endl;
				band= false;//asigna falso para indica que aun no ha encontrado el primer elemento de la lista x en la lista principal
				while ((!band) && (pivot!=NULL))
				{
					pos++;
					if(pivot->get_info()== ptr->get_info())
					{
						band= true;
				//		cout<<"::::::::aux:"<<aux->ObtElem()<<endl;
					}
					else
						pivot=pivot->get_next();
				}


				if(band)//si encontro el primer elemento de la lista x en la lista base
				{
					esSL= true;
					
					//si la lista x aun cabe en la lista base
				//	cout<<"::::::::dimension restante"<<((this->ch)-pos)- (x.ch)<<endl;
					if (((this->dim+1)-pos)>= (x.dim))
					{
						aux= pivot;
						//mientras, no sea el final de ninguna de las dos lista
						//y los elementos que se esten comparando sean iguales
					//	cout<<"::::::::while{"<<endl;
						while( (aux!=NULL)&&(ptr!=NULL) && (esSL))
						{
					//		cout<<"::::::::ptr:"<<ptr->ObtElem()<<endl;
					//		cout<<"::::::::aux:"<<aux->ObtElem()<<endl;
							if(aux->get_info()== ptr->get_info())//si los elementos son iguales
							{
								aux=aux->get_next();//compara el sig
								ptr=ptr->get_next();//compara el sig
							}
							
							else
							{
								esSL= false;//le dice que no es SubLista
				//				cout<<"::::::::false"<<endl;
							}

						}
				//		cout<<"::::::::}Fwhile"<<aux->ObtElem()<<endl;
					}
					else
					{
						esSL= false;//entonces, no es sublista
				//		cout<<"::::::::false"<<endl;
					}

				}
				else//si no encontro el primer elemento de la lista x en la lista base
				{
					esSL= false;//entonces, no es sublista
				//	cout<<"::::::::false"<<endl;
				}

				if (pivot !=NULL)
					pivot= pivot->get_next(); 
			}
			
				
		}
			
		
		if (!esSL)
		{
			pos=-1;
		//	cout<<"::::::::pos= -1"<<endl;
		}

		return pos;//retorna la posicion donde empieza la subLista

	}
        
template <class T>
int List<T>::ocurrencia(const List<T> &listB) const
{
    Node<T> *primB, *auxA, *auxB;
    int i=1, repeat=0;
    bool band=true;
    
    
    auxB=listB.first;
    primB=listB.first;
    auxA=this->first;
    while(band)
    {
        
        if(auxA->get_info()!=auxB->get_info() || auxA->get_next()==NULL)
        {
            if(auxA->get_next()==NULL)
                repeat++;
            
            auxA=this->first;
            primB=primB->get_next();
            auxB=primB;
            i++;
            //cout<<i;
            if(listB.dim-i < this->dim-1)
                band=false;
        }
        else
        {
            auxB=auxB->get_next();
            auxA=auxA->get_next();
        }
    }
    return (repeat);
} 

template<class T>
	void List<T>::eliminarSL(const List &x)
	{
		int i, n, sl;
		Node<T>* aux;

		
		sl= this->esSubL(x);
		if (sl>0)
		{
			aux= this->consultPtr(sl);
			n= x.length();
			for(i=1; i<= n; i++)
				this->deletePtr(aux);
		}

	}

template<class T>
	List<T> List<T>:: generarSL(const T& a, const T& b)
	{
		Node<T>* aux;
		int i, x, y;
		List<T> nvo;
		

		x= this->itsFound(a);//busca los elementos
		y= this->itsFound(b);

		if ((x>0) && (y>0)&& (x<=y))//verifica que amos elementos estan en la lista y que el 'a' esta primero que el 'b'
		{
		
			aux= this->first;
			for (i = 1; i < x; i++)//recorre los nodos hasta el elemento 'a'
				aux= aux->get_next();
			
			for (i = 1; i <=((y-x)+1) ; i++)
			{
				nvo.insert(aux->get_info(), i);
				aux= aux->get_next();
				//nvo->ModifElem(this->consultar(i))
			}

		}
		return (nvo);
	}

template<class T>
List<T> List<T>:: generarSLint(int x, int y)
{
    Node<T>* aux;
    int i;
    List<T> nvo;

    if ((x<=dim)&&(x>0) && (y>0)&&(y<=dim)&& (x<=y))//verifica que amos elementos estan en la lista y que el 'a' esta primero que el 'b'
    {
        aux= this->first;
        for (i = 1; i < x; i++)//recorre los nodos hasta el elemento 'a'
            aux= aux->get_next();
        for (i = 1; i <=((y-x)+1) ; i++)
        {
            nvo.insert(aux->get_info(), i);
            aux= aux->get_next();
        }
    }
    return (nvo);
}

template<class T>
	int List<T>:: estaOrdenada() const
	{	//1- si esta ordenada de forma ascendente, 2- si esta ordenada
		// de forma descendente, 0- si esta desordenada

	
		Node<T>* ant, *aux;
		int orden, op;

		orden= 1;//asume que esta ordenada ascendentemente
		ant= first;
		aux= ant->get_next();
		while ((orden==1)&& (aux!=NULL))
		{
			if( ant->get_info()<= aux->get_info())
			{
				ant= aux;
				aux= aux->get_next();
			}

			else
				orden= 2;//asume que esta ordenada descendentemente
		}

		ant= first;
		aux= ant->get_next();
		while ((orden==2)&& (aux!=NULL))
		{
			if( ant->get_info()>= aux->get_info())
			{
				ant= aux;
				aux= aux->get_next();
			}

			else
				orden= -1;//no esta ordenada
		}

		return (orden);

	}

template<class T>
	T List<T>::mayorElem() const
	{	
		Node<T>* aux;
		T mayor;

		if (dim>0)
		{
			aux= first->get_next();
			mayor= first->get_info();
			while (aux!= NULL)
			{
				if (aux->get_info()> mayor)
					mayor=aux->get_info();
				
				aux= aux->get_next();
			}
		}

		return (mayor);
	}

template<class T>
	T List<T>:: menorElem() const
	{	
		Node<T>* aux;
		T menor;
		if (dim>0)
		{
			aux= first->get_next();
			menor= first->get_info();
			while (aux!= NULL)
			{
				if (aux->get_info()< menor)
					menor=aux->get_info();
				
				aux= aux->get_next();
			}
		}
		return (menor);
	}

template<class T>
	int List<T>:: menorPos() const
	{
		int  pos=-1, i;
		Node<T>* aux;
		T menor;
		
		if (dim>0)
		{
			aux= first->get_next();
			menor= first->get_info();
			pos=1;
			i=2;
			while (aux!= NULL)
			{
				
				if (aux->get_info()< menor)
				{
					menor=aux->get_info();
					pos=i;
				}
				aux= aux->get_next();
				i++;
			}
		}
		return pos;
	}

template<class T>
	int List<T>:: mayorPos() const
	{
		int  pos=-1, i;
		Node<T>* aux;
		T mayor;
		
		if (dim>0)
		{
			aux= first->get_next();
			mayor= first->get_info();
			pos=1;
			i=2;
			while (aux!= NULL)
			{
				
				if (aux->get_info()> mayor)
				{
					mayor=aux->get_info();
					pos=i;
				}
				aux= aux->get_next();
				i++;
			}
		}
		return pos;
	}

template<class T>
List<T> List<T>:: intersection(const List<T> &li)
	{
		Node<T>* q;
		int i;
		List<T> lnew;

		q= li->first;
		i=1;

		while(q!= NULL)
		{
			if ((this->itsFound(q->get_info())> 0) && (lnew->itsFound(q->get_info())< 0))
			{
				lnew->insert(q->get_info, i);
				
				i++;
			}
			q= q->get_next();
		}
		return (lnew);

	}

template<class T>
	void List<T>:: mezclarL(const List &l1, const List &l2)
	{
		Node<T> *aux, *aux2;


		this->emptying();
		aux2= l2.first;
		aux=l1.first;

		while(aux!= NULL)
		{
			this->insert(aux->get_info());
			aux= aux->get_next();
		}

		while(aux2!= NULL)
		{
			//if(lr->esta(aux2->ObtElem())< 0){
			this->insert(aux2->get_info());
			aux2= aux2->get_next();
			//}
		}

	}

template<class T>
	void List<T>:: swap(int a, int b)const
	{
		int i;
		Node<T> *aux1, *aux2, *auxS, *auxA;

		if ((a!=b)&&(a>0)&&(a<=dim)&&(b>0)&&(b<=dim))
		{
			aux2= this->first;
			if (a>b)
			{
				a=a+b;
				b=a-b;
				a=a-b;
			}
			for (i = 1; i < b; i++)//recorre todos los nodos(confirmado)
			{
				if (i==a)
					aux1=aux2;

				aux2= aux2->get_next();
			}

			///nodo1
			if (aux1->get_prev()!=NULL)
				aux1->get_prev()->set_next(aux2);
			if (aux1->get_next()!=NULL)
				aux1->get_next()->set_prev(aux2);
			auxS= aux1->get_next();
			auxA= aux1->get_prev();	
			aux1->set_next(aux2->get_next());
			aux1->set_prev(aux2->get_prev());
			
			///nodo2
			if (aux2->get_prev()!=NULL)
				aux2->get_prev()->set_next(aux1);
			if (aux2->get_next()!=NULL)
				aux2->get_next()->set_prev(aux1);
			aux2->set_next(auxS);
			aux2->set_prev(auxA);
			
			
		}

	}

template<class T>
bool List<T>::operator==(const List<T>& li) const
{
	Node<T> *q, *k;
	bool equal;
	
	q= this->first;
	k= li.first;
	equal= true;
		
	if (this->dim != li.dim)
		equal = false;
		 
		else
		{
			while( (q!=NULL)&&(k!=NULL) && (equal))//mientras no se acaben los elementos de ambas listas
			{
				if(q->get_info()== k->get_info())//si los elementos son iguales
				{
					q=q->get_next();//compara el sig
					k=k->get_next();//compara el sig
				}
				
				else
					equal= false;//le dice que no son iguales
			}
		}

	return equal;
}

template<class T>
bool List<T>::operator!=(const List<T>& li) const
	{
		Node<T> *q, *k;
		bool equal;
		
		q= this->first;
		k= li.first;
		equal= true;
		
		if (this->dim!= li.dim)
			equal= false;
		 
		else
		{
			while( (q!=NULL)&&(k!=NULL) && (equal))//mientras no se acaben los elementos de ambas listas
			{
				if(q->get_info()== k->get_info())//si los elementos son iguales
				{
					q=q->get_next();//compara el sig
					k=k->get_next();//compara el sig
				}
				
				else
					equal = false;//le dice que no son iguales
			}
		}

		return (!equal);
}

template<class T>
List<T> List<T>::operator+(const List<T>& li) const
{
		Node<T> *q, *k;
		List<T> lnew;

		k= li.first;
		q=this->first;
		while(q!= NULL)
		{
			lnew.insert(q->get_info(), lnew.dim+1);
			q= q->get_next();
		}
		while(k!= NULL)
		{
			lnew.insert(k->get_info(), lnew.dim+1);
			k= k->get_next();
		}

		return lnew;
}

template<class T>
List<T> List<T>::operator-(const List<T>& li) const
{
		/** retona una lista con todos los elementos de la lista original, menos, los elementos
		 *	de l2 que esten en esa lista original*/
		Node<T> *q, *k;
		List<T> lnew;

		lnew= *this;
		q= lnew.first;
		k= li.first;

		while (k != NULL)//mientras el primer pivot no llegue al final
		{

			if (q==NULL)//si el segundo pivot llega al final, entonces...
			{
				k= k->get_next();//el primer pivot se mueve al siguiente
				if (k!=NULL)//y si aun el primer pivot no ha llegado al final, entocnes
					q=lnew.first;//reseteo el segundo pivot
			}
			///evaluo
			if (((q!=NULL) && (k!=NULL))&&(k->get_info()== q->get_info()))//si encontro el elemnto de l2 en lr
				lnew.deletePtr(q);//se elimina
			
			///fin de la evaluacion
			if (q!=NULL)//si el segundo pivot no ha llegado al final, entonces
				q= q->get_next();//se mueve el segundo pivot a la sig posicion
		}
		return lnew;
}

template<class T>
void List<T>::operator=(const List<T>& ly)
{
		///- cout<<"sobrecarga(= ... <<lista>>)/";
		Node<T> *aux;
		//cout<<endl<<"sobrecargaAsignacion('=')/";

		//cout<<"vaciarListaMadre()/";
		this->emptying();
		//cout<<"ListaMAdraVacia/";
		aux= ly.first;
		//cout<<"LlenarListaMadre/";
		while(aux!= NULL)
		{
			this->insert(aux->get_info(), this->dim+1);
			aux= aux->get_next();
		}
		//cout<<"ListaMadreLLena/";
		//cout<<"--SucessFull"<<endl;
		///- cout<<"FsobreCarga/";
}

template<class T>
void List<T>::insertPtr(Node<T> *x, const T& e)//el ptr debe quedar alante del elemento que se va a insertar
{
		///cout<<"estoy escribiendo desde el insertar ptr, 'inicio'"<<endl;
		Node<T> *newn, *prv;
		
		newn= new Node<T>;//crea o reserva la memoria para el nodo nvo
		newn->set_info(e);//le asigna el elemento al nvo nodo

		///cout<<"estoy escribiendo desde el insertar ptr, 'antesala a los casos'"<<endl;
 /*caso1*/	if(this->first== NULL)//si es el unico elemento
			{
				newn->set_next(NULL);//coloca el nvo nodo apuntando a NULL
				newn->set_prev(NULL);//y como no tiene un nodo anterior, se le coloca apuntando a NULL
				first= newn;//luego, coloca al apuntador prim a apuntar al nvo nodo
				last= newn;
			}
					
 /*caso2*/	else if(x== NULL)//si es la ultima posicion
			{
				///cout<<"estoy escribiendo desde el insertar ptr, 'caso3'"<<endl;
				newn->set_next(NULL);//como no tiene un nodo proximo, se le coloca apuntando a NULL
				newn->set_prev(last);//coloca el nvo nodo apuntando al que era el ultimo elemento
				last->set_next(newn);//luego, coloca al apuntador de elq era el ultimo elemento a apuntar al nvo nodo
				last=newn; 
			}

 /*caso3*/	else if (x->get_prev()==NULL)//si es la primera posicion
			{
				newn->set_next(x);//coloca el nvo nodo apuntando al primer elemento
				newn->set_prev(NULL);//y como no tiene un nodo anterior, se le coloca apuntando a NULL
				x->set_prev(newn);
				first= newn;//luego, coloca al apuntador prim a apuntar al nvo nodo
			}
			
 /*caso4*/	else// sino, si es una posicion intermedia
			{
					prv= x->get_prev();
					x->set_prev(newn);
					newn->set_next(x);//ahora nvo apunta al siguien del anterior
					newn->set_prev(prv);//ahora, coloca al nvo nodo a apuntar a su anterior (ant)
					prv->set_next(newn);
			}

			//succes_full
			dim++;//aunmenta la cantidad de elementos		
}


template <class T>
void List<T>:: deletePtr(Node<T>* x)
	{
		Node<T> *y;
		
		if (x!=NULL)
		{
			//se elimina
				if((x->get_next()==NULL) && (x->get_prev()==NULL))//si queda un solo elemento
				{
					delete (x);
					first= NULL;
					last= NULL;

				}
				
				else if (x->get_prev()==NULL)//si es el primer elemento
				{
					y= x->get_next();
					delete (x);
					first= y;
					first->set_prev(NULL);
					
				}

				else if(x->get_next()==NULL)//si es el ultimo elemento
				{
					y= x->get_prev();
					delete (x);
					last= y;
					last->set_next(NULL);
					
				}

				else//si es un elemento intermedio
				{
					y=x->get_prev();

					y->set_next(x->get_next());
					x->get_next()->set_prev(x);
					delete(x);
				}
				
				dim--;
		}
		
			
}

template <class T>
Node<T>* List<T>:: thisPtr(const T& e) const
{
		Node<T>* q;
		
		q= first;
		while ((q!= NULL) && (q->get_info()!= e))
			q= q->get_next();

		return (q);
}

template<class T>
Node<T>* List<T>::consultPtr(int pos) const
{	
	int i;
	Node<T>* q=NULL;

	if ((pos>0)&&(pos<= this->dim))
	{
		q= first;
		for (i = 1; i < pos; i++)//recorre todos los nodos(confirmado)
				q= q->get_next();
	}
	return (q);
}

template<class T>
	void List<T>:: mayorElem(T *mayor,int *n)
	{
		Node<T>* aux;
		
		aux= first;
		
		mayoRecursivo(aux , mayor, n);
		
		
	}

template<class T>
	void List<T>:: mayoRecursivo(Node<T>* aux,T *e, int *n)
	{
		if (aux->get_next()== NULL)
		{
			(*e)= aux->get_info();
			(*n)= 1;
		}
		else
		{
			mayoRecursivo(aux->get_next(), e, n);
			if ((aux->get_info())>(*e))
			{
				*e=aux->get_info();
				(*n)= 1;
			}
			else if (aux->get_info()==(*e))
			{
				(*n)++;
			}
			
			
		}

	}

template<class T>
	void List<T>:: mezclarL2(const List &l1, const List &l2)
	{
		Node<T> *aux, *aux2;

///		*esto es con listas ordenadas. la primera en orden ascendente,
///		la segunda en orden descendente

		this->emptying();
		aux=l1.first;
		aux2= l2.last;
		
		
		/*l1->imprimir();
		l2->imprimir();*/
		
		while( ((aux!= NULL) || (aux2!= NULL)) )
		{
			if (aux== NULL)//si se acabaron los elementos de la primera lista
			{
				this->insert(aux2->get_info(), this->length()+1);
				aux2= aux2->get_prev();
			}
			else if (aux2== NULL)//si se acabaron los elementos de la segunda lista
			{
				this->insert(aux->get_info(), this->length()+1);
				aux= aux->get_next();
			}
			else//si aun quedan elementos en ambas listas
			{
				if (aux->get_info()<= aux2->get_info())//si el elemento de la lista1 es menor o igual al de la lista2
				{
					this->insert(aux->get_info(), this->length()+1);//inserta el elemento de la lista1
					aux= aux->get_next();//y avanza el pivot de la lista 1 al siguiente
				}
				else//si el elemento de la lista 2 es menor que el de la lista1
				{
					this->insert(aux2->get_info(), this->length()+1);//inserta el elemento de la lista 2
					aux2= aux2->get_prev();//y avanza el pivoy de la lista2 al anterior
				}
				
				
			}
			
			
			
			
		}

		
	}

template<class T>
	void List<T>:: ordenar()
	{

		this->QuickSort(1, this->length());


	}


	template<class T>
	void List<T>:: QuickSort(int izq, int der)//izq debe recibir la primera posicion, der la ultima
	{
		Node<T> *ei, *ej, *eaux;
		int i,j,aux,pivote;
		i=izq;
		j=der;
		aux=(izq+der)/2;
		pivote= this->consult(aux);

		eaux= new Node<T>;//crea o reserva la memoria para el nodo nvo

		ei= this->consultPtr(i);
		ej= this->consultPtr(j);
			do{
				while(ei->get_info() < pivote)
				{
					if (ei != NULL)
					{
						i++;
						ei= ei->get_next();
					}
				}	
					while(ej->get_info() > pivote)
					{
						if (ej != NULL)
						{
							j--;
							ej= ej->get_prev();
						}
					}
						if(i <= j)
						{
							eaux->set_info(ei->get_info());
							ei->set_info(ej->get_info());
							ej->set_info(eaux->get_info());
							i++;
							j--;
						}
			}while(i <= j);
			
			if(izq < j)
				this->QuickSort(izq,j);
			if(i < der)
				this->QuickSort(i,der);
	}

//ejercicio 1 de la practica de estructuras enlazadas
template <class T>
List<T> List<T>::codification()
{
    int i=1,cont;
    T elem;
    cont=this->dim/4;
    Node<T> *q, *p,*x, *y;
    if(this->dim%2==0)
    {
        q=this->last;
        
    }
    else
    {
        q=this->last->get_prev();
    }
    
    p=this->first->get_next();
    
    while(i<=cont)
    {
        x=p->get_next()->get_next();
        y=q->get_prev()->get_prev();
        elem=p->get_info();
        p->set_info(q->get_info());
        q->set_info(elem);
        p=x;
        q=y;
        i++;
    }
}

#endif
