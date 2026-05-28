# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def isPalindrome(self, head: Optional[ListNode]) -> bool:
        num2 = 0
        punt = head
        while(punt != None):
            punt = punt.next
            num2+=1
        if(num2%2==0):
            num=num2/2
            flag = False
        else:
            num=int(num2/2)
            flag = True
        punt1 = head
        p1 = []
        p2 = []
        cont = 0
        while(cont < num2):
            if(flag == False):
                if(cont >= num):
                    p2.insert(0,punt1.val)
                else:
                    p1.append(punt1.val)
            else:
                if(cont > num):
                    p2.insert(0,punt1.val)
                elif(cont<num):
                    p1.append(punt1.val)
            punt1 = punt1.next
            cont+=1
        print(p1)
        print(p2)
        if(p1 == p2 or num2==1):
            return True
        else:
            return False
        
        