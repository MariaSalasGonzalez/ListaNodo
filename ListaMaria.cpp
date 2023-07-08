#pragma once
#include <iostream>
#include <sstream>
#include"Persona.h"

//-----Clase Nodo-----
template<class T>
class Nodo {

private:
	T * objetoPtr;
	Nodo* siguiente;

public:
	Nodo(T*, Nodo*);
	void setObjetoPtr(T*);
	void setSiguiente(Nodo*);
	T* getObjetoPtr();
	Nodo* getSiguiente();
	virtual ~Nodo();
};

template <class T>
Nodo<T>::Nodo(T* ptr, Nodo<T>* nod) :
	objetoPtr(ptr),
	siguiente(nod) {
}

template<class T>
void Nodo<T>::setObjetoPtr(T* ptr) {
	objetoPtr = ptr;
}

template<class T>
void Nodo<T>::setSiguiente(Nodo<T>* nod) {
	siguiente = nod;
}

template<class T>
T* Nodo<T>::getObjetoPtr() {
	return objetoPtr;
}

template<class T>
Nodo<T>* Nodo<T>::getSiguiente() {
	return siguiente;
}

template<class T>
Nodo<T>::~Nodo() {
	// delete objetoPtr; //  <<==Ojo  Aquí nada hay que borrar
}

//--------------Clase Lista------------
template<class T>
class Lista {
  private:
	Nodo<T>* ppio;

  public:
	Lista();
	void ingresarDePrimero(T*);
	void ingresarDeUltimo(T*);
	Nodo<T>* creaNodo(T*);    //  <<= ojo este método es nuevo..
	void invertir();
	T* buscar(int);     // <<==OJO es lo mismo que retornaElemento.?
	bool eliminaPrimero();
	T* eliminaUltimo();  //  <<== (Facil de implementa..).
	T* retornaElemento(int lug);
	string toString();
	virtual ~Lista();

	//GestorArchivos
	T* recuperar();
	T* recuperarPorCodigo(string); // ???????
	void inicializarActual();
	int obtenerValor();
};

template <class T>
Lista<T>::Lista(){
	ppio = NULL;
}


template <class T>
void Lista<T>::ingresarDePrimero(T* ptr) {
	ppio = new Nodo<T>(ptr, ppio);
}

template <class T>
void Lista<T>::ingresarDeUltimo(T* ptr) {  // <<== pequeño y sencillo.
	Nodo<T>* p = ppio;         // Solo le hice un par de cambios pequeños.
	if (ppio == NULL) {
		ingresarDePrimero(ptr);
	}else {
		Nodo<T>* nuevo = this->creaNodo(ptr);
		while (p->getSiguiente() != NULL) 
			   p = p->getSiguiente();
		p->setSiguiente(nuevo);
	}
}

template <class T>    
Nodo<T>* Lista<T>::creaNodo(T* obj) {  //   <<== OJO (Es pequeño y sencillo).
	Nodo<T>* nuevo = new Nodo<T>(obj, NULL);
	return nuevo;
}

template <class T>
T* Lista<T>::buscar(int lug) {
	//  Este método es lo mismo que retornaElemento();
	return NULL;
}

template <class T>
bool Lista<T>::eliminaPrimero() {  //   <<== ojo
	// Este método es muy pequeño
	// es solo eliminar el primero..
	Nodo<T>* p = ppio;
	if (ppio != NULL) {
		p = ppio->getSiguiente();
		delete ppio;
		ppio = p;
		return true;
	}
	return false;
}

template <class T>
T* Lista<T>::eliminaUltimo() {  // Elimina el último nodo pero retorna el objeto.
	T* objPtr = NULL;
	Nodo<T>* borrado = NULL;
	Nodo<T>* p = ppio;
	if (ppio != NULL) {  // Hay por lo menos uno..
		if (ppio->getSiguiente() == NULL) {  // Entonces elimina primero
			objPtr = ppio->getObjetoPtr();
			this->eliminaPrimero();
		}else {
			while (p->getSiguiente()->getSiguiente() != NULL) {
				p = p->getSiguiente();
			}
			objPtr = p->getSiguiente()->getObjetoPtr();
			borrado = p->getSiguiente();
			p->setSiguiente(NULL);
			delete borrado;  // Eliminar el último Nodo.
		}
		return objPtr;
	}
	return NULL;
}

template<class T>
void Lista<T>::invertir() {  // Al rato sirve...
	T* objPtr = NULL;
	Nodo<T>* p = NULL;
	Nodo<T>* Po = ppio;
	if (ppio != NULL && ppio->getSiguiente() != NULL) {  // Por lo menos hay dos..
		while (Po->getSiguiente() != NULL) {
			p = Po->getSiguiente();
			objPtr = p->getObjetoPtr();
			Po->setSiguiente(p->getSiguiente());
			delete p;
			this->ingresarDePrimero(objPtr);
		}
	}
}

//template <class T>
//void Lista<T>::invertir() {  //  <<== ojo (NO lo revisé)
//	Nodo<T> *a = ppio;         //  <<== Lo veo Laaaaarrrrgo
//	Nodo<T> *aux;
//	if (a != NULL) {
//		aux = a->getSiguiente();
//	}
//	while (aux != NULL) {
//		a->setSiguiente(aux->getSiguiente());
//		aux->setSiguiente(ppio);
//		ppio = aux;
//		aux = a->getSiguiente();
//	}
//}


template <class T>
T* Lista<T>::retornaElemento(int lug) {  // <<== ojo (ya listo).
	int cont = 1;
	Nodo<T>* p = ppio;
	while (p != NULL && cont < lug) {
		p = p->getSiguiente();
		cont++;
	}
	if (p == NULL)  // <<== (un pequeño cambio por acá).
		return NULL;
	if (cont == lug) {
		return p->getObjetoPtr();
	}
}

template <class T>
string Lista<T>::toString() {
	Nodo<T>* p = ppio;
	int cont = 1;
	stringstream s;
	s << "-------------LISTADO--------------" << endl;
	if (p == NULL) {
		s << "No hay elementos en la lista" << endl;
	}else {
		while (p != NULL) {
			s << "No. " << cont << " ---> " << *p->getObjetoPtr() << endl;
			p = p->getSiguiente();
			cont++;
		}
	}
	s << "-----------------------------------" << endl;
	return s.str();
}

template <class T>
Lista<T>:: ~Lista() { // <<==ojo (estaba bien)..
	Nodo<T> *p = ppio;
	Nodo<T> *aux;
	while (p != NULL) {
		aux = p->getSiguiente();
		delete p;
		p = aux;
	}
	ppio = NULL;
}

//-----GestorArchivos----- Esto es particular del grupo
template <class T>
T* Lista<T>::recuperar() {   // <<== ojo (no lo revisé)
	T* p = ppio->getObjetoPtr();
	ppio = ppio->getSiguiente();
	return p;
}

template <class T>
T* Lista<T>::recuperarPorCodigo(string nombre) {  // <<== ojo (no lo revisé)
	T* p;
	inicializarActual();
	while (ppio != NULL) {
		p = ppio->getObjetoPtr();
		if (p->getNombre() == nombre) {
			return p;
		}
		ppio = ppio->getSiguiente();
	}
	return NULL;
}

template <class T>
void Lista<T>::inicializarActual() { // <<== ojo (no lo revisé)
	ppio = ppio;    //  <<== no tiene mucho sentido;
}

template <class T>
int Lista<T>::obtenerValor() {
	return T;       //  <<==error..
}

int main() {
	cout << "-------------Probar Lista generica-----------" << endl;
	cout << "-----------Lista Simplemente Enlazada--------" << endl;
	cout << "------------o Simplemente Eslabonada---------" << endl;
	cout << "---------------------------------------------" << endl;

	cout << "Creacion de una lista Generica que se utilizara para" << endl;
	cout << "               Ingresar personas dinamicas          " << endl;
	cout << "----------------------------------------------------" << endl;
	Lista<Persona>* list = new Lista<Persona>();
	cout << endl << endl;
	cout << "---------------Creacion de Personas-----------------" << endl;
	cout << "----------------------------------------------------" << endl;
	Persona* per1 = new Persona("1111", "Maria", 20);
	Persona* per2 = new Persona("2222", "Juan", 21);
	Persona* per3 = new Persona("3333", "Xinia", 22);
	Persona* per4 = new Persona("4444", "Pedro", 23);
	Persona* per5 = new Persona("5555", "Mateo", 22);
	Persona* per6 = new Persona("6666", "Magdalena", 23);

	cout << "---------------Ingreso de Personas-----------------" << endl;
	cout << "-------------------Al contenedor-------------------" << endl;
	list->ingresarDePrimero(per2);
	list->ingresarDePrimero(per1);
	list->ingresarDeUltimo(per3);
	list->ingresarDeUltimo(per4);
	list->ingresarDeUltimo(per5);
	list->ingresarDeUltimo(per6);

	cout << "---------------Imprimir Listado--------------------" << endl;
	cout << list->toString() << endl;
	cout << "---------------------------------------------------" << endl;

	system("pause");
	system("cls");
	cout << endl << endl;
	cout << "-------------------Eliminar el Primero--------------" << endl;
	list->eliminaPrimero();
	cout << "------------Listado con Primero Eliminado-----------" << endl;
	cout << list->toString() << endl;
	cout << "----------------------------------------------------" << endl;

	system("pause");
	system("cls");
	cout << endl << endl;
	cout << "-------------------Eliminar el Ultimo---------------" << endl;
	Persona* per = list->eliminaUltimo();
	cout << "------------Listado con Ultimo Eliminado-----------" << endl;
	cout << list->toString() << endl;
	cout << "----------------------------------------------------" << endl;
	cout << "----------------------------------------------------" << endl;
	cout << endl;
	cout << "El que fue eliminado es..." << endl;
	cout << *per << endl;
	delete per;   // Hay que eliminarla dado que el método retorna la persona.
	              
	system("pause");
	system("cls");
	cout << endl << endl;
	cout << "-------------------Invertir la lista----------------" << endl;
	list->invertir();
	cout << "------------Listado con Lista Invertida-----------" << endl;
	cout << list->toString() << endl;
	cout << "----------------------------------------------------" << endl;

	system("pause");
	return 0;
}
