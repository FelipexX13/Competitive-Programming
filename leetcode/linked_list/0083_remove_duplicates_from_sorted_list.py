# <3
# Tema: LeetCode Hub / Recorrido de Lista Ligada
# Resumen: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/)
#
# O: (n), una pasada
# Detalle: NO ES MIO: codigo de Juan Jose Lozano, del repo del equipo (carpeta leetcode/).
# LeetCode 83 "Remove Duplicates from Sorted List": quitar los repetidos de una lista ordenada.
# Tecnica: como esta ordenada, los repetidos estan pegados, asi que basta recordar el ultimo
# valor visto y solo copiar cuando cambia. Aca construye una lista NUEVA en vez de saltarse
# nodos. En el sitio seria mas barato: si nodo.val == nodo.next.val entonces nodo.next =
# nodo.next.next.

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
            
        