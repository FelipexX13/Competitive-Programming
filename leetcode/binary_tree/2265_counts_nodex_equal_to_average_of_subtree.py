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

        