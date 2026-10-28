// Autores: Nombre1 Codigo1, Nombre2 Codigo2, Nombre3 Codigo3
// Punto de entrada del proyecto. Reemplacen este archivo por el suyo.
#include <cstdio>
#include <string>

struct Nodo {
    int codigo;
    std::string nombre;
    int cantidad;
    Nodo* sig = nullptr;
};

void agregarProducto(Nodo*& cabeza, int codigo, const std::string& nombre, int cantidad){
  Nodo* nuevo = new Nodo;
  nuevo -> codigo = codigo;
  nuevo -> nombre = nombre;
  nuevo -> cantidad = cantidad;
  nuevo->sig = cabeza;   
  cabeza = nuevo; 

}

Nodo* buscarProducto(Nodo*& cabeza, int codigo){
    Nodo* actual = cabeza;
    while(actual != nullptr){
      if(actual ->codigo == codigo){
        return actual;
      }
      actual = actual ->sig;
    }
    return nullptr;
}

int main() {
  Nodo* cabeza = nullptr;
  agregarProducto(cabeza, 112341234, "Arroz", 10);
  agregarProducto(cabeza, 212351235, "Frijol", 5);
  agregarProducto(cabeza, 52345, "lechona", 100);
  printf("%d %s\n", cabeza->codigo, cabeza->nombre.c_str());

  Nodo* encontrado = buscarProducto(cabeza, 0);
  if(encontrado != nullptr){
    printf("Encontrado: %s, cantidad %d\n", encontrado->nombre.c_str(), encontrado->cantidad);
  } else {
  printf("No existe\n");
  return 0;
}
}
