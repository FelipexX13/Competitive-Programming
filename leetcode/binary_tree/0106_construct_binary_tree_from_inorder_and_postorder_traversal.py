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