# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def hasCycle(self, head: Optional[ListNode]) -> bool:
        slow = head
        fast = head

        #Puedo hacer el de visitados y sale, pero para practicar eso
        #uno mas rapido que otro

        while fast != None and fast.next!=None:
            slow = slow.next
            fast = fast.next.next

            if slow == fast:
                return True

        return False
        