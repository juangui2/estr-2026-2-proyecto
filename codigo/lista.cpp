#include <iostream>
#include "Lista.h"



Lista::Lista() {
    cabeza = nullptr;
}

Nodo* Lista::buscarProducto(int codigo) const{

    Nodo* actual = cabeza;

    while(actual != nullptr && actual->codigo != codigo){
        actual = actual->sig;
    }
    return actual;

}

bool Lista::agregarProducto(int codigo, string& nombre, int cantidad){
    bool agregado = false;

    if(buscarProducto(codigo) == nullptr){

        Nodo* nuevo = new Nodo;
        nuevo ->codigo = codigo;
        nuevo ->cantidad = cantidad;
        nuevo ->nombre = nombre;
        nuevo->sig = cabeza;
        cabeza = nuevo;

        agregado = true;
    }
    
    return agregado;
}

bool Lista::eliminarProducto(int codigo){
    bool eliminado = false;
    Nodo* actual = cabeza;
    Nodo* anterior = nullptr;

    while(actual != nullptr && actual ->codigo != codigo){

        anterior = actual;
        actual = actual ->sig;

    }

    if(actual != nullptr){
        if(actual == cabeza){
            cabeza = actual ->sig;
        }
        else{
            anterior ->sig = actual ->sig;

        }

        delete actual;
        eliminado = true;
    }

    return eliminado;
}

