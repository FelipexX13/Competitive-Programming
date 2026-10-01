# <3
# Tema: LeetCode Hub / DFS que Sube Informacion
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 2265 "Count Nodes Equal to Average of Subtree": cuantos nodos valen exactamente el
# promedio entero de su subarbol. Tecnica: DFS que devuelve DOS valores hacia arriba, la suma y
# la cantidad de nodos del subarbol. Con eso el promedio sale en el padre sin volver a recorrer
# nada. Es el patron tipico de DFS que retorna un resumen. OJO: usa -1 como marca de no hay hijo
# y un contador global. Con valores negativos en el arbol la marca se confundiria con un valor
# real.

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
cont = 0
class Solution:

    def dfs(self,nodo):
        global cont
        if(nodo == None):
            return -1, -1
        else:
            val1, cant1 = self.dfs(nodo.left)
            val2, cant2 = self.dfs(nodo.right)
            if(val1 == -1 and val2 == -1):
                cont+=1
                return nodo.val, 1
            elif(val1 != -1 and val2 != -1):
                val = (val1+val2+nodo.val)//(cant1+cant2+1)
                if(val == nodo.val):
                    cont+=1
                return val1+val2+nodo.val, cant1+cant2+1
            else:
                if(val1 != -1):
                    val = (val1 + nodo.val) // (cant1 + 1)
                    if val == nodo.val:
                        cont += 1
                    return val1 + nodo.val, cant1 + 1
                else:
                    val = (val2 + nodo.val) // (cant2 + 1)
                    if val == nodo.val:
                        cont += 1
                    return val2 + nodo.val, cant2 + 1

    def averageOfSubtree(self, root: TreeNode) -> int:
        global cont
        cont = 0
        self.dfs(root)
        return cont

        