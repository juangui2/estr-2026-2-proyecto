// Autores: Juan Guillermo Espinosa 9038654, Miguel Angel Lenis 9040913, Juan Jose Arenas 9035047
// Punto de entrada del proyecto. Reemplacen este archivo por el suyo.
#include <cstdio>
#include <string>
#include "lista.h"


int main() {
    Lista inventario;

    inventario.agregarProducto(112341234, "Arroz", 10);
    inventario.agregarProducto(212351235, "Frijol", 5);
    inventario.agregarProducto(52345, "lechona", 100);

    // Duplicado: debe devolver false
    if (!inventario.agregarProducto(52345, "otra lechona", 1)) {
        printf("No se agrego: el codigo 52345 ya existe\n");
    }

    printf("--- Inventario inicial ---\n");
    inventario.listarProductos();

    // Consultar (producto que existe)
    std::string nombre;
    int cantidad;
    if (inventario.consultarProducto(212351235, nombre, cantidad)) {
        printf("Encontrado: %s, cantidad %d\n", nombre.c_str(), cantidad);
    } else {
        printf("No existe\n");
    }

    // Consultar (producto que no existe)
    if (inventario.consultarProducto(0, nombre, cantidad)) {
        printf("Encontrado: %s, cantidad %d\n", nombre.c_str(), cantidad);
    } else {
        printf("El codigo 0 no existe\n");
    }

    // Reponer
    inventario.reponerProducto(112341234, 20);

    // Eliminar
    inventario.eliminarProducto(52345);

    printf("--- Inventario final ---\n");
    inventario.listarProductos();

  
    return 0;   // el destructor de Lista libera los nodos

}
