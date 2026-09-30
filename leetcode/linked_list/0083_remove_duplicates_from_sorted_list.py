# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def deleteDuplicates(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if(head is None):
            return head
        voy = head.val
        new = ListNode(head.val)
        p = new
        while head != None:
            if(head.val != voy):
                voy = head.val
                new2 = ListNode(head.val)
                new.next = new2
                new = new.next
            head = head.next
        return p
            
        