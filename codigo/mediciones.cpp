//Este code se usa para medir tiempos y entregar un informa mucho mas completo a nivel de datos

#include <cstdio>
#include <chrono>
#include <string>
#include "lista.h"
#include "TablaHash.h"
#include "MapInventario.h"

using namespace std::chrono;

double ahoraMs() {
    return duration<double, milli>(steady_clock::now().time_since_epoch()).count();
}

//Funciones para saber si es primo o para buscar el siguiente

bool esPrimo(int n) {
    bool primo = n >= 2;

    for (int d = 2; d * d <= n && primo; d++) {
        if (n % d == 0) {
            primo = false;
        }
    }

    return primo;
}

int siguientePrimo(int n) {
    while (!esPrimo(n)) {
        n++;
    }
    return n;
}

int codigoDe(int i) {
    return i * 7 + 3;
}

template <typename Estructura> // Esta es una funcion para que sirva el agregarProducto de cada una 
                               // de la estructuras, ya que al tener mismo nombre puede generar problemas
double llenar(Estructura& e, int n) {
    double t0 = ahoraMs();

    for (int i = 0; i < n; i++) {
        e.agregarProducto(codigoDe(i), "producto", 1);
    }

    return ahoraMs() - t0;
}

template <typename Estructura>
double consultarTodos(const Estructura& e, int n, int& encontrados) {
    std::string nombre;
    int cantidad;
    encontrados = 0;

    double t0 = ahoraMs();

    for (int i = 0; i < n; i++) {
        if (e.consultarProducto(codigoDe(i), nombre, cantidad)) {
            encontrados++;
        }
    }

    return ahoraMs() - t0;
}

template <typename Estructura>
double eliminarTodos(Estructura& e, int n) {
    double t0 = ahoraMs();

    for (int i = 0; i < n; i++) {
        e.eliminarProducto(codigoDe(i));
    }

    return ahoraMs() - t0;
}


// Peor caso de la hash: todos los codigos son multiplos de M,
// asi que todos caen en el mismo bucket
void peorCasoHash(int n) {
    int M = siguientePrimo(n / 2);
    TablaHash tabla(M);
    std::string nombre;
    int cantidad;
    int encontrados = 0;

    double t0 = ahoraMs();
    for (int i = 0; i < n; i++) {
        tabla.agregarProducto(i * M, "producto", 1);
    }
    double a = ahoraMs() - t0;

    printf("# HashPeor n=%d M=%d lambda=%.2f max=%d vacios=%d\n",
           n, M, tabla.factorCarga(), tabla.longitudMaxima(), tabla.bucketsVacios());

    t0 = ahoraMs();
    for (int i = 0; i < n; i++) {
        if (tabla.consultarProducto(i * M, nombre, cantidad)) {
            encontrados++;
        }
    }
    double c = ahoraMs() - t0;

    t0 = ahoraMs();
    for (int i = 0; i < n; i++) {
        tabla.eliminarProducto(i * M);
    }
    double e = ahoraMs() - t0;

    printf("HashPeor,%d,%.3f,%.3f,%.3f\n", n, a, c, e);
    if (encontrados != n) printf("# ERROR HashPeor: encontrados=%d\n", encontrados);
}

int main() {
    int tamanos[] = {1000, 5000, 10000, 50000, 100000};
    int cantidadTamanos = 5;

    printf("estructura,n,agregar_ms,consultar_ms,eliminar_ms\n");
    printf("------------------------------------------------------\n");

    for (int k = 0; k < cantidadTamanos; k++) {
        int n = tamanos[k];
        int encontrados;

        // ---- Lista ----
        {
            Lista lista;
            double a = llenar(lista, n);
            double c = consultarTodos(lista, n, encontrados);
            double e = eliminarTodos(lista, n);
            printf("Lista,%d,%.3f,%.3f,%.3f\n", n, a, c, e);
            if (encontrados != n) printf("# ERROR Lista: encontrados=%d\n", encontrados);
        }

        // ---- TablaHash ----
        {
            int M = siguientePrimo(n / 2);
            TablaHash tabla(M);
            double a = llenar(tabla, n);

            // diagnostico con la tabla llena
            printf("# Hash n=%d M=%d lambda=%.2f max=%d vacios=%d\n",
                   n, M, tabla.factorCarga(), tabla.longitudMaxima(), tabla.bucketsVacios());

            double c = consultarTodos(tabla, n, encontrados);
            double e = eliminarTodos(tabla, n);
            printf("Hash,%d,%.3f,%.3f,%.3f\n", n, a, c, e);
            if (encontrados != n) printf("# ERROR Hash: encontrados=%d\n", encontrados);
        }

        // ---- Map ----
        {
            MapInventario mapa;
            double a = llenar(mapa, n);
            double c = consultarTodos(mapa, n, encontrados);
            double e = eliminarTodos(mapa, n);
            printf("Map,%d,%.3f,%.3f,%.3f\n", n, a, c, e);
            if (encontrados != n) printf("# ERROR Map: encontrados=%d\n", encontrados);
        }
        
        {

         // ---- Hash en el peor caso ----
        peorCasoHash(n);
        printf("------------------------------------------------------\n");
        }
    }

    return 0;
}