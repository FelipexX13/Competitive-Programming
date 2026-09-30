# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def oddEvenList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if(head is None):
            return head
        voy = 1
        impar = ListNode(head.val)
        p = impar
        while head != None:
            head = head.next
            if(head is None):
                break
            voy += 1
            if(voy % 2 == 0 and voy == 2):
                par = ListNode(head.val)
                q = par
            elif(voy % 2 == 0):
                new2 = ListNode(head.val)
                par.next = new2
                par = par.next
            else:
                new2 = ListNode(head.val)
                impar.next = new2
                impar = impar.next
        if(voy != 1):
            impar.next = q
            return p
        else:
            return impar
            
        