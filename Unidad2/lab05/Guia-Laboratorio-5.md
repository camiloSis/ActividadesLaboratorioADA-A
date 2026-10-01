# UNIVERSIDAD NACIONAL DE SAN AGUSTÍN
## FACULTAD DE INGENIERÍA DE PRODUCCIÓN Y SERVICIOS
### ESCUELA PROFESIONAL DE INGENIERÍA DE SISTEMAS

**Formato:** Guía de Práctica de Laboratorio / Talleres / Centros de Simulación  
**Aprobación:** 2022/03/01  
**Código:** GUIA-PRLD-001  

---

# GUÍA DE LABORATORIO N° 5

## INFORMACIÓN BÁSICA

| Campo | Detalle |
|-------|---------|
| **ASIGNATURA** | ANÁLISIS Y DISEÑO DE ALGORITMOS |
| **TÍTULO DE LA PRÁCTICA** | Árbol de Expansión Mínimo: Kruskal, Prim y Boruvka |
| **NÚMERO DE PRÁCTICA** | 5 |
| **AÑO LECTIVO** | 2026-B |
| **NRO. SEMESTRE** | IV (cuarto) |
| **TIPO DE PRÁCTICA** | ☐ INDIVIDUAL ☑ GRUPAL |
| **MÁXIMO DE ESTUDIANTES** | |
| **FECHA INICIO** | 01/10/2026 |
| **FECHA FIN** | 05/10/2026 |
| **DURACIÓN** | 2 horas |

**RECURSOS A UTILIZAR:**
- Un computador
- Material del curso
- Bibliografía del curso

**DOCENTE(S):**  
Roxana Evelyn Limache Calatayud

---

## OBJETIVOS, TEMAS Y COMPETENCIAS

### OBJETIVOS
- Comprender el concepto de árbol de expansión mínimo y sus aplicaciones.
- Implementar el algoritmo de Kruskal usando la estructura Union-Find.
- Implementar el algoritmo de Prim usando una cola de prioridad.
- Analizar y comparar la complejidad de Kruskal, Prim y Boruvka.

### TEMAS
- Árbol de expansión mínimo
- Algoritmo de Kruskal
- Algoritmo de Prim (Jarník)
- Algoritmo de Boruvka

### COMPETENCIAS
- **C.a** Capacidad de análisis de problemas computacionales
- **C.b** Diseño de soluciones algorítmicas eficientes
- **C.c** Validación y verificación de algoritmos
- **C.d** Comunicación técnica y redacción formal

---

## CONTENIDO DE LA GUÍA

---

### I. MARCO CONCEPTUAL

#### 1. El árbol de expansión mínimo

Dado un grafo conexo, no dirigido y ponderado, un **árbol de expansión** (spanning tree) es un subgrafo que conecta todos los vértices usando exactamente V-1 aristas, sin formar ciclos. El **árbol de expansión mínimo** (Minimum Spanning Tree, MST) es, entre todos los árboles de expansión posibles, el que tiene la suma de pesos de sus aristas más baja.

Este problema aparece cada vez que se necesita conectar un conjunto de puntos al menor costo posible: diseñar el cableado eléctrico o de red de un edificio, tender tuberías de agua entre localidades, o construir carreteras que conecten ciudades minimizando el costo total de construcción. A diferencia del camino más corto (Laboratorio 4), que busca la mejor ruta **ENTRE DOS** vértices, el MST busca conectar **TODOS** los vértices al menor costo total.

La **Figura 1** muestra el grafo de ejemplo que usaremos en todo el laboratorio (el mismo de 6 vértices usado en el Laboratorio 4), junto con su árbol de expansión mínimo. Tanto Kruskal como Prim, explicados a continuación, llegan exactamente a este mismo árbol y al mismo peso total, aunque lo construyen de forma distinta.

> **Figura 1.** Grafo ponderado y árbol de expansión mínimo (Kruskal / Prim).

#### 2. Algoritmo de Kruskal

Propuesto por Joseph Kruskal en 1956, es un algoritmo goloso (greedy) que construye el MST eligiendo en cada paso la arista más barata disponible, siempre que no forme un ciclo. En palabras simples: es como comprar los cables más baratos del mercado, uno por uno, pero rechazando cualquier cable que conectaría dos puntos que ya están conectados entre sí (porque cerraría un circuito y sería dinero desperdiciado).

**Proceso:**
1. Ordenar todas las aristas del grafo de menor a mayor peso.
2. Recorrer la lista ordenada y, para cada arista, agregarla al árbol solo si sus dos extremos pertenecen a componentes distintas (si agregarla no forma un ciclo).
3. Usar una estructura **Union-Find** (conjuntos disjuntos) para verificar y actualizar eficientemente a qué componente pertenece cada vértice.
4. Repetir hasta agregar V-1 aristas.

**Complejidad:** O(E log E), dominada por el ordenamiento de las aristas.

Veamos un ejemplo simple sobre este mismo grafo, para entender exactamente qué aristas elige Kruskal, en qué orden, y por qué rechaza alguna de ellas:

> **Figura 2.** Kruskal paso a paso: orden de revisión de las aristas y motivo de aceptación o rechazo.

#### 3. Algoritmo de Prim (Jarník)

Descrito originalmente por Vojtěch Jarník en 1930 y redescubierto por Robert Prim en 1957, este algoritmo también es goloso, pero construye el árbol de forma distinta: en lugar de considerar todas las aristas del grafo, crece un único árbol a partir de un vértice inicial.

**Proceso:**
1. Elegir un vértice inicial arbitrario y marcarlo como parte del árbol.
2. En cada paso, agregar al árbol la arista de menor peso que conecta un vértice ya incluido con uno que todavía no lo está.
3. Repetir hasta que todos los vértices formen parte del árbol.

**Complejidad:** O(E log V) usando una cola de prioridad (heap).

#### 4. Algoritmo de Boruvka

Es el algoritmo de MST más antiguo, publicado por Otakar Borůvka en 1926. Funciona por rondas: en cada ronda, **CADA** componente (inicialmente cada vértice es su propia componente) busca simultáneamente su arista más barata que la conecte con otra componente, y todas esas aristas se agregan a la vez, fusionando varias componentes en paralelo. En palabras simples: es como si cada isla mandara, al mismo tiempo, un bote hacia la isla más cercana que aún no está conectada; después de varias rondas de este tipo, todas las islas terminan conectadas.

**Proceso:**
1. Inicializar cada vértice como su propia componente.
2. En cada ronda, cada componente identifica la arista de menor peso que la conecta con otra componente distinta.
3. Agregar todas esas aristas mínimas a la vez y fusionar las componentes resultantes.
4. Repetir hasta que quede una sola componente (todo el grafo conectado).

Veamos también un ejemplo simple: sobre el mismo grafo de la Figura 1, Boruvka llega al mismo árbol en solo 2 rondas:

> **Figura 3.** Boruvka paso a paso sobre el grafo de la Figura 1: en la ronda 1 cada vértice elige su arista más barata, y en la ronda 2 cada componente resultante hace lo mismo.

Como cada ronda al menos reduce a la mitad el número de componentes, Boruvka termina en aproximadamente log₂ V rondas (Figura 4), lo que lo hace naturalmente adecuado para ejecutarse en paralelo.

> **Figura 4.** Número de rondas que necesita Boruvka según el número de vértices.

**Complejidad:** O(E log V).

#### 5. Comparación entre los tres algoritmos

| Criterio | Kruskal | Prim (Jarník) | Boruvka |
|----------|---------|---------------|---------|
| **Estrategia** | Ordena todas las aristas | Crece un árbol desde un vértice | Fusiona componentes por rondas |
| **Estructura clave** | Union-Find | Cola de prioridad (heap) | Lista de componentes |
| **Complejidad** | O(E log E) | O(E log V) | O(E log V) |
| **Mejor uso** | Grafos dispersos | Grafos densos | Paralelizable |
| **Cómputo paralelo/distribuido** | Difícil | Difícil | Natural (por rondas) |

---

### II. EJERCICIO/PROBLEMA RESUELTO POR EL DOCENTE

**Problema:** Dado el grafo ponderado de la Figura 1 (vértices A-F), calcular su árbol de expansión mínimo con Kruskal y verificar el resultado con Prim.

#### Kruskal (con Union-Find)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Arista { int u, v, peso; };

vector<int> padre, rango;

int encontrar(int x) {
    if (padre[x] != x) padre[x] = encontrar(padre[x]); // compresión de caminos
    return padre[x];
}

bool unir(int x, int y) {
    int rx = encontrar(x), ry = encontrar(y);
    if (rx == ry) return false; // ya están en la misma componente (formaría ciclo)
    if (rango[rx] < rango[ry]) swap(rx, ry);
    padre[ry] = rx;
    if (rango[rx] == rango[ry]) rango[rx]++;
    return true;
}

int main() {
    int n = 6; // A=0, B=1, C=2, D=3, E=4, F=5
    vector<Arista> aristas = {
        {0, 1, 4}, {0, 2, 2}, {1, 2, 1}, {1, 3, 5},
        {2, 3, 8}, {2, 4, 10}, {3, 4, 2}, {3, 5, 6}, {4, 5, 3}
    };

    sort(aristas.begin(), aristas.end(), [](Arista a, Arista b) {
        return a.peso < b.peso;
    });

    padre.resize(n);
    rango.assign(n, 0);
    for (int i = 0; i < n; i++) padre[i] = i;

    string nombres[] = { "A", "B", "C", "D", "E", "F" };
    int pesoTotal = 0;

    for (auto& a : aristas) {
        if (unir(a.u, a.v)) {
            cout << nombres[a.u] << " - " << nombres[a.v];
            cout << " (peso " << a.peso << ")" << endl;
            pesoTotal += a.peso;
        }
    }

    cout << "Peso total del árbol de expansion minimo: " << pesoTotal << endl;
    return 0;
}
```

#### Prim (con cola de prioridad)

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int n = 6; // A=0, B=1, C=2, D=3, E=4, F=5
    vector<vector<pair<int, int>>> grafo(n);

    auto agregarArista = [&](int u, int v, int peso) {
        grafo[u].push_back({v, peso});
        grafo[v].push_back({u, peso});
    };

    agregarArista(0, 1, 4);
    agregarArista(0, 2, 2);
    agregarArista(1, 2, 1);
    agregarArista(1, 3, 5);
    agregarArista(2, 3, 8);
    agregarArista(2, 4, 10);
    agregarArista(3, 4, 2);
    agregarArista(3, 5, 6);
    agregarArista(4, 5, 3);

    vector<bool> enArbol(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 0}); // {peso, vertice}: empezamos en A

    string nombres[] = { "A", "B", "C", "D", "E", "F" };
    int pesoTotal = 0;

    while (!pq.empty()) {
        auto [peso, u] = pq.top();
        pq.pop();
        if (enArbol[u]) continue;
        enArbol[u] = true;
        pesoTotal += peso;
        if (peso > 0) {
            cout << "Se agrega " << nombres[u];
            cout << " al árbol (peso " << peso << ")" << endl;
        }

        for (auto [v, p] : grafo[u]) {
            if (!enArbol[v])
                pq.push({p, v});
        }
    }

    cout << "Peso total del árbol de expansion minimo: " << pesoTotal << endl;
    return 0;
}
```

#### Resultados de la comparación

| Criterio | Kruskal | Prim |
|----------|---------|------|
| **Orden de construcción** | Por peso de arista global | Por cercanía al árbol actual |
| **Aristas elegidas** | B-C, A-C, D-E, E-F, B-D | B-C, A-C, D-E, E-F, B-D |
| **Peso total** | 13 | 13 |

Ambos algoritmos, aunque construyen el árbol de forma distinta, llegan exactamente al mismo árbol de expansión mínimo y al mismo peso total (13), porque en este grafo todas las aristas tienen pesos distintos, lo que garantiza un MST único.

---

### III. EJERCICIOS/PROBLEMAS PROPUESTOS

> **Nota:** En cada ejercicio, además del código y su ejecución, incluyan una breve explicación de qué hace el código y cómo está implementada la solución (qué estructuras de datos usaron, cómo adaptaron el algoritmo al problema, qué decisiones tomaron). No se aceptará únicamente el código copiado sin explicación: la calificación considera qué tan bien pueden justificar y explicar su implementación, no solo si el programa compila y corre correctamente.

**Ejercicio 1:**  
Implementa Kruskal con Union-Find (incluyendo compresión de caminos) para diseñar la red de cableado de menor costo que conecte un conjunto de edificios ingresados por el usuario.

**Ejercicio 2:**  
Implementa Prim con cola de prioridad y compara el árbol resultante (aristas y peso total) contra el obtenido con Kruskal sobre el mismo grafo.

**Ejercicio 3:**  
Implementa el algoritmo de Boruvka por rondas e imprime, en cada ronda, qué aristas se agregaron y cuántas componentes quedan, verificando que el resultado final coincide con el de Kruskal y Prim.

**Ejercicio 4:**  
Genera grafos aleatorios densos y dispersos de distintos tamaños y compara los tiempos de ejecución de Kruskal y Prim, determinando en qué casos conviene usar cada uno.

**Ejercicio 5:**  
Modela una red de distribución eléctrica (o de agua) entre varias localidades como un grafo ponderado por costo de tendido, y calcula el costo mínimo de conectarlas todas usando Kruskal o Prim.

---

### IV. CUESTIONARIO

1. ¿Por qué Kruskal necesita una estructura Union-Find, y qué problema resuelve la compresión de caminos dentro de esa estructura?
2. ¿En qué se diferencia la estrategia de Prim de la de Kruskal, si ambos son algoritmos golosos?
3. ¿Puede un grafo tener más de un árbol de expansión mínimo? ¿Bajo qué condición ocurre esto?
4. ¿Por qué se dice que Boruvka es un algoritmo naturalmente paralelizable?
5. ¿Qué diferencia fundamental existe entre el problema del árbol de expansión mínimo y el problema del camino más corto visto en el Laboratorio 4?

---

### V. REFERENCIAS Y BIBLIOGRAFÍA RECOMENDADAS

- Cormen, T. et al. *Introduction to Algorithms* (MIT Press, 2022).
- Sedgewick, R. & Wayne, K. *Algorithms* (Addison-Wesley, 2011).
- Brassard, G. & Bratley, P. *Fundamentals of Algorithmics* (Prentice Hall, 1996).

---

## TÉCNICAS E INSTRUMENTOS DE EVALUACIÓN

| TÉCNICAS | INSTRUMENTOS |
|----------|--------------|
| Resolución de ejercicios prácticos | Rúbrica |
| Redacción escrita | |

### CRITERIOS DE EVALUACIÓN

| Nivel | Descripción |
|-------|-------------|
| **1** | Insatisfactorio |
| **2** | En proceso |
| **3** | Satisfactorio |
| **4** | Sobresaliente |

#### Criterio: Informe - Cantidad de Información

| Nivel | Descripción |
|-------|-------------|
| **1** | El informe es difícil de leer y no cuenta con la información pedida (0) |
| **2** | Uno o más de los temas no han sido tratados (0) |
| **3** | El informe incluye la información solicitada, pero cuesta comprenderlo (2) |
| **4** | Todos los temas han sido tratados, pero solo la mayor parte de las preguntas contestadas, como mínimo con una frase cada una (2) |
| **5** | El informe incluye la información solicitada y es comprensible (4) |
| **6** | Todos los temas han sido tratados y todas las preguntas han sido contestadas, aunque de forma breve, con una o dos frases cada una (3) |
| **7** | La información está claramente relacionada con el tema principal (3) |
| **8** | El informe está claramente detallado e incluye la información solicitada (8) |
| **9** | Todos los temas han sido tratados y todas las preguntas han sido contestadas con tres o más frases cada una (6) |
| **10** | La información está claramente relacionada con el tema principal y presenta otros ejemplos (6) |

#### Criterio: Calidad de Información

| Nivel | Descripción |
|-------|-------------|
| **1** | La información tiene poco que ver con el tema principal (0) |
| **2** | La información está relacionada con el tema principal (2) |
| **3** | La información está claramente relacionada con el tema principal (4) |
| **4** | La información está claramente relacionada con el tema principal y presenta otros ejemplos (6) |

---