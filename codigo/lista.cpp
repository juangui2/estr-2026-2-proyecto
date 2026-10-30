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


//la idea de consultar producto es que nombre y cantidad que le pasamos a la funcion sean variables que creamos en las que vamos a almacenar el nombre 
//y la cantidad del producto que necesitamos si es que existe, y esas variables ps las usaremos para lo que necesitemos, ejemplo:
//if (existe) {
//    printf("%s ,%d", nombre, cantidad);
//} else {
//    printf("no existe");
//}


bool Lista::consultarProducto(int codigo, string& nombre, int& cantidad) const{
    Nodo* encontrado = buscarProducto(codigo);
    bool existe = false;

    if (encontrado != nullptr){
        bool existe = true;
        nombre = encontrado ->nombre;
        cantidad = encontrado ->cantidad;
    }

    return existe;
}


bool Lista::reponerProducto(int codigo, int cantidad){
    bool repuesto = false;
    Nodo* reponer = buscarProducto(codigo);

      if (reponer != nullptr) {
        reponer->cantidad += cantidad;
        repuesto = true;
    }

    return repuesto;
}

void Lista::listarProductos() const{
    Nodo* actual = cabeza;

    while(actual != nullptr){
        printf("%d", actual ->codigo);
        printf("%s", actual ->nombre);
        printf("%d", actual ->cantidad);

        actual = actual ->sig;
    }
}

void Lista::liberarLista(){

    while(cabeza != nullptr){
        Nodo* muerto = cabeza;
        cabeza = cabeza ->sig;
        delete muerto;
    }

}

Lista::~Lista(){
    liberarLista();
}