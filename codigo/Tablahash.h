// Autores: Juan Guillermo Espinosa 9038654, Miguel Angel Lenis 9040913, Juan Jose Arenas 9035047
 
#ifndef TABLAHASH_H
#define TABLAHASH_H
 
#include <string>
#include "lista.h"
using namespace std;
 
class TablaHash {
private:
    Lista* tabla;  
    int M;
 
    int hash(int codigo) const;
 
public:
    TablaHash(int m = 101);   // M primo
    ~TablaHash();
 
    TablaHash(const TablaHash&) = delete;
    TablaHash& operator=(const TablaHash&) = delete;
 
    bool agregarProducto(int codigo, const string& nombre, int cantidad);
    bool eliminarProducto(int codigo);
    bool consultarProducto(int codigo, string& nombre, int& cantidad) const;
    bool reponerProducto(int codigo, int cantidad);
    void listarProductos() const;
};
 
#endif