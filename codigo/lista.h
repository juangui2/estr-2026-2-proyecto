// Autores: Juan Guillermo Espinosa 9038654, Miguel Angel Lenis 9040913, Juan Jose Arenas 9035047

#ifndef LISTA_H
#define LISTA_H

#include <string>
using namespace std;

struct Nodo {
    int codigo;
    string nombre;
    int cantidad;
    Nodo* sig;
};

class Lista {
private:
    Nodo* cabeza;

    Nodo* buscarProducto(int codigo) const;

public:
    Lista();
    ~Lista();

    bool agregarProducto(int codigo, const string& nombre, int cantidad);
    bool eliminarProducto(int codigo);
    bool consultarProducto(int codigo, string& nombre, int& cantidad) const;
    bool reponerProducto(int codigo, int cantidad);
    void listarProductos() const;
    void liberarLista();
};

#endif