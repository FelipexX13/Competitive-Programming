# <3
# Tema: LeetCode Hub / Orden Topologico de Kahn
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n+m), Kahn con los grados de entrada
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 207 "Course Schedule": decir si se pueden tomar todos los cursos respetando los
# prerrequisitos. Tecnica: Kahn. Se cuentan los grados de ENTRADA, se meten a la cola los de
# grado 0 y al sacar uno se baja el grado de sus vecinos. Si al final el orden no tiene los n
# nodos, hay un ciclo. Detectar ciclo en dirigido con Kahn es contar cuantos salieron, y eso es
# toda la gracia.

from collections import deque
class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        def kahn_topological_sort(num_nodes, edges):
            # 1. Initialize adjacency list and in-degree array
            adj_list = {i: [] for i in range(num_nodes)}
            in_degree = [0] * num_nodes
            
            # 2. Build the graph: edge is u -> v
            for u, v in edges:
                adj_list[u].append(v)
                in_degree[v] += 1
                
            # 3. Add all nodes with 0 incoming edges to the queue
            queue = deque([i for i in range(num_nodes) if in_degree[i] == 0])
            topo_order = []
            
            # 4. Process the queue
            while queue:
                u = queue.popleft()
                topo_order.append(u)
                
                for neighbor in adj_list[u]:
                    in_degree[neighbor] -= 1
                    if in_degree[neighbor] == 0:
                        queue.append(neighbor)
                        
            # 5. Check for cycles
            if len(topo_order) != num_nodes:
                return False
                
            return True
        
        return kahn_topological_sort(numCourses, prerequisites)
