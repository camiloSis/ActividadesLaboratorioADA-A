# UNIVERSIDAD NACIONAL DE SAN AGUSTÍN
## FACULTAD DE INGENIERÍA DE PRODUCCIÓN Y SERVICIOS
### ESCUELA PROFESIONAL DE INGENIERÍA DE SISTEMAS

---

**Formato:** Guía de Práctica de Laboratorio / Talleres / Centros de Simulación  
**Aprobación:** 2022/03/01  
**Código:** GUIA-PRLD-001  

---

# GUÍA DE LABORATORIO N° 6

## INFORMACIÓN BÁSICA

| Campo | Detalle |
|-------|---------|
| **Asignatura** | Análisis y Diseño de Algoritmos |
| **Título de la Práctica** | Programación Dinámica: Fundamentos y el Problema de la Diligencia |
| **Número de Práctica** | 6 |
| **Tipo de Práctica** | ☑ Individual  ☐ Grupal |
| **Máximo de Estudiantes** | — |
| **Año Lectivo** | 2026-B |
| **Semestre** | IV (cuarto) |
| **Fecha Inicio** | 22/10/2026 |
| **Fecha Fin** | 26/10/2026 |
| **Duración** | 2 horas |

**Recursos a utilizar:**
- Un computador
- Material del curso
- Bibliografía del curso

**Docente(s):**
- Mg. Roxana Evelyn Limache Calatayud

---

## OBJETIVOS, TEMAS Y COMPETENCIAS

### Objetivos
- Comprender los fundamentos de la Programación Dinámica: subestructura óptima y subproblemas superpuestos.
- Diferenciar entre memorización (top-down) y tabulación (bottom-up).
- Aplicar la técnica **SRTBOT** para diseñar soluciones de Programación Dinámica.
- Resolver el problema de la diligencia utilizando Programación Dinámica.

### Temas
- Fundamentos de la Programación Dinámica
- Memorización y tabulación
- Técnica SRTBOT
- El problema de la diligencia

### Competencias
| Código | Descripción |
|--------|-------------|
| **C.a** | Capacidad de análisis de problemas computacionales |
| **C.b** | Diseño de soluciones algorítmicas eficientes |
| **C.c** | Validación y verificación de algoritmos |
| **C.d** | Comunicación técnica y redacción formal |

---

## CONTENIDO DE LA GUÍA

### I. MARCO CONCEPTUAL

#### 1. ¿Qué es la Programación Dinámica?

La **Programación Dinámica (PD)** es una técnica de diseño de algoritmos que resuelve problemas complejos dividiéndolos en subproblemas más pequeños, igual que **Divide y Vencerás** (Laboratorio 3). La diferencia clave es que, en PD, esos subproblemas se repiten una y otra vez (**subproblemas superpuestos**), así que en lugar de resolverlos cada vez desde cero, se resuelven **UNA SOLA VEZ** y su resultado se guarda para reutilizarlo cuando se vuelva a necesitar.

Un problema puede resolverse con Programación Dinámica cuando cumple dos condiciones:

1. **Subestructura óptima:** la solución óptima del problema completo se puede construir a partir de las soluciones óptimas de sus subproblemas.
2. **Subproblemas superpuestos:** los mismos subproblemas aparecen repetidamente al resolver el problema de forma recursiva.

> **Ejemplo:** Mergesort y Quicksort **NO** se benefician de PD porque sus subproblemas son independientes y nunca se repiten. En cambio, calcular `Fibonacci(5)` recursivamente vuelve a calcular `Fibonacci(3)` y `Fibonacci(2)` muchas veces.

**Figura 1.** Subproblemas independientes (Divide y Vencerás) frente a subproblemas superpuestos (Programación Dinámica).

---

#### 2. Memorización (top-down) vs Tabulación (bottom-up)

Existen dos formas de implementar Programación Dinámica:

| Característica | Memorización (top-down) | Tabulación (bottom-up) |
|----------------|------------------------|------------------------|
| **Forma de resolver** | Recursiva, guarda resultados | Iterativa, llena una tabla |
| **Orden de cálculo** | El que pida la recursión | Definido de antemano (SRTBOT: T) |
| **Subproblemas calculados** | Solo los que realmente se necesitan | Todos los de la tabla |
| **Riesgo** | Desbordamiento de pila en recursiones profundas | Ninguno (sin recursión) |

**Memorización:** resuelve el problema de la manera recursiva natural, pero guarda ("memoiza") el resultado de cada subproblema la primera vez que se calcula, en un arreglo o mapa; si ese subproblema se vuelve a necesitar, se devuelve el valor guardado en lugar de recalcularlo.

**Tabulación:** resuelve el problema de abajo hacia arriba: llena una tabla iterativamente empezando por los casos base, sin usar recursión.

El ejemplo clásico para entender esta diferencia es **Fibonacci**: calculado de forma recursiva ingenua tiene complejidad **O(2ⁿ)** porque recalcula los mismos subproblemas exponencialmente muchas veces; con memorización o tabulación baja a **O(n)**, porque cada subproblema se resuelve una única vez.

**Figura 2.** Fibonacci recursivo ingenuo frente a Fibonacci con memorización.  
**Figura 3.** Memorización (top-down) frente a tabulación (bottom-up) para Fibonacci.

---

#### 3. La técnica SRTBOT

**SRTBOT** es un procedimiento de seis pasos que ayuda a diseñar sistemáticamente una solución de Programación Dinámica para cualquier problema nuevo:

| Paso | Letra | Descripción |
|------|-------|-------------|
| 1 | **S** — **Subproblemas** | Definir con precisión qué representa cada subproblema o estado (ej: "el costo mínimo para llegar desde el nodo X hasta el destino"). |
| 2 | **R** — **Relación de Recurrencia** | Expresar la solución de un subproblema en función de subproblemas más pequeños. |
| 3 | **T** — **orden Topológico** | Determinar en qué orden deben resolverse los subproblemas para que, al resolver cada uno, sus dependencias ya estén resueltas. |
| 4 | **B** — **casos Base** | Identificar los subproblemas más pequeños, que se resuelven directamente sin depender de otros. |
| 5 | **O** — **problema Original** | Precisar cuál subproblema específico responde la pregunta que realmente se quiere resolver. |
| 6 | **T** — **Tiempo** | Calcular la complejidad temporal total, típicamente (número de subproblemas) × (tiempo por subproblema). |

**Figura 4.** La técnica SRTBOT: seis preguntas y su respuesta en el problema de la diligencia.

---

#### 4. El problema de la diligencia (Stagecoach Problem)

Es un problema clásico de la investigación de operaciones, popularizado por **Richard Bellman** como ejemplo introductorio de Programación Dinámica: un viajero debe llegar de un origen a un destino final atravesando varias etapas intermedias, donde cada tramo tiene un costo distinto, y se busca la ruta de costo total mínimo.

**Aplicando SRTBOT:**
- **S** = `f(nodo)` es el costo mínimo para llegar desde ese nodo hasta el destino
- **R** = `f(nodo) = min { costo(nodo, vecino) + f(vecino) }` para cada vecino alcanzable
- **T** = se procesan los nodos en orden inverso, empezando por el destino y avanzando hacia el origen
- **B** = `f(destino) = 0`
- **O** = la respuesta buscada es `f(origen)`
- **T (tiempo)** = **O(V + E)**

**Figura 5.** Problema de la diligencia: etapas y camino óptimo (A-C-E-H).  
**Figura 6.** Resolución paso a paso del problema de la diligencia con SRTBOT (de H hacia A).

> **Nota:** El problema de la diligencia **NO** es el problema del viajero (TSP). En la diligencia se busca el camino más barato entre un origen y un destino, avanzando por etapas ordenadas; como el grafo no tiene ciclos, la Programación Dinámica lo resuelve en **O(V + E)**. En el problema del viajero hay que visitar **TODAS** las ciudades exactamente una vez y regresar al origen, sin etapas fijas: el orden de visita es libre y existen **(n-1)!** rutas posibles, por eso es **NP-difícil** y no tiene una solución eficiente conocida.

---

#### 5. Memorización vs Tabulación: comparación

| Criterio | Memorización (top-down) | Tabulación (bottom-up) |
|----------|------------------------|------------------------|
| **Forma de resolver** | Recursiva, guarda resultados | Iterativa, llena una tabla |
| **Orden de cálculo** | El que pida la recursión | Definido de antemano (SRTBOT: T) |
| **Subproblemas calculados** | Solo los que realmente se necesitan | Todos los de la tabla |
| **Riesgo** | Desbordamiento de pila en recursiones profundas | Ninguno (sin recursión) |

---

### II. EJERCICIO/PROBLEMA RESUELTO POR EL DOCENTE

**Problema:** Resolver el problema de la diligencia de la Figura 5 aplicando la técnica SRTBOT, calculando el costo mínimo desde A hasta H y la ruta óptima correspondiente.

#### Tabla de resolución

| Etapa | Nodo | f(nodo) | Decisión óptima |
|-------|------|---------|-----------------|
| 4 (base) | H | 0 | — |
| 3 | E | 3 | E → H |
| 3 | F | 6 | F → H |
| 3 | G | 3 | G → H |
| 2 | B | 9 | B → G → H |
| 2 | C | 6 | C → E → H |
| 2 | D | 7 | D → E → H |
| 1 (original) | A | 10 | A → C → E → H |

> **Nota:** Desde D existe empate entre pasar por E o por F (ambos suman 7), y por eso desde A hay **tres** rutas de costo 10: `A-C-E-H`, `A-D-E-H` y `A-D-F-H` (ver Figura 6). Esto ilustra que la Programación Dinámica garantiza encontrar el **VALOR** óptimo, pero puede haber más de un camino que lo alcance.

#### Código (tabulación, orden topológico inverso)

```cpp
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    // Nodos: 0=A, 1=B, 2=C, 3=D, 4=E, 5=F, 6=G, 7=H
    int n = 8;
    vector<vector<pair<int, int>>> grafo(n); // (destino, costo)

    grafo[0] = { {1, 2}, {2, 4}, {3, 3} };  // A -> B, C, D
    grafo[1] = { {4, 7}, {5, 4}, {6, 6} };  // B -> E, F, G
    grafo[2] = { {4, 3}, {5, 2}, {6, 4} };  // C -> E, F, G
    grafo[3] = { {4, 4}, {5, 1}, {6, 5} };  // D -> E, F, G
    grafo[4] = { {7, 3} };                  // E -> H
    grafo[5] = { {7, 6} };                  // F -> H
    grafo[6] = { {7, 3} };                  // G -> H

    vector<int> f(n, INT_MAX);
    vector<int> siguiente(n, -1);
    f[7] = 0; // caso base: el destino H cuesta 0 llegar a sí mismo

    // T: orden topologico inverso: G, F, E, D, C, B, A
    for (int u = 6; u >= 0; u--) {
        for (size_t k = 0; k < grafo[u].size(); k++) {
            int v = grafo[u][k].first, costo = grafo[u][k].second;
            // R: relacion de recurrencia
            if (f[v] != INT_MAX && costo + f[v] < f[u]) {
                f[u] = costo + f[v];
                siguiente[u] = v;
            }
        }
    }

    string nombres[] = { "A", "B", "C", "D", "E", "F", "G", "H" };
    cout << "Costo minimo desde A hasta H: " << f[0] << endl;

    cout << "Ruta optima: ";
    int actual = 0; // O: la respuesta buscada es f[0], el origen
    while (actual != -1) {
        cout << nombres[actual];
        actual = siguiente[actual];
        if (actual != -1) cout << " -> ";
    }
    cout << endl;

    return 0;
}
```

---

### III. EJERCICIOS/PROBLEMAS PROPUESTOS

> **Nota:** En cada ejercicio, además del código y su ejecución, incluyan una breve explicación de qué hace el código y cómo está implementada la solución (qué estructuras de datos usaron, cómo adaptaron el algoritmo al problema, qué decisiones tomaron). No se aceptará únicamente el código copiado sin explicación: la calificación considera qué tan bien pueden justificar y explicar su implementación, no solo si el programa compila y corre correctamente.

#### Ejercicio 1
Diseña tu propio problema de la diligencia con **al menos 5 etapas**, y resuélvelo aplicando explícitamente cada paso de la técnica **SRTBOT** (documenta S, R, T, B, O y T en tu informe).

#### Ejercicio 2
Implementa **Fibonacci** de tres formas:
1. Recursivo ingenuo
2. Con memorización (top-down)
3. Con tabulación (bottom-up)

Compara sus tiempos de ejecución para **n = 10, 20 y 30**.

#### Ejercicio 3
Modifica el código del problema de la diligencia para que, cuando existan empates como el de D, se impriman **TODOS** los caminos óptimos encontrados, no solo uno.

#### Ejercicio 4
Aplica la técnica **SRTBOT** para resolver un problema de camino de costo **MÁXIMO** (en vez de mínimo) sobre una malla de etapas similar a la del ejercicio resuelto.

#### Ejercicio 5
Investiga y documenta un problema real (logística, finanzas, biología computacional) que pueda modelarse como un problema de decisión multietapa similar al de la diligencia, y explica cómo se definirían sus subproblemas.

---

### IV. CUESTIONARIO

1. ¿Qué dos condiciones debe cumplir un problema para poder resolverse con Programación Dinámica?
2. ¿Cuál es la diferencia principal entre memorización y tabulación?
3. En la técnica SRTBOT, ¿qué garantiza específicamente el paso del orden topológico?
4. ¿Por qué el problema de la diligencia puede tener más de una solución óptima?
5. ¿Por qué aplicar Programación Dinámica a un algoritmo como Mergesort (Laboratorio 3) no traería ninguna mejora de eficiencia?

---

### V. REFERENCIAS Y BIBLIOGRAFÍA RECOMENDADAS

- Cormen, T. et al. *Introduction to Algorithms* (MIT Press, 2022).
- Sedgewick, R. & Wayne, K. *Algorithms* (Addison-Wesley, 2011).
- Brassard, G. & Bratley, P. *Fundamentals of Algorithmics* (Prentice Hall, 1996).

---

## TÉCNICAS E INSTRUMENTOS DE EVALUACIÓN

### Instrumentos: Rúbrica

| Nivel | Denominación |
|-------|--------------|
| 1 | Insatisfactorio |
| 2 | En proceso |
| 3 | Satisfactorio |
| 4 | Sobresaliente |

### Criterios de evaluación

#### Informe

| Criterio | 1 - Insatisfactorio (0) | 2 - En proceso (2) | 3 - Satisfactorio (4) | 4 - Sobresaliente (6-8) |
|----------|------------------------|-------------------|----------------------|------------------------|
| **Calidad de información** | La información tiene poco que ver con el tema principal | La información está relacionada con el tema principal | La información está claramente relacionada con el tema principal | La información está claramente relacionada con el tema principal y presenta otros ejemplos |
| **Cantidad de información** | Uno o más de los temas no han sido tratados | El informe incluye la información solicitada, pero cuesta comprenderlo | El informe incluye la información solicitada y es comprensible | El informe está claramente detallado e incluye la información solicitada |
| **Tratamiento de temas y preguntas** | — | Todos los temas han sido tratados, pero solo la mayor parte de las preguntas contestadas, como mínimo con una frase cada una | Todos los temas han sido tratados y todas las preguntas han sido contestadas, aunque de forma breve, con una o dos frases cada una | Todos los temas han sido tratados y todas las preguntas han sido contestadas con tres o más frases cada una |

### Técnicas
- Resolución de ejercicios prácticos
- Redacción escrita