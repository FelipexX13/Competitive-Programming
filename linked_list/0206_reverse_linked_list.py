# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if(head is None):
            return head

        nodos = []
        while head != None:
            nodos.append(head.val)
            head = head.next
        
        prev = ListNode(nodos[len(nodos)-1])
        q = prev
        for i in range(len(nodos)-2,-1,-1):
            act = ListNode(nodos[i])
            prev.next = act
            prev = prev.next

        return q

