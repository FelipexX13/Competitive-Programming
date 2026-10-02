# <3
# Tema: LeetCode Hub / Palindromo en Lista Ligada
# Resumen: Decir si la lista se lee igual al reves
# O: (n^2) por el insert(0,...); con liebre y tortuga seria (n) y (1) de memoria
# Detalle: LeetCode 234 "Palindrome Linked List": decir si la lista se lee igual al reves.
# Tecnica: se mide el largo, se parte a la mitad y se guardan la primera mitad en orden y la
# segunda al reves (con insert(0, ...)), y se comparan. La bandera flag maneja el caso de largo
# impar, donde el elemento del centro se ignora. OJO: deja dos prints, y el insert(0, ...) es
# O(n) cada vez, asi que esa parte es O(n^2). La version O(1) de memoria: liebre y tortuga para
# hallar el medio, invertir la segunda mitad en el sitio y comparar.

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
        
        