class Solution:
    def cloneGraph(self, node: Optional['Node']) -> Optional['Node']:

        if not node:
            return None

        visited = {}
        # original -> copia

        def creator(curr):

            if curr in visited:
                return visited[curr]

            copy = Node(curr.val)
            visited[curr] = copy

            for nxt in curr.neighbors:
                copy.neighbors.append(creator(nxt))

            return copy

        return creator(node)
