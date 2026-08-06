from collections import deque
class Solution:
    def findOrder(self, numCourses: int, prerequisites: List[List[int]]) -> List[int]:

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
                return []
                
            return topo_order

        for i in range(len(prerequisites)):
            prerequisites[i] = [prerequisites[i][1], prerequisites[i][0]]
        return (kahn_topological_sort(numCourses, prerequisites))
