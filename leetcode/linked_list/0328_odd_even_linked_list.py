# <3
# Tema: LeetCode Hub / Separar en Dos Listas
# NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
#
# LeetCode 328 "Odd Even Linked List": reordenar para que queden primero las posiciones impares y
# despues las pares, conservando el orden relativo.
# Tecnica: se arman dos listas mientras se recorre, una con las posiciones impares y otra con las
# pares, y al final se pega la de pares al final de la de impares. La variable voy lleva la
# posicion, no el valor, que es lo que puede confundir al leerlo.
# El caso de un solo nodo va aparte porque ahi la lista de pares nunca se crea.

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
            
        