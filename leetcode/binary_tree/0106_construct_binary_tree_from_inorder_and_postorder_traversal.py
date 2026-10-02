# <3
# Tema: LeetCode Hub / Divide y Conquista sobre Recorridos
# Resumen: Reconstruir el arbol a partir de sus recorridos inorden y postorden
# O: (n^2) por el inorder.index(); con un mapa de posiciones seria (n)
# Detalle: LeetCode 106 "Construct Binary Tree from Inorder and Postorder Traversal":
# reconstruir el arbol a partir de sus recorridos inorden y postorden. Tecnica: el ULTIMO de
# postorden es la raiz. Se busca en inorden y eso parte los dos recorridos en izquierda y
# derecha, y se repite. La cantidad de nodos de la izquierda es lo que dice donde cortar el
# postorden. OJO: inorder.index() es O(n), asi que en el peor caso queda O(n^2). Con un
# diccionario valor -> posicion baja a O(n).

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:

    def construir(self, inorder, postorder):
        if len(inorder) == 0:
            return None
        padre = postorder[-1]
        nodo = TreeNode(padre)

        pos = inorder.index(padre)

        inorder_izq = inorder[:pos]
        inorder_der = inorder[pos + 1:]
        cantidad_izq = len(inorder_izq)

        postorder_izq = postorder[:cantidad_izq]
        postorder_der = postorder[cantidad_izq:-1]
        nodo.left = self.construir(inorder_izq, postorder_izq)
        nodo.right = self.construir(inorder_der, postorder_der)

        return nodo

    def buildTree(self, inorder: list[int], postorder: list[int]) -> TreeNode | None:

        return self.construir(inorder, postorder)