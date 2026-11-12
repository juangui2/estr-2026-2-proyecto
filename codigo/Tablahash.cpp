// Autores: Juan Guillermo Espinosa 9038654, Miguel Angel Lenis 9040913, Juan Jose Arenas 9035047
 
#include "TablaHash.h"
 
TablaHash::TablaHash(int m) : M(m) {
    tabla = new Lista[M];
}
 
TablaHash::~TablaHash() {
    delete[] tabla;
}
 
int TablaHash::hash(int codigo) const {
    return ((codigo % M) + M) % M;
}
 
bool TablaHash::agregarProducto(int codigo, const string& nombre, int cantidad) {
    return tabla[hash(codigo)].agregarProducto(codigo, nombre, cantidad);
}
 
bool TablaHash::eliminarProducto(int codigo) {
    return tabla[hash(codigo)].eliminarProducto(codigo);
}
 
bool TablaHash::consultarProducto(int codigo, string& nombre, int& cantidad) const {
    return tabla[hash(codigo)].consultarProducto(codigo, nombre, cantidad);
}
 
bool TablaHash::reponerProducto(int codigo, int cantidad) {
    return tabla[hash(codigo)].reponerProducto(codigo, cantidad);
}
 
void TablaHash::listarProductos() const {
    for (int i = 0; i < M; i++) {
        tabla[i].listarProductos();
    }
}
 