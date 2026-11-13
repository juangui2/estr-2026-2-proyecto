#include <cstdio>
#include "MapInventario.h"

bool MapInventario::agregarProducto(int codigo,const string & nombre, int cantidad ){
    bool agregado = false;

    if(productos.find(codigo) == productos.end()){
        DatosProducto datos;
        datos.nombre = nombre;
        datos.cantidad = cantidad;
        productos[codigo] = datos;
        agregado = true;

    }
    return agregado;
}

bool MapInventario::eliminarProducto(int codigo){
    bool eliminado = false;

    map<int, DatosProducto>::iterator it = productos.find(codigo);
    if (it != productos.end()){
        productos.erase(it);
        eliminado = true;
    }
    return eliminado;
}

bool MapInventario::consultarProducto(int codigo, string& nombre, int& cantidad) const{
    bool existe = false;
    map<int, DatosProducto>::const_iterator it = productos.find(codigo);
    if(it != productos.end()){
        existe = true;
        nombre = it->second.nombre;
        cantidad = it->second.cantidad;
    }
    return existe;
}

bool MapInventario::reponerProducto(int codigo, int cantidad){
    bool aux = false;

    map<int, DatosProducto>::iterator it = productos.find(codigo);
    if(it!=productos.end()){
        it ->second.cantidad += cantidad;
        aux = true;
    }
    return aux;
}


void MapInventario::listarProductos()const{
    map<int, DatosProducto>::const_iterator it;
    for(it = productos.begin(); it != productos.end(); ++it){
        printf("%d %s %d\n", it->first, it->second.nombre.c_str(), it->second.cantidad);
    }
}