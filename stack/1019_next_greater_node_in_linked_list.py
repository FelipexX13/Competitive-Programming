# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def nextLargerNodes(self, head: Optional[ListNode]) -> List[int]:
        lista = []
        stack = []
        stackpos = []
        p = 0
        c = head
        while c != None:
            lista.append(0)
            while True:
                if(len(stack) != 0 and stack[-1] < c.val):
                    lista[stackpos[-1]] = c.val
                    stack.pop()
                    stackpos.pop()
                else:
                    break
            stack.append(c.val)
            stackpos.append(p)
            p+= 1
            c = c.next
            
        return lista

       
        
        