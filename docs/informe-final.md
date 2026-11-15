# Informe final

*(Parte del informe del avance, corregido con la realimentación.)*

## 1. El escenario y el modelado

<<<<<<< HEAD
El escenario seleccionado corresponde al inventario de una tienda, el programa permite almacenar y administrar productos mediante un código que identifica a cada uno.

Cada producto tiene tres datos: un código entero, un nombre y una cantidad disponible. El código se utiliza como clave para identificar los productos y evitar que se agreguen dos productos con el mismo código.

El sistema permite realizar las siguientes operaciones:

- **AGREGAR:** registra un producto nuevo con su código, nombre y cantidad.
- **ELIMINAR:** elimina un producto utilizando su código.
- **CONSULTAR:** busca un producto y muestra su nombre y cantidad.
- **REPONER:** aumenta la cantidad disponible de un producto.
- **LISTAR:** muestra todos los productos almacenados.

Para implementar el inventario se utiliza una lista enlazada simple y una tabla hash con encadenamiento, además, se utiliza `map` de C++ como estructura de referencia para comparar los tiempos de ejecución.

En las estructuras implementadas, cada producto se almacena con su código, nombre y cantidad, en la lista enlazada, los productos se conectan mediante punteros entre nodos, en la tabla hash, el código del producto determina la cubeta donde se almacena mediante la operación módulo.

Lo usaría la persona encargada del inventario, que necesita registrar productos nuevos, eliminar los que dejan de venderse, consultar cuántas unidades quedan de uno y reponer existencias cuando llega mercancía. También puede listar todo lo que hay en bodega. Casi todo lo que hace es buscar un producto por su código, así que la rapidez de esa búsqueda es lo que más importa.

El propósito es llevar el control del stock sin errores (sin duplicados) y comparar tres formas de organizar los datos: una lista enlazada, una tabla hash y un map de la librería estándar. Queremos ver cuál responde mejor cuando el inventario crece, de mil a veinte mil productos.


# Diagramas del informe

Diagramas mermaid de cada una de las 2 estructuras usadas.

Lista enlazada con nodos y punteros

Se insertó Arroz, luego Frijol y luego lechona. Como agregarProducto inserta al inicio, queda en orden inverso:

```mermaid
flowchart LR
    cabeza([cabeza]) --> N1["codigo: 52345<br/>nombre: lechona<br/>cantidad: 100<br/>sig"]
    N1 --> N2["codigo: 212351235<br/>nombre: Frijol<br/>cantidad: 5<br/>sig"]
    N2 --> N3["codigo: 112341234<br/>nombre: Arroz<br/>cantidad: 10<br/>sig"]
    N3 --> NULO([nullptr])
```


Tabla hash con varias cubetas (M = 5, hash = codigo % M)

```mermaid
flowchart LR
    B0["tabla[0]"] --> A10["codigo 10"] --> Z0([nullptr])
    B1["tabla[1]"] --> Z1([nullptr])
    B2["tabla[2]"] --> A7["codigo 7"] --> Z2([nullptr])
    B3["tabla[3]"] --> A3["codigo 3"] --> Z3([nullptr])
    B4["tabla[4]"] --> A9["codigo 9"] --> Z4([nullptr])
```

Colision: dos codigos en la misma cubeta
 
```mermaid
flowchart LR
    C1["codigo 7<br/>7 % 5 = 2"] --> B2["tabla[2]"]
    C2["codigo 12<br/>12 % 5 = 2"] --> B2
    B2 --> N12["codigo 12<br/>Arroz"] --> N7["codigo 7<br/>Frijol"] --> Z([nullptr])
```

## 2. Las dos estructuras

### Lista enlazada simple

Cada nodo almacena el código, nombre y cantidad de un producto, además de un puntero al siguiente nodo, la lista permite agregar, consultar, eliminar, reponer y listar productos mediante recorridos desde la cabeza.

### Tabla hash con encadenamiento

Utiliza un arreglo de cubetas, donde cada producto se almacena según el resultado de la función hash:

$$h(codigo) = codigo \bmod M$$

Si varios productos llegan a la misma cubeta, se almacenan en una lista enlazada.

### Interfaz de las estructuras

Ambas estructuras permiten realizar las mismas operaciones: agregar, eliminar, consultar, reponer y listar productos.

### Estructura de referencia: map de C++

Se utiliza `map` de C++ como referencia para comparar los tiempos de ejecución. Almacena los productos usando su código como clave y mantiene las claves ordenadas.

Las tres estructuras (Lista, TablaHash y MapInventario) exponen las mismas cinco operaciones, y todas identifican al producto por su código:

agregarProducto(codigo, nombre, cantidad) devuelve false si el código ya existe.
eliminarProducto(codigo) devuelve true si lo encontró y lo quitó.
consultarProducto(codigo, nombre, cantidad) devuelve por referencia el nombre y la cantidad, y responde si existe.
reponerProducto(codigo, cantidad) suma unidades a un producto existente.
listarProductos() imprime todo el inventario.

La interfaz es la misma porque las tres implementan un mismo contrato: el de un diccionario que asocia una clave (el código) con sus datos, con insertar, buscar y eliminar como operaciones básicas [1]. Lo que cambia es la representación interna: nodos enlazados, un arreglo de listas con una función hash, o un árbol balanceado dentro de std::map. Separar interfaz e implementación permite cambiar la segunda sin tocar el código que usa la estructura [2][3]. Lo comprobamos en la práctica: para pasar de Lista a TablaHash en principal.cpp solo cambiamos el tipo de la variable, y el mismo código de medición sirve para las tres.

## 3. Análisis formal de complejidad

Una demostración por operación no trivial, en cuatro partes:

**Teorema.** (Enunciado con la cota.)

**Demostración.** Se procede de forma directa. (La estrategia.)

*Desarrollo.* (La cadena de desigualdades, con la justificación de cada
paso.)

$$T(n) = \ldots \leq c \cdot n^2 \quad \text{para todo } n \geq k$$

*Conclusión.* Por lo tanto, $T(n) \in O(n^2)$ con testigos $c = \ldots$
y $k = \ldots$

Resumen de costos:

| Operación | Desde cero | De la biblioteca | Por qué |
|---|---|---|---|
|  |  |  |  |


### Demostraciones de complejidad

Para las demostraciones se usa $n$ como la cantidad de productos almacenados. En la tabla hash, $b$ representa la cantidad de productos que hay en la cubeta consultada, por lo que $0\leq b\leq n$.

#### Lista enlazada

**Teorema 1.** Consultar un producto en la lista enlazada tiene complejidad $O(n)$ en el peor caso.

**Demostración.** Se recorre la lista desde la cabeza hasta encontrar el código o llegar al final.

**Desarrollo.** En el peor caso se revisan los $n$ nodos. Si cada revisión cuesta como máximo una constante $a$ y el resto de operaciones cuesta $d$, entonces:

$$T(n)\leq an+d.$$

Para $n\geq 1$, se cumple $an+d\leq (a+d)n$. Tomando $c=a+d$ y $k=1$, se obtiene $T(n)\leq cn$.

**Conclusión.** $T(n)\in O(n)$, con testigos $c=a+d$ y $k=1$.

**Teorema 2.** Agregar un producto a la lista enlazada tiene complejidad $O(n)$ en el peor caso.

**Demostración.** Antes de insertar, el método busca si el código ya existe. Si no existe, crea el nodo y lo enlaza al inicio en tiempo constante.

**Desarrollo.** La búsqueda revisa como máximo $n$ nodos y la inserción realiza una cantidad constante de operaciones. Por tanto:

$$T(n)\leq an+d\leq (a+d)n,\qquad n\geq 1.$$

Tomando $c=a+d$ y $k=1$, se cumple la definición de $O(n)$.

**Conclusión.** $T(n)\in O(n)$, con testigos $c=a+d$ y $k=1$.

**Teorema 3.** Eliminar un producto de la lista enlazada tiene complejidad $O(n)$ en el peor caso.

**Demostración.** Se recorre la lista hasta encontrar el producto. Una vez encontrado, se ajustan los punteros y se libera el nodo, operaciones que toman tiempo constante.

**Desarrollo.** Como se pueden revisar los $n$ nodos, existe una constante $a$ para el recorrido y una constante $d$ para el ajuste de punteros y la eliminación:

$$T(n)\leq an+d\leq (a+d)n,\qquad n\geq 1.$$

Con $c=a+d$ y $k=1$, se obtiene la cota requerida.

**Conclusión.** $T(n)\in O(n)$, con testigos $c=a+d$ y $k=1$.

**Teorema 4.** Reponer un producto en la lista enlazada tiene complejidad $O(n)$ en el peor caso.

**Demostración.** El método busca el producto por su código y, si lo encuentra, actualiza su cantidad en tiempo constante.

**Desarrollo.** La búsqueda revisa como máximo $n$ nodos y la actualización cuesta una constante:

$$T(n)\leq an+d\leq (a+d)n,\qquad n\geq 1.$$

Tomando $c=a+d$ y $k=1$, se cumple la definición.

**Conclusión.** $T(n)\in O(n)$, con testigos $c=a+d$ y $k=1$.

**Teorema 5.** Listar los productos de la lista enlazada tiene complejidad $O(n)$.

**Demostración.** El método visita cada nodo una sola vez e imprime sus datos.

**Desarrollo.** Si visitar e imprimir cada nodo cuesta como máximo $a$ y existe un costo fijo $d$, entonces:

$$T(n)\leq an+d\leq (a+d)n,\qquad n\geq 1.$$

Con $c=a+d$ y $k=1$, la cota queda demostrada.

**Conclusión.** $T(n)\in O(n)$, con testigos $c=a+d$ y $k=1$.

#### Tabla hash con encadenamiento

**Teorema 6.** Consultar, agregar, eliminar o reponer un producto en la tabla hash tiene complejidad $O(b)$ para una cubeta con $b$ productos y, en el peor caso, $O(n)$.

**Demostración.** La función hash calcula la cubeta en tiempo constante. Después, la operación correspondiente se realiza sobre la lista enlazada de esa cubeta.

**Desarrollo.** El recorrido de la lista de la cubeta revisa como máximo $b$ nodos. Las operaciones adicionales de insertar, actualizar o desconectar un nodo cuestan tiempo constante. Por tanto, para constantes $a$ y $d$:

$$T(b)\leq ab+d\leq (a+d)b,\qquad b\geq 1.$$

Como $b\leq n$, también se cumple $T(n)\leq an+d\leq (a+d)n$ para $n\geq 1$. Así, se pueden tomar $c=a+d$ y $k=1$ para la cota $O(n)$ del peor caso.

**Conclusión.** Cada una de estas operaciones cuesta $O(b)$ en la cubeta correspondiente y $O(n)$ en el peor caso, con testigos $c=a+d$ y $k=1$ para la cota peor caso.

**Teorema 7.** Listar todos los productos de la tabla hash tiene complejidad $O(M+n)$, donde $M$ es la cantidad de cubetas.

**Demostración.** El método recorre las $M$ cubetas y lista los nodos de cada lista. Cada producto pertenece a una sola cubeta y se visita una vez.

**Desarrollo.** Recorrer las cubetas cuesta como máximo $aM$ y visitar todos los nodos cuesta como máximo $bn$. Para constantes $a$ y $b$:

$$T(M,n)\leq aM+bn\leq (a+b)(M+n).$$

Tomando $c=a+b$ y $k=1$, se obtiene la cota $O(M+n)$.

**Conclusión.** $T(M,n)\in O(M+n)$, con testigos $c=a+b$ y $k=1$.

#### Referencia de la biblioteca

La estructura `map` de C++ mantiene sus claves ordenadas. Sus operaciones de búsqueda, inserción y eliminación tienen complejidad $O(\log n)$; listar todos los elementos cuesta $O(n)$ porque se recorren sus elementos una vez.

### Resumen de costos

| Operación | Lista enlazada | Tabla hash | `map` de C++ |
|---|---:|---:|---:|
| Agregar | $O(n)$ | $O(n)$ peor caso | $O(\log n)$ |
| Consultar | $O(n)$ | $O(n)$ peor caso | $O(\log n)$ |
| Reponer | $O(n)$ | $O(n)$ peor caso | $O(\log n)$ |
| Eliminar | $O(n)$ | $O(n)$ peor caso | $O(\log n)$ |
| Listar | $O(n)$ | $O(M+n)$ | $O(n)$ |

En la tabla hash, las operaciones individuales pueden ser $O(1)$ en promedio cuando los productos se distribuyen entre las cubetas; sin embargo, si todos los productos caen en una misma cubeta, el costo llega a $O(n)$.

## 4. Experimentos

Las mediciones se hicieron en Intel(R) Core(TM) 5 210H ,16 GB RAM en windows, compilando con `g++`  y las banderas `-Wall -Wextra -O2`. Las entradas son deterministas: el producto i (de 0 a n − 1) usa el código 7·i + 3, así todos son distintos y las tres estructuras reciben los mismos datos. En cada experimento se insertan los n productos, se consultan los n y se eliminan los n en el mismo orden, y se reporta la suma de los tres tiempos. Para la tabla hash y `std::map` se repitió ese ciclo 500 veces y se reporta el promedio (20 repeticiones para la tabla de 101 cubetas, que es más lenta). La `Lista` y el peor caso de la tabla hash se midieron en una sola corrida, porque ya tardan lo suficiente. El tiempo se midió con `std::chrono::steady_clock`.

| n | desde cero (ms) | biblioteca (ms) | Lista (ms) |
|---|---|---|---|
| 1000* | ≈ 0,12 | ≈ 0,22 | no confiable |
| 5000 | 0,551 | 1,159 | 101,3 |
| 10000 | 1,034 | 2,392 | 365,6 |
| 50000 | 4,826 | 11,839 | 10743 |
| 100000 | 9,872 | 24,710 | 41689 |

\* Con n = 1.000 cada medición dura menos que la resolución del reloj del sistema (~1 ms), y algunas fases dieron tiempos nulos o negativos. Por eso este tamaño solo se reporta de forma aproximada (mediana de cuatro corridas) y no se usa en el análisis. La `Lista` no se reporta en esta fila.

Otro dato aparte en los casos de Tabla Hash peor caso, para n = 50000 y n = 100000 no se toman datos ya que la tabla hash se desborda ya que los multiplos de M que se necesitan para entrar en un solo bucket se desbordan

```mermaid
xychart-beta
    title "Tiempo contra tamaño de la entrada"
    x-axis "n (productos)" [1000, 5000, 10000, 50000, 100000]
    y-axis "milisegundos" 0 --> 30
    line [0.12, 0.551, 1.034, 4.826, 9.872]
    line [0.22, 1.159, 2.392, 11.839, 24.710]
```

## 5. Lo medido contra lo predicho

Comparamos cuánto creció cada tiempo al pasar de n = 5.000 a n = 100.000 (veinte veces más datos) con lo que predice la cota de cada estructura.

| Estructura | Cota predicha (n operaciones) | Crecimiento esperado | Crecimiento medido |
|---|---|---|---|
| Lista | Θ(n²) | ×400 | ×412 |
| Tabla hash (M = n) | Θ(n) | ×20 | ×18 |
| `std::map` | Θ(n log n) | ×27 | ×21 |

**Lista.** Coincide con la cota cuadrática: cada operación recorre la lista (O(n)) y hacemos n operaciones. Al duplicar n el tiempo se multiplica por ~4 (de 50.000 a 100.000 midió ×3,9). Entre 10.000 y 50.000 creció algo más de lo esperado (×29 en vez de ×25). Lo más probable es la memoria caché: cada nodo se reserva con `new` por separado, y con pocos nodos todo cabe en caché, pero con decenas de miles hay que ir a memoria principal en cada paso. No lo verificamos con un contador de caché.

**Tabla hash (M = n).** El crecimiento es casi proporcional a n (×18 contra ×20 esperado), es decir, O(1) por operación. El diagnóstico coincide con la teoría: factor de carga 1 y bucket más largo de 1. Pero el resultado es mejor que el promedio teórico de la hash, porque nuestras claves (7·i + 3) son una progresión aritmética que se reparte perfectamente entre las cubetas. Con claves reales o aleatorias esperaríamos algunas colisiones y cadenas más largas. Cuando forzamos todas las claves a una sola cubeta (peor caso), el tiempo creció ×4,4 al duplicar n (de 5.000 a 10.000), igual que la lista: O(n) por operación.

**`std::map`.** Creció menos que n log n (×21 contra ×27). Insertamos y buscamos las claves en orden creciente, así que cada operación recorre casi el mismo camino del árbol, lo que favorece la caché. Con claves en orden aleatorio esperaríamos tiempos mayores. Además, la constante oculta de `map` es mayor que la de la hash: con n = 100.000 fue unas 2,5 veces más lento, por reservar un nodo por producto y mantener el árbol balanceado.

**Limitaciones.** No usamos `vector`, así que no hay crecimiento de arreglo que explicar: el costo de memoria viene de reservar un nodo por producto. Entre corridas del mismo programa los tiempos variaron entre un 15 % y un 35 % (en la `Lista` con n = 100.000, por ejemplo), así que las diferencias pequeñas entre lo medido y lo predicho no son significativas. Con n = 1.000 los tiempos son menores que la resolución del reloj y no se usaron.

## 6. Conclusiones

Para el escenario de inventario de una tienda, consideramos que la tabla hash con encadenamiento es una buena opción, ya que permite buscar los productos a partir de su código sin tener que recorrer toda la lista en condiciones normales, sin embargo, su rendimiento depende de la distribución de los códigos y de la cantidad de colisiones que se presenten.

La lista enlazada es sencilla de implementar, pero sus operaciones de búsqueda, eliminación y reposición pueden requerir recorrer todos los productos, por otro lado, map permite buscar los productos de forma eficiente y mantiene las claves ordenadas, aunque utiliza una estructura proporcionada por la biblioteca de C++.

En conclusión, para este inventario elegiríamos la tabla hash porque las consultas se realizan mediante el código del producto, si fuera necesario mantener los productos ordenados por código, map sería una alternativa conveniente, La lista enlazada puede ser útil cuando se busca una implementación más sencilla y no se requiere hacer búsquedas frecuentes.
