#pragma once
#include <vector>

template <class T>
class Nodo {
    protected:
        T dato;
        Nodo<T>* izquierdo;
        Nodo<T>* derecho;
    public:
        Nodo();
        Nodo(T dato);
        ~Nodo();
        T getDato();
        void setDato(T dato);
        Nodo<T>* getIzq();
        Nodo<T>* getDer();
        void setIzq(Nodo<T>* izquierdo);
        void setDer(Nodo<T>* derecho);
        bool esHoja();
        unsigned long long altura();
        unsigned long long tama();
        long long buscar(T dato);
        std::vector<T> preorden();
    private:
        long long buscar(T dato, long long profundidad);
        void preorden(std::vector<T>& v);
};
#include "nodo.hxx"