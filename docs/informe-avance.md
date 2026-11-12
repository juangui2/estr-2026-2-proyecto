# Informe de avance: Inventario de una tienda

## 1. Escenario

Vamos a manejar el inventario de una tienda. Cada artículo tiene un código numérico, un nombre de una palabra y una cantidad. El programa puede agregar un artículo (si el código no existe), eliminarlo, consultarlo, reponer unidades y listar todo el inventario. Si el código no está, responde que no existe.

En este avance usamos una lista enlazada simple con búsqueda por código. En la entrega final la cambiaremos por una tabla hash con encadenamiento, donde cada cubeta será esta lista.

## 2. Qué guarda la estructura y qué operaciones necesita

Cada nodo guarda el código, el nombre, la cantidad y un puntero al siguiente nodo. La lista solo guarda el puntero `cabeza` al primer nodo.

Operaciones: buscar por código, agregar, eliminar, consultar, reponer, listar y liberar la lista.

## 3. Por qué una lista enlazada y qué costo esperamos

Escogimos la lista enlazada porque la cantidad de artículos cambia y no hay que fijar un tamaño de antemano. Además, todas las operaciones buscan por código y nunca por posición, así que no necesitamos el acceso directo del arreglo. Insertamos al frente porque solo cuesta escribir dos punteros, y esta misma lista servirá como cubeta de la tabla hash final.

El costo de cada operación, con n artículos:

- **Consultar y reponer** cuestan O(n), porque hay que recorrer la lista hasta encontrar el código.
- **Agregar** cuesta O(n), porque primero se busca que el código no esté repetido; insertar al frente en sí es Θ(1).
- **Eliminar** cuesta O(n), porque hay que llegar al nodo anterior; desenlazar y liberar es Θ(1).
- **Listar** cuesta Θ(n), porque es un solo recorrido.
- **Liberar la lista** cuesta Θ(n), porque se libera un nodo a la vez.

Fuente: clase 15.

## 4. Qué pensamos medir al final

Mediremos el tiempo de `CONSULTAR` contra el número de artículos. Lo haremos con la tabla hash en tres tamaños (uno pequeño, uno cercano al número de artículos y uno primo mayor) y con un cuarto juego de códigos que caen todos en la misma cubeta. Lo compararemos con la lista del avance y con `map`.

También explicaremos el orden de `LISTAR`. En la lista sale en orden inverso al de inserción. En la tabla hash sale por cubeta, y dentro de cada cubeta en el orden de su lista. Para tener el mismo orden en las dos estructuras hay que listar con un criterio común, por ejemplo ordenando por código.
