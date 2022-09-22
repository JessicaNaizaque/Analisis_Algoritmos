#include "nodo.h"

#include <queue>
template <class T>
Nodo<T>::Nodo() {
    this->izquierdo = NULL;
    this->derecho = NULL;
}
template <class T>
Nodo<T>::Nodo(T dato) {
    this->izquierdo = NULL;
    this->derecho = NULL;
    this->dato = dato;
}
template <class T>
Nodo<T>::~Nodo() {
    if (this->izquierdo != NULL) {
        delete this->izquierdo;
        this->izquierdo = NULL;
    }
    if (this->derecho != NULL) {
        delete this->derecho;
        this->derecho = NULL;
    }
}
template <class T>
Nodo<T>* Nodo<T>::getIzq() {
    return this->izquierdo;
}
template <class T>
Nodo<T>* Nodo<T>::getDer() {
    return this->derecho;
}
template <class T>
void Nodo<T>::setIzq(Nodo<T>* izquierdo) {
    this->izquierdo = izquierdo;
}
template <class T>
void Nodo<T>::setDer(Nodo<T>* derecho) {
    this->derecho = derecho;
}
template <class T>
T Nodo<T>::getDato() {
    return this->dato;
}
template <class T>
void Nodo<T>::setDato(T dato) {
    this->dato = dato;
}
template <class T>
bool Nodo<T>::esHoja() {
    return (this->izquierdo == NULL && this->derecho == NULL);
}

template <class T>
unsigned long long Nodo<T>::altura() {
    unsigned long long alt;
    if (this->esHoja()) {
        alt = 0;
    } else {
        unsigned long long alt_izq = -1, alt_der = -1;
        if (this->izquierdo != NULL)
            alt_izq = (this->izquierdo)->altura();
        if (this->derecho != NULL)
            alt_der = (this->derecho)->altura();
        if (alt_izq > alt_der)
            alt = alt_izq + 1;
        else
            alt = alt_der + 1;
    }
    return alt;
}

template <class T>
unsigned long long Nodo<T>::tama() {
    unsigned long long tam;
    if (this->esHoja()) {
        tam = 1;
    } else {
        unsigned long long tam_izq = 0, tam_der = 0;
        if (this->izquierdo != NULL)
            tam_izq = (this->izquierdo)->tama();
        if (this->derecho != NULL)
            tam_der = (this->derecho)->tama();
        tam = tam_izq + tam_der + 1;
    }
    return tam;
}

template <class T>
long long Nodo<T>::buscar(T dato) {
    return this->buscar(dato, 0);
}
template <class T>
long long Nodo<T>::buscar(T dato, long long profundidad) {
    if (dato == this->dato) {
        return profundidad;
    }
    if (this->esHoja()) {
        return -1;
    }
    if (dato < this->dato) {
        if (this->izquierdo != NULL) {
            return (this->izquierdo)->buscar(dato, profundidad + 1);
        }
    } else {
        if (this->derecho != NULL) {
            return (this->derecho)->buscar(dato, profundidad + 1);
        }
    }
    return -1;
}

template <class T>
std::vector<T> Nodo<T>::preorden() {
    std::vector<T> v;
    this->preorden(v);
    return v;
}
template <class T>
void Nodo<T>::preorden(std::vector<T>& v) {
    v.push_back(this->dato);
    if (this->izquierdo != NULL)
        (this->izquierdo)->preorden(v);
    if (this->derecho != NULL)
        (this->derecho)->preorden(v);
}