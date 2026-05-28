# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        f = []
        cabeza1 = l1
        cabeza2 = l2
        while True:
            if(cabeza1 and cabeza2):
                v = cabeza1.val + cabeza2.val
                f.append(v)
                cabeza1 = cabeza1.next
                cabeza2 = cabeza2.next
            elif(cabeza1):
                v = cabeza1.val
                f.append(v)
                cabeza1 = cabeza1.next
            elif(cabeza2):
                v = cabeza2.val
                f.append(v)
                cabeza2 = cabeza2.next
            else:
                break

        k = []
        i = 0 
        while (i < len(f)):
            if(f[i]<=9):
                k.append(f[i])
            else:
                k.append(f[i]-10)
                if(i==len(f)-1):
                    f.append(1)
                else:
                    f[i+1] += 1
            i+=1
        final = ListNode()
        final.val = k[0]
        cabeza = final
        for i in range(1, len(k)):
            nuevo = ListNode()  
            nuevo.val = k[i]
            cabeza.next = nuevo     
            cabeza = cabeza.next 

        return final