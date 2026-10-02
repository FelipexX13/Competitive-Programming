# <3
# Tema: LeetCode Hub / Atajo de Libreria
# Resumen: Copia profunda de una lista con un puntero extra que apunta a cualquier nodo
# O: (n) por el deepcopy, pero se salta el ejercicio
# Detalle: LeetCode 138 "Copy List with Random Pointer": copia profunda de una lista con un
# puntero extra que apunta a cualquier nodo. Tecnica del codigo: copy.deepcopy(head). Una linea
# y pasa. OJO: se salta el ejercicio. Lo que se buscaba es la tecnica del diccionario nodo viejo
# -> nodo nuevo en una primera pasada, y en la segunda conectar next y random usando ese mapa.
# Ese patron si sirve para clonar grafos (LeetCode 133 es el mismo).

import copy
class Solution:
    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':        
        return copy.deepcopy(head)


        