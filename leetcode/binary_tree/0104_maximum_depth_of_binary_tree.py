# <3
# Tema: LeetCode Hub / DFS en Arbol Binario
# Resumen: Profundidad del arbol
# O: (n), visita cada nodo una vez
# Detalle: LeetCode 104 "Maximum Depth of Binary Tree": profundidad del arbol. Tecnica: dos
# funciones mutuamente recursivas que bajan por derecha e izquierda guardando la profundidad de
# cada hoja en una lista, y al final se toma el maximo. OJO: es dar la vuelta larga. Lo normal
# es una sola linea recursiva: 0 si el nodo es None, si no 1 + max(maxDepth(izq),
# maxDepth(der)).

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def der(self,root,cont,l):
        if(root.right == None):
            l.append(cont)
            return cont
        root = root.right
        cont+=1
        self.der(root,cont,l)
        self.izq(root,cont,l)

    def izq(self,root,cont,l):
        if(root.left == None):
            l.append(cont)
            return cont
        root = root.left
        cont+=1
        self.izq(root,cont,l)
        self.der(root,cont,l)

    def maxDepth(self, root: Optional[TreeNode]) -> int:
        l = []
        if(root == None):
            return 0
        cont = 1
        if(root.left == None and root.right == None):
            return cont
        self.der(root,cont,l)
        self.izq(root,cont,l)
        return (max(l))
        