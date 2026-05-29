# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def mergeTwoLists(self, list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:
        if(list1 == None and list2 == None):
            return list1
        elif(list1 == None):
            return list2
        elif(list2 == None):
            return list1
        h1 = list1
        h2 = list2
        cabeza1 = list1
        cabeza2 = list2
        if(cabeza1.val <= cabeza2.val):
            ant = cabeza1
            ant2 = cabeza2
            while (cabeza1 != None):
                if(cabeza2 == None):
                    return list1
                if(cabeza1.val >= cabeza2.val):
                    cabeza1 = ant
                    cabeza2 = cabeza2.next
                    ant2.next = cabeza1.next
                    cabeza1.next = ant2
                    ant2 = cabeza2
                ant = cabeza1
                cabeza1 = cabeza1.next

            cabeza1 = h1
            while (cabeza1.next != None):
                cabeza1 = cabeza1.next
            cabeza1.next = cabeza2
            return list1
        else:
            ant = cabeza1
            ant2 = cabeza2
            while (cabeza2 != None):
                if(cabeza1 == None):
                    return list2
                if(cabeza2.val >= cabeza1.val):
                    cabeza2 = ant2
                    cabeza1 = cabeza1.next
                    ant.next = cabeza2.next
                    cabeza2.next = ant
                    ant = cabeza1
                ant2 = cabeza2
                cabeza2 = cabeza2.next
            cabeza2 = h2
            while (cabeza2.next != None):
                cabeza2 = cabeza2.next
            cabeza2.next = cabeza1
            return list2
        
        