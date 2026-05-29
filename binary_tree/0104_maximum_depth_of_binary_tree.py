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
        