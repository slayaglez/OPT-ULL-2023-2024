# OPT-ULL-2023-2024
Repositorio con el proyecto en C++ creado en las clases de Optimización de 1º de Ingeniería Informática en la Universidad de La Laguna.

## Descripción

Un programa de grafos desarrollado a lo largo de un cuatrimestre entero. El programa cuenta con diferentes métodos como los siguientes:
- Constructores y destructores de grafos (listas enlazadas)
- Si el grafo es dirigido o no
- Información del grafo
- Recorridos de **profundidad** por el grafo
- Recorridos de **amplitud** por el grafo
- Recorridos de amplitud a **mínimo costo**

Al compilar el programa se generará un ejecutable como `Optimizacion_en_grafos.exe` donde habrá un menú en el que se presentan las siguientes opciones:

En caso de grafo no dirigido
- Mostrar información básica del grafo
- Mostrar la linea de adyacencia
- Realizar un recorrido en amplitud del grafo desde un nodo por sucesores
- Realizar un recorrido en amplitud del grafo asumiendo el costo mínimo

En caso de grafo dirigido
- Mostrar información básica del grafo
- Mostrar la lista de sucesores
- Mostrar la lista de predecesores
- Realizar un recorrido de amplitud del grafo desde un nodo por sucesores

Para los caminos mínimos usamos distintos algoritmos, entre ellos Dijkstra, BellmanFordEnd y Floyd-Warshall. Para ejecutar el programa también se debe introducir el nombre del fichero que debe estar en la misma carpeta del ejecutable, en este caso hay 8 archivos .gr como grafos de ejemplo, pero siguiendo la nomenclatura se puede crear un fichero .gr propio.
