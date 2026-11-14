#include <cstdio>
#include <climits> //Se usa para evitar el desborde
#include <chrono>
#include <string>
#include "lista.h"
#include "Tablahash.h"
#include "MapInventario.h"

using namespace std::chrono;

// Tiempo actual en milisegundos
double ahoraMs() {
    return duration<double, milli>(steady_clock::now().time_since_epoch()).count();
}

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

// Codigo del producto i. Con paso = 7 los codigos se reparten bien;
// con paso = M todos caen en el mismo bucket (peor caso de la hash).
int codigoDe(int i, int paso) {
    return (int)((long long)i * paso + 3);
}

// Evita el desborde de int
bool cabeEnInt(int n, int paso) {
    return (long long)(n - 1) * paso + 3 <= INT_MAX;
}

template <typename Estructura>
double llenar(Estructura& e, int n, int paso) {
    double t0 = ahoraMs();

    for (int i = 0; i < n; i++) {
        e.agregarProducto(codigoDe(i, paso), "producto", 1);
    }

    return ahoraMs() - t0;
}

template <typename Estructura>
double consultarTodos(const Estructura& e, int n, int paso, int& encontrados) {
    std::string nombre;
    int cantidad;
    encontrados = 0;

    double t0 = ahoraMs();

    for (int i = 0; i < n; i++) {
        if (e.consultarProducto(codigoDe(i, paso), nombre, cantidad)) {
            encontrados++;
        }
    }

    return ahoraMs() - t0;
}

template <typename Estructura>
double eliminarTodos(Estructura& e, int n, int paso) {
    double t0 = ahoraMs();

    for (int i = 0; i < n; i++) {
        e.eliminarProducto(codigoDe(i, paso));
    }

    return ahoraMs() - t0;
}

// Repite llenar -> consultar -> eliminar y devuelve el promedio de cada fase.
// Devuelve false si alguna vez la estructura no encontro los n elementos.
template <typename Estructura>
bool medirCiclo(Estructura& e, int n, int paso, int repeticiones,
                double& a, double& c, double& el) {
    bool ok = true;
    int encontrados = 0;
    a = 0;
    c = 0;
    el = 0;

    for (int r = 0; r < repeticiones; r++) {
        a += llenar(e, n, paso);
        c += consultarTodos(e, n, paso, encontrados);
        if (encontrados != n) {
            ok = false;
        }
        el += eliminarTodos(e, n, paso);
    }

    a /= repeticiones;
    c /= repeticiones;
    el /= repeticiones;

    return ok;
}

// Llena la tabla una vez y muestra como quedaron los buckets
void diagnostico(const char* nombre, TablaHash& tabla, int n, int M, int paso) {
    llenar(tabla, n, paso);
    printf("# %s n=%d M=%d lambda=%.2f max=%d vacios=%d\n",
           nombre, n, M, tabla.factorCarga(), tabla.longitudMaxima(), tabla.bucketsVacios());
    eliminarTodos(tabla, n, paso);
}

int main() {
    int tamanos[] = {1000, 2000, 5000, 10000, 20000};
    int cantidadTamanos = 5;
    int paso = 7;
    int repeticiones = 500;     // Hash y Map son muy rapidos: se promedia
    bool todoOk = true;

    printf("estructura,n,M,agregar_ms,consultar_ms,eliminar_ms\n");
    printf("--------------------------------------------------\n");

    for (int k = 0; k < cantidadTamanos; k++) {
        int n = tamanos[k];
        double a, c, e;
        bool ok;

        // ---- Lista (una sola corrida: ya tarda lo suficiente) ----
        {
            Lista lista;
            ok = medirCiclo(lista, n, paso, 1, a, c, e);
            printf("Lista,%d,-,%.6f,%.6f,%.6f\n", n, a, c, e);
            printf("--------------------------------------------------\n");
            if (!ok) { printf("# ERROR Lista: no encontro todos los elementos\n"); todoOk = false; }
        }

        // ---- TablaHash con tres tamanos de tabla ----
        int Ms[3] = {101, n, siguientePrimo(2 * n)};
        const char* nombres[3] = {"Hash_pequena", "Hash_cercana_n", "Hash_primo_mayor"};
        int reps[3] = {20, repeticiones, repeticiones};   // la pequena es lenta

        for (int j = 0; j < 3; j++) {
            int M = Ms[j];
            TablaHash tabla(M);

            diagnostico(nombres[j], tabla, n, M, paso);
            ok = medirCiclo(tabla, n, paso, reps[j], a, c, e);
            printf("%s,%d,%d,%.6f,%.6f,%.6f\n", nombres[j], n, M, a, c, e);
            printf("--------------------------------------------------\n");
            if (!ok) { printf("# ERROR %s: no encontro todos los elementos\n", nombres[j]); todoOk = false; }
        }

        // ---- Map ----
        {
            MapInventario mapa;
            ok = medirCiclo(mapa, n, paso, repeticiones, a, c, e);
            printf("Map,%d,-,%.6f,%.6f,%.6f\n", n, a, c, e);
            if (!ok) { printf("# ERROR Map: no encontro todos los elementos\n"); todoOk = false; }
            printf("--------------------------------------------------\n");
        }

        // ---- Peor caso de la hash: todos los codigos en el mismo bucket ----
        {
            int M = n;
            if (!cabeEnInt(n, M)) {
                printf("# Hash_peor_caso n=%d omitido: los codigos desbordarian int\n", n);
            } else {
                TablaHash tabla(M);

                diagnostico("Hash_peor_caso", tabla, n, M, M);
                ok = medirCiclo(tabla, n, M, 1, a, c, e);
                printf("Hash_peor_caso,%d,%d,%.6f,%.6f,%.6f\n", n, M, a, c, e);
                printf("--------------------------------------------------\n");
                if (!ok) { printf("# ERROR Hash_peor_caso: no encontro todos los elementos\n"); todoOk = false; }
            }
        }
    }

    if (todoOk) {
        printf("# Verificacion OK: todas las estructuras encontraron todos los elementos\n");
    } else {
        printf("# Verificacion FALLO: revisar los ERROR de arriba\n");
    }

    return todoOk ? 0 : 1;
}