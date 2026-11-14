
// Autores: Juan Guillermo Espinosa 9038654, Miguel Angel Lenis 9040913, Juan Jose Arenas 9035047
// Programa principal del inventario.

#include <cstdio>
#include <string>
#include "Tablahash.h"

using namespace std;

void convertirMayusculas(char texto[]){
    int i = 0;

    while (texto[i] != '\0'){
        if (texto[i] >= 'a' && texto[i] <= 'z'){
            texto[i] = texto[i] - 32;
        }

        i++;
    }
}

int main(){

    TablaHash inventario;
    char comando[20];
    int n;

    scanf("%d", &n);

    for (int i = 0; i < n; i++){

        scanf("%19s", comando);
        convertirMayusculas(comando);

        if (string(comando) == "SALIR"){
            i = n;
        }
        else if (string(comando) == "AGREGAR"){

            int codigo;
            int cantidad;
            char nombre[100];

            scanf("%d %99s %d", &codigo, nombre, &cantidad);

            if (inventario.agregarProducto(codigo, nombre, cantidad)){
                printf("ok\n");
            }
            else{
                printf("repetido\n");
            }

        }
        else if (string(comando) == "ELIMINAR"){

            int codigo;
            scanf("%d", &codigo);

            if (inventario.eliminarProducto(codigo)){
                printf("ok\n");
            }
            else{
                printf("no existe\n");
            }

        }
        else if (string(comando) == "CONSULTAR"){

            int codigo;
            string nombre;
            int cantidad;

            scanf("%d", &codigo);

            if (inventario.consultarProducto(codigo, nombre, cantidad)){
                printf("%d %s %d\n", codigo, nombre.c_str(), cantidad);
            }
            else{
                printf("no existe\n");
            }

        }
        else if (string(comando) == "REPONER"){

            int codigo;
            int cantidad;

            scanf("%d %d", &codigo, &cantidad);

            if (inventario.reponerProducto(codigo, cantidad)){
                printf("ok\n");
            }
            else{
                printf("no existe\n");
            }

        }
        else if (string(comando) == "LISTAR"){
            inventario.listarProductos();
        }
    }

    return 0;
}
