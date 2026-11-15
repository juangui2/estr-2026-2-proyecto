# Informe final

*(Parte del informe del avance, corregido con la realimentación.)*

## 1. El escenario y el modelado

(Del avance, corregido.)

# Diagramas del informe

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

(Qué operaciones expone cada una y por qué la interfaz es la misma.)

Diagramas mermaid de cada una de las 2 estructuras usadas.


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

## 4. Experimentos

Máquina, compilador y banderas con que se midió; cómo se generaron las
entradas; cuántas repeticiones por tamaño.

| $n$ | desde cero (ms) | biblioteca (ms) |
|---|---|---|
| 1000 |  |  |
| 5000 |  |  |
| 10000 |  |  |
| 50000 |  |  |
| 100000 |  |  |

```mermaid
xychart-beta
  title "Tiempo contra tamaño de la entrada"
  x-axis [1000, 5000, 10000, 50000, 100000]
  y-axis "milisegundos" 0 --> 100
  line [1, 5, 12, 60, 130]
  line [1, 4, 9, 45, 95]
```

## 5. Lo medido contra lo predicho

(¿Coincide la curva con la cota? Donde no coincida, expliquen por qué:
la constante oculta, la memoria caché, el crecimiento del vector.)

## 6. Conclusiones

(Cuál estructura conviene para este escenario y bajo qué condiciones
cambiaría la respuesta.)
