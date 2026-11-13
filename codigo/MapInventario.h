#ifndef MAPINVENTARIO_H
#define MAPINVENTARIO_H

#include <map>
#include <string>
using namespace std;

struct DatosProducto {
    string nombre;
    int cantidad;
};

class MapInventario {
private:
    map<int, DatosProducto> productos;   // clave: codigo

public:
    bool agregarProducto(int codigo, const string& nombre, int cantidad);
    bool eliminarProducto(int codigo);
    bool consultarProducto(int codigo, string& nombre, int& cantidad) const;
    bool reponerProducto(int codigo, int cantidad);
    void listarProductos() const;
};

#endif